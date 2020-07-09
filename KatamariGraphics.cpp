#include "KatamariGraphics.h"
#include <iostream>

KatamariGraphics::KatamariGraphics()
{
	Player = 0;
	_light = 0;
	m_renderTexture = 0;
	m_depthShader = 0;
}

bool KatamariGraphics::Initialize(int screenWidth, int screenHeight, HWND hwnd)
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

	_light = new Light;

	// Create the model object.

	Player = new ObjModel("OBJ/Ball2.obj", M_Brass);
	Player->Initialize(m_D3D->GetDevice(), m_D3D->GetDeviceContext(), { 0,0,0 }, 1.0f, L"Textures/hohloma2.jpg");

	floor = new Square(M_Silver);
	floor->Initialize(m_D3D->GetDevice(), m_D3D->GetDeviceContext(), { 0,0,0 }, 150.0f, L"Textures/green.png");

	ObjModel* environmentItem = new ObjModel("OBJ/Wolf.obj", M_Silver);
	environmentItem->Initialize(m_D3D->GetDevice(), m_D3D->GetDeviceContext(), { 20, 0, -10 }, 0.5f, L"Textures/grey.jpg");
	environment.insert(environmentItem);

	environmentItem = new ObjModel("OBJ/Moto.obj", M_Brass);
	environmentItem->Initialize(m_D3D->GetDevice(), m_D3D->GetDeviceContext(), { 1000, 300, 500 }, 0.005f, L"Textures/grey.jpg");
	environment.insert(environmentItem);


	environmentItem = new ObjModel("OBJ/Dog.obj", M_Plastic);
	environmentItem->Initialize(m_D3D->GetDevice(), m_D3D->GetDeviceContext(), { -20,0,19 }, 0.3f, L"Textures/brown.jpg");
	environment.insert(environmentItem);


	environmentItem = new ObjModel("OBJ/Cat.obj");
	environmentItem->Initialize(m_D3D->GetDevice(), m_D3D->GetDeviceContext(), { 40,0,0 }, 0.2f, L"Textures/orange.jpg");
	environment.insert(environmentItem);

	environmentItem = new ObjModel("OBJ/Table.obj");
	environmentItem->Initialize(m_D3D->GetDevice(), m_D3D->GetDeviceContext(), { 6,0,-7}, 2.0f, L"Textures/brown.jpg");
	environment.insert(environmentItem);

	environmentItem = new ObjModel("OBJ/Vase2.obj");
	environmentItem->Initialize(m_D3D->GetDevice(), m_D3D->GetDeviceContext(), { 1,0,8 }, 3.0f, L"Textures/pink.jpg");
	environment.insert(environmentItem);

	environmentItem = new ObjModel("OBJ/Chair.obj");
	environmentItem->Initialize(m_D3D->GetDevice(), m_D3D->GetDeviceContext(), { 3.5,0,4.8 }, 2.0f, L"Textures/brown.jpg");
	environment.insert(environmentItem);

	environmentItem = new ObjModel("OBJ/BookCase.obj");
	environmentItem->Initialize(m_D3D->GetDevice(), m_D3D->GetDeviceContext(), { 5,0,1.5 }, 4.0f, L"Textures/brown.jpg");
	environment.insert(environmentItem);

	environmentItem = new ObjModel("OBJ/Plant.obj");
	environmentItem->Initialize(m_D3D->GetDevice(), m_D3D->GetDeviceContext(), { -5,0,6 }, 2.0f, L"Textures/green.png");
	environment.insert(environmentItem);

	environmentItem = new ObjModel("OBJ/Lamp.obj");
	environmentItem->Initialize(m_D3D->GetDevice(), m_D3D->GetDeviceContext(), { -4,0,1 }, 2.0f, L"Textures/pink.jpg");
	environment.insert(environmentItem);

	environmentItem = new ObjModel("OBJ/Cat.obj");
	environmentItem->Initialize(m_D3D->GetDevice(), m_D3D->GetDeviceContext(), { -80,0,0 }, 0.4f, L"Textures/grey.jpg");
	environment.insert(environmentItem);


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
bool KatamariGraphics::Render()
{
	SimpleMath::Matrix worldMatrix, viewMatrix, projectionMatrix;
	SimpleMath::Matrix tMat, rMat;
	bool result;

	RenderToTexture();

	// Reset the render target back to the original back buffer and not the render to texture anymore.
	m_D3D->SetBackBufferRenderTarget();

	// Reset the viewport back to the original.
	m_D3D->ResetViewport();

	// Clear the buffers to begin the scene.
	m_D3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	//Player->position.y = Player->sphereColision->Radius+ 0.3;
	m_Camera->SetPosition(Player->position.x - (10.0f * XMScalarSin(ballRot.y)), Player->position.y + 6.0f, Player->position.z - (10.0f*XMScalarCos(ballRot.y)));
	m_Camera->SetRotation(PI*30.0f/180.0f, ballRot.y, 0.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);

	Player->sphereColision->Center = Player->position;

	m_D3D->GetWorldMatrix(worldMatrix);
	tMat = worldMatrix.CreateTranslation(Player->position.x, Player->position.y, Player->position.z);
	rMat = worldMatrix.CreateRotationX(ballRot.x) * worldMatrix.CreateRotationY(ballRot.y);
	worldMatrix = rMat * tMat;
	Player->worldMatrix = worldMatrix;

	for (auto model : environment)
	{
		if (Player->sphereColision->Intersects(*model->sphereColision))
		{
			if (Player->sphereColision->Radius > model->sphereColision->Radius)
			{
				float temp = Player->sphereColision->Radius;
				model->sphereColision->Radius /= 3;
				Player->sphereColision->CreateMerged(*Player->sphereColision, *Player->sphereColision, *model->sphereColision);
				/*model->sphereColision->Radius = temp;
				model->rotation = ballRot;*/
				model->worldMatrix = Player->worldMatrix.Invert();
				attachment.push_back(model);
				environment.erase(model);
				break;
			}
		}
	}

	//Render

	Player->Render(m_D3D->GetDeviceContext());
	// Render the model using the color shader.
	result = m_ColorShader->Render(m_D3D->GetDeviceContext(), Player->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, 
		Player->GetTexture(), Player->GetMaterial().ambientColor, Player->GetMaterial().diffuseColor, 
		Player->GetMaterial().specularColor, Player->GetMaterial().specularPower, _light->GetDirection(), m_Camera->GetDirection(),
		_light->GetViewMatrix(), _light->GetProjMatrix(), m_renderTexture->GetShaderResourceView());

	m_D3D->GetWorldMatrix(worldMatrix);
	floor->Render(m_D3D->GetDeviceContext());
	result = m_ColorShader->Render(m_D3D->GetDeviceContext(), floor->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		floor->GetTexture(), floor->GetMaterial().ambientColor, floor->GetMaterial().diffuseColor,
		floor->GetMaterial().specularColor, floor->GetMaterial().specularPower, _light->GetDirection(), m_Camera->GetDirection(),
		_light->GetViewMatrix(), _light->GetProjMatrix(), m_renderTexture->GetShaderResourceView());

	for (auto model : attachment)
	{
		m_D3D->GetWorldMatrix(worldMatrix);

		worldMatrix = model->worldMatrix * Player->worldMatrix;
		model->Render(m_D3D->GetDeviceContext());
		// Render the model using the color shader.
		result = m_ColorShader->Render(m_D3D->GetDeviceContext(), model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, 
			model->GetTexture(), model->GetMaterial().ambientColor, model->GetMaterial().diffuseColor,
			model->GetMaterial().specularColor, model->GetMaterial().specularPower, _light->GetDirection(),
			m_Camera->GetDirection(), _light->GetViewMatrix(), _light->GetProjMatrix(), m_renderTexture->GetShaderResourceView());

	}

	for (auto model : environment)
	{
		worldMatrix = worldMatrix.Identity;

		model->Render(m_D3D->GetDeviceContext());
		// Render the model using the color shader.
		result = m_ColorShader->Render(m_D3D->GetDeviceContext(), model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
			model->GetTexture(), model->GetMaterial().ambientColor, model->GetMaterial().diffuseColor,
			model->GetMaterial().specularColor, model->GetMaterial().specularPower, _light->GetDirection(), m_Camera->GetDirection(),
			_light->GetViewMatrix(), _light->GetProjMatrix(), m_renderTexture->GetShaderResourceView());
	}

	// Present the rendered scene to the screen.

	m_D3D->EndScene();

	return true;
}

