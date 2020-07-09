#include "OrbitCubesGraphics.h"

OrbitCubesGraphics::OrbitCubesGraphics()
{
	m_D3D = 0;
	m_Camera = 0;
	m_ColorShader = 0;

	for (int i = 0; i < 10; i++)
	{
		selfAngle[i] = i * 0.3f;
		uniAngle[i] = i * 0.3f;
		radius[i] = 3 + 2 * i;
	}


}

bool OrbitCubesGraphics::Initialize(int screenWidth, int screenHeight, HWND hwnd)
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

	for (int i = 0; i < 10; i++)
	{
		Model* m_model = new Model;
		models.push_back(m_model);

	}
	// Create the model object.

	// Initialize the model object.
	models.at(0)->Initialize(m_D3D->GetDevice(), m_D3D->GetDeviceContext(), { 1,0,0 }, 1.0f, L"");
	models.at(1)->Initialize(m_D3D->GetDevice(), m_D3D->GetDeviceContext(), { 0,0,0 }, 0.5f, L"");
	models.at(2)->Initialize(m_D3D->GetDevice(), m_D3D->GetDeviceContext(), { 0,1,0 }, 1.3f, L"");
	models.at(3)->Initialize(m_D3D->GetDevice(), m_D3D->GetDeviceContext(), { 0,0,2 }, 2.0f, L"");
	models.at(4)->Initialize(m_D3D->GetDevice(), m_D3D->GetDeviceContext(), { 0,0,0 }, 1.0f, L"");
	models.at(5)->Initialize(m_D3D->GetDevice(), m_D3D->GetDeviceContext(), { 0,0,0 }, 2.5f, L"");
	models.at(6)->Initialize(m_D3D->GetDevice(), m_D3D->GetDeviceContext(), { 0,-1,0 }, 1.0f, L"");
	models.at(7)->Initialize(m_D3D->GetDevice(), m_D3D->GetDeviceContext(), { 0,0,0 }, 2.0f, L"");
	models.at(8)->Initialize(m_D3D->GetDevice(), m_D3D->GetDeviceContext(), { 0,0,0 }, 1.0f, L"");
	models.at(9)->Initialize(m_D3D->GetDevice(), m_D3D->GetDeviceContext(), { 0,0,0 }, 0.5f, L"");

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

bool OrbitCubesGraphics::Render()
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
		DirectX::SimpleMath::Matrix rMat;
		DirectX::SimpleMath::Matrix tMat;
		i++;
		uniAngle[i] += 0.05 + 0.011 * i - 0.02 * (i % 5);
		rMat = worldMatrix.CreateRotationY(selfAngle[i] += (0.2 + 0.01 * (i % 4)));
		tMat = worldMatrix.CreateTranslation(radius[i] * XMScalarCos(uniAngle[i]), 0, radius[i] * XMScalarSin(uniAngle[i]));
		worldMatrix = rMat * tMat;
		// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
		model->Render(m_D3D->GetDeviceContext());
		// Render the model using the color shader.
		result = m_ColorShader->Render(m_D3D->GetDeviceContext(), model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, model->GetTexture());

	}

	// Present the rendered scene to the screen.
	m_D3D->EndScene();

	return true;
}
