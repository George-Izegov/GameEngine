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
	m_Camera->SetPosition(0.0f, 0.0f, -5.0f);

	for (int i = 0; i < 1; i++)
	{
		ObjModel* m_model = new ObjModel("OBJ/seahorse.obj");
		models.push_back(m_model);

	}
	// Create the model object.

	// Initialize the model object.
	models.at(0)->Initialize(m_D3D->GetDevice(), m_D3D->GetDeviceContext(), {0,0,0}, 1.0f, L"pink.jpg");


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

	return true;
}

void Graphics::GoCameraForward(int dir)
{
	float dist = sqrt(m_Camera->GetPosition().x * m_Camera->GetPosition().x +
		m_Camera->GetPosition().y * m_Camera->GetPosition().y +
		m_Camera->GetPosition().z * m_Camera->GetPosition().z);

	DirectX::SimpleMath::Vector3 lookAt;
	if (dist > 0) lookAt = m_Camera->GetPosition() / dist;
	m_Camera->SetPosition(m_Camera->GetPosition().x - dir*0.1f*lookAt.x, 
		m_Camera->GetPosition().y - dir * 0.1f * lookAt.y,
		m_Camera->GetPosition().z - dir*0.1f*lookAt.z);
}

void Graphics::RotateCameraToRight(int dir)
{
	float dist = sqrt(m_Camera->GetPosition().x * m_Camera->GetPosition().x + 
		m_Camera->GetPosition().y* m_Camera->GetPosition().y +
		m_Camera->GetPosition().z * m_Camera->GetPosition().z);

	m_Camera->SetRotation(m_Camera->GetRotation().x, m_Camera->GetRotation().y - dir * 1.0f, m_Camera->GetRotation().z);
	m_Camera->SetPosition(-1*dist*XMScalarSin(m_Camera->GetRotation().y*3.14/180)* 
		XMScalarCos(m_Camera->GetRotation().x * 3.14 / 180),
		1 * dist * XMScalarSin(m_Camera->GetRotation().x * 3.14 / 180), -1*dist * XMScalarCos(m_Camera->GetRotation().y * 3.14 / 180)*
		XMScalarCos(m_Camera->GetRotation().x * 3.14 / 180));
}

void Graphics::RotateCameraToUp(int dir)
{
	float dist = sqrt(m_Camera->GetPosition().x * m_Camera->GetPosition().x +
		m_Camera->GetPosition().y * m_Camera->GetPosition().y +
		m_Camera->GetPosition().z * m_Camera->GetPosition().z);

	m_Camera->SetRotation(m_Camera->GetRotation().x + dir * 1.0f, m_Camera->GetRotation().y, m_Camera->GetRotation().z);
	m_Camera->SetPosition(-1 * dist * XMScalarSin(m_Camera->GetRotation().y * 3.14 / 180) *
		XMScalarCos(m_Camera->GetRotation().x * 3.14 / 180),
		1 * dist * XMScalarSin(m_Camera->GetRotation().x * 3.14 / 180), -1 * dist * XMScalarCos(m_Camera->GetRotation().x * 3.14 / 180)* 
		XMScalarCos(m_Camera->GetRotation().y * 3.14 / 180));
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
		m_D3D->GetWorldMatrix(worldMatrix);
		
		// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
		model->Render(m_D3D->GetDeviceContext());
		// Render the model using the color shader.
		result = m_ColorShader->Render(m_D3D->GetDeviceContext(), model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, model->GetTexture());

	}

	// Present the rendered scene to the screen.
	m_D3D->EndScene();

	return true;
}