void KatamariGraphics::SetPosOfModels(DirectX::SimpleMath::Vector3 pos, DirectX::SimpleMath::Vector3 rot)
{
	Player->position = pos;
	ballRot = rot*PI/180.0;
}

void KatamariGraphics::RenderToTexture()
{
	SimpleMath::Matrix tMat, rMat, worldMatrix;

	// Set the render target to be the render to texture.
	m_renderTexture->SetRenderTarget(m_D3D->GetDeviceContext());

	// Clear the render to texture.
	m_renderTexture->ClearRenderTarget(m_D3D->GetDeviceContext(), 0.0f, 0.0f, 0.0f, 1.0f);

	Player->position.y = Player->sphereColision->Radius + 0.3;

	m_D3D->GetWorldMatrix(worldMatrix);
	tMat = worldMatrix.CreateTranslation(Player->position.x, Player->position.y, Player->position.z);
	rMat = worldMatrix.CreateRotationX(ballRot.x) * worldMatrix.CreateRotationY(ballRot.y);
	worldMatrix = rMat * tMat;
	Player->worldMatrix = worldMatrix;

	Player->Render(m_D3D->GetDeviceContext());
	//m_ColorShader->RenderToDepth(m_D3D->GetDeviceContext(), Player->GetIndexCount(), Player->worldMatrix, _light->GetViewMatrix(), _light->GetProjMatrix());
	m_depthShader->Render(m_D3D->GetDeviceContext(), Player->GetIndexCount(), Player->worldMatrix, _light->GetViewMatrix(), _light->GetProjMatrix());


	for (auto model : environment)
	{
		/*model->Render(m_D3D->GetDeviceContext());
		m_ColorShader->RenderToDepth(m_D3D->GetDeviceContext(), model->GetIndexCount(), Matrix::Identity, _light->GetViewMatrix(), _light->GetProjMatrix());
		*/
		model->Render(m_D3D->GetDeviceContext());
		m_depthShader->Render(m_D3D->GetDeviceContext(), model->GetIndexCount(), Matrix::Identity, _light->GetViewMatrix(), _light->GetProjMatrix());
	}

	for (auto model : attachment)
	{
		m_D3D->GetWorldMatrix(worldMatrix);

		worldMatrix = model->worldMatrix * Player->worldMatrix;
		model->Render(m_D3D->GetDeviceContext());
		//m_ColorShader->RenderToDepth(m_D3D->GetDeviceContext(), model->GetIndexCount(), Matrix::Identity, _light->GetViewMatrix(), _light->GetProjMatrix());
		m_depthShader->Render(m_D3D->GetDeviceContext(), model->GetIndexCount(), worldMatrix, _light->GetViewMatrix(), _light->GetProjMatrix());
	}


	m_D3D->GetWorldMatrix(worldMatrix);
	tMat = worldMatrix.CreateTranslation(Player->position.x, Player->position.y, Player->position.z);
	rMat = worldMatrix.CreateRotationX(ballRot.x) * worldMatrix.CreateRotationY(ballRot.y);
	worldMatrix = rMat * tMat;
	Player->worldMatrix = worldMatrix;

	Player->Render(m_D3D->GetDeviceContext());
	//m_ColorShader->RenderToDepth(m_D3D->GetDeviceContext(), Player->GetIndexCount(), Player->worldMatrix, _light->GetViewMatrix(), _light->GetProjMatrix());
	m_depthShader->Render(m_D3D->GetDeviceContext(), Player->GetIndexCount(), Player->worldMatrix, _light->GetViewMatrix(), _light->GetProjMatrix());

	floor->Render(m_D3D->GetDeviceContext());
	m_depthShader->Render(m_D3D->GetDeviceContext(), floor->GetIndexCount(), Matrix::Identity, _light->GetViewMatrix(), _light->GetProjMatrix());
}
	//m_ColorShader->RenderToDepth(m_D3D->GetDeviceContext(), floor->GetIndexCount(), Matrix::Identity, _light->GetViewMatrix(), _light->GetProjMatrix());
