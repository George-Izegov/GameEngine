#include "Graphics.h"


Graphics::Graphics()
{
	m_D3D = 0;
	m_Camera = 0;
	m_ColorShader = 0;

}


Graphics::Graphics(const Graphics& other)
{
}


Graphics::~Graphics()
{
}

void Graphics::SetCameraTransform(Vector3 dL, Vector3 dR)
{
	m_Camera->SetPosition(m_Camera->GetPosition() + dL);

	m_Camera->SetRotation(m_Camera->GetRotation() + dR);
}

bool Graphics::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
	bool result;


	// Create the Direct3D object.
	m_D3D = new D3DClass;
	if (!m_D3D)
	{
		return false;
	}

	// Initialize the Direct3D object.
	result = m_D3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D", L"Error", MB_OK);
		return false;
	}

	// Create the camera object.
	m_Camera = new Camera;
	if (!m_Camera)
	{
		return false;
	}

	// Set the initial position of the camera.
	m_Camera->SetPosition({ 0.0f, 0.0f, -5.0f });

	_light = new Light;

	for (int i = 0; i < 1; i++)
	{
		MeshOBJ* m_model = new MeshOBJ("Graphics/OBJ/seahorse.obj", M_Brass);
		models.push_back(m_model);

	}
	// Create the model object.

	// Initialize the model object.
	models.at(0)->Initialize(m_D3D->GetDevice(), m_D3D->GetDeviceContext(), {0,0,0}, 1.0f, L"Graphics/OBJ/pink.jpg");

	m_renderTexture = new RenderTextureClass;
	m_renderTexture->Initialize(m_D3D->GetDevice(), _light->ShadowMapSize, _light->ShadowMapSize, SCREEN_DEPTH, SCREEN_NEAR);

	m_depthShader = new DepthShaderClass;
	m_depthShader->Initialize(m_D3D->GetDevice(), hwnd);

	// Create the color shader object.
	m_ColorShader = new ColorShaderClass;
	if (!m_ColorShader)
	{
		return false;
	}

	// Initialize the color shader object.
	result = m_ColorShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the color shader object.", L"Error", MB_OK);
		return false;
	}

	_light->Init(m_D3D->GetDevice());

	return true;
}


void Graphics::Shutdown()
{
	if (m_D3D)
	{
		m_D3D->Shutdown();
		delete m_D3D;
		m_D3D = 0;
	}
	// Release the color shader object.
	if (m_ColorShader)
	{
		m_ColorShader->Shutdown();
		delete m_ColorShader;
		m_ColorShader = 0;
	}

	// Release the model object.
	if (models.size()>0)
	{
		for (auto model : models)
		{
			model->Shutdown();
			delete model;
			model = 0;
		}
		
	}

	// Release the camera object.
	if (m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}
	return;
}


bool Graphics::Frame()
{
	bool result;


	// Render the graphics scene.
	result = Render();
	if (!result)
	{
		return false;
	}


	return true;
}


bool Graphics::Render()
{
	SimpleMath::Matrix worldMatrix, viewMatrix, projectionMatrix;
	bool result;

	RenderToTexture();

	// Reset the render target back to the original back buffer and not the render to texture anymore.
	m_D3D->SetBackBufferRenderTarget();

	// Reset the viewport back to the original.
	m_D3D->ResetViewport();

	// Clear the buffers to begin the scene.
	m_D3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);

	int i = -1;
	for (auto model : models)
	{
		worldMatrix = worldMatrix.Identity;

		model->Render(m_D3D->GetDeviceContext());
		// Render the model using the color shader.
		result = m_ColorShader->Render(m_D3D->GetDeviceContext(), model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
			model->GetTexture(), model->GetMaterial().ambientColor, model->GetMaterial().diffuseColor,
			model->GetMaterial().specularColor, model->GetMaterial().specularPower, _light->GetDirection(), m_Camera->GetForwardVector(),
			_light->GetViewMatrix(), _light->GetProjMatrix(), m_renderTexture->GetShaderResourceView());
	}

	// Present the rendered scene to the screen.
	m_D3D->EndScene();

	return true;
}

void Graphics::RenderToTexture()
{
	// Set the render target to be the render to texture.
	m_renderTexture->SetRenderTarget(m_D3D->GetDeviceContext());

	// Clear the render to texture.
	m_renderTexture->ClearRenderTarget(m_D3D->GetDeviceContext(), 0.0f, 0.0f, 0.0f, 1.0f);


	for (auto model : models)
	{
		model->Render(m_D3D->GetDeviceContext());
		m_depthShader->Render(m_D3D->GetDeviceContext(), model->GetIndexCount(), Matrix::Identity, _light->GetViewMatrix(), _light->GetProjMatrix());
	}
}
