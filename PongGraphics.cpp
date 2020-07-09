#include "PongGraphics.h"

PongGraphics::PongGraphics()
{
	_ball = 0;
	_plat1 = 0;
	_plat2 = 0;
}
bool PongGraphics::Initialize(int screenWidth, int screenHeight, HWND hwnd)
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

	 _ball = new Ball;
	 _plat1 = new Platform;
	 _plat2 = new Platform;
	// Create the model object.


	// Initialize the model object.
	_ball->Initialize(m_D3D->GetDevice(), m_D3D->GetDeviceContext(), { 0,0,0}, 0.3f, L"m.png");
	_plat1->Initialize(m_D3D->GetDevice(), m_D3D->GetDeviceContext(), { 0,-1.5,0 }, 1.0f, L"tex.jpg");
	_plat2->Initialize(m_D3D->GetDevice(), m_D3D->GetDeviceContext(), { 0,1.5,0 }, 1.0f, L"tex.jpg");


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
bool PongGraphics::Render()
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

	//ball render
	m_D3D->GetWorldMatrix(worldMatrix);
	worldMatrix = worldMatrix.CreateTranslation(_ballPos.x, _ballPos.y, 0);
	_ball->Render(m_D3D->GetDeviceContext());
	result = m_ColorShader->Render(m_D3D->GetDeviceContext(), _ball->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, _ball->GetTexture());
	//platform1 render
	m_D3D->GetWorldMatrix(worldMatrix);
	worldMatrix = worldMatrix.CreateTranslation(platform1Pos, 0, 0);
	_plat1->Render(m_D3D->GetDeviceContext());
	result = m_ColorShader->Render(m_D3D->GetDeviceContext(), _plat1->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, _plat1->GetTexture());
	//platform2 render
	m_D3D->GetWorldMatrix(worldMatrix);
	worldMatrix = worldMatrix.CreateTranslation(platform2Pos, 0, 0);
	_plat2->Render(m_D3D->GetDeviceContext());
	result = m_ColorShader->Render(m_D3D->GetDeviceContext(), _plat2->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, _plat2->GetTexture());
	// Present the rendered scene to the screen.

	m_D3D->EndScene();

	return true;
}

void PongGraphics::SetPosOfModels(float pl1Pos, float pl2Pos, DirectX::SimpleMath::Vector2 ballPos)
{
	platform1Pos = pl1Pos;
	platform2Pos = pl2Pos;
	_ballPos = ballPos;
}