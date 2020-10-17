#include "Game.h"
#include <iostream>

Game::Game()
{
	m_Input = 0;
	m_Graphics = 0;
}

Game::Game(const Game& other)
{
}

Game::~Game()
{
}

bool Game::Initialize()
{
	int screenWidth, screenHeight;
	bool result;

	// Initialize the width and height of the screen to zero before sending the variables into the function.
	screenWidth = 0;
	screenHeight = 0;

	// Initialize the windows api.
	InitializeWindows(screenWidth, screenHeight);

	// Create the input object.  This object will be used to handle reading the keyboard input from the user.
	m_Input = new Input;
	if (!m_Input)
	{
		return false;
	}

	// Initialize the input object.
	m_Input->Initialize();

	// Create the graphics object.  This object will handle rendering all the graphics for this application.
	m_Graphics = new Graphics;
	if (!m_Graphics)
	{
		return false;
	}

	// Initialize the graphics object.
	result = m_Graphics->Initialize(screenWidth, screenHeight, m_hwnd);
	if (!result)
	{
		return false;
	}

	SetCursorToCenter();

	return true;
}

void Game::Shutdown()
{
	// Release the graphics object.
	if (m_Graphics)
	{
		m_Graphics->Shutdown();
		delete m_Graphics;
		m_Graphics = 0;
	}

	// Release the input object.
	if (m_Input)
	{
		delete m_Input;
		m_Input = 0;
	}

	// Shutdown the window.
	ShutdownWindows();

	return;
}

void Game::Run()
{
	MSG msg;
	bool done, result;


	// Initialize the message structure.
	ZeroMemory(&msg, sizeof(MSG));

	// Loop until there is a quit message from the window or the user.
	done = false;
	while (!done)
	{
		// Handle the windows messages.
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		// If windows signals to end the application then exit out.
		if (msg.message == WM_QUIT)
		{
			done = true;
		}
		else
		{
			// Otherwise do the frame processing.
			result = this->Frame();
			if (!result)
			{
				done = true;
			}
		}

	}

	return;

}

bool Game::Frame()
{
	bool result;

	// track mouse cursor
	if (m_Input)
	{
		prevMousePosition = m_Input->MousePosition;
		GetCursorPos(&m_Input->MousePosition);

		m_Input->MouseDelta = GetMouseDelta();
		SetCursorToCenter();

		ShowCursor(false);
	}

	Camera* camera = m_Graphics->GetCamera();

	DirectX::SimpleMath::Vector3 dCameraPos;
	DirectX::SimpleMath::Vector3 dCameraRot;
	float yRot = camera->GetRotation().y;
	float speed = 3.0f;
	float rotSpeed = 0.003f;

	dt = GetCounter();
	StartCounter();

	// Check if the user pressed escape and wants to exit the application.
	if (m_Input->IsKeyDown(27)) // ESC key
	{
		return false;
	}

	if (m_Input->IsKeyDown(68)) //d key
	{
		dCameraPos += camera->GetRightVector() * speed * dt;
	}

	if (m_Input->IsKeyDown(65)) //a key
	{
		dCameraPos -= camera->GetRightVector() * speed * dt;
	}

	if (m_Input->IsKeyDown(87)) //w key
	{
		dCameraPos += camera->GetForwardVector() * speed * dt;
	}

	if (m_Input->IsKeyDown(83)) //s key
	{
		dCameraPos -= camera->GetForwardVector() * speed * dt;
	}

	if (m_Input->IsKeyDown(32)) //space key
	{

	}

	{
		float deltaXMouse = m_Input->MouseDelta.x;
		float deltaYMouse = m_Input->MouseDelta.y;

		if( dt < INFINITY )
			dCameraRot += {static_cast<float>(rotSpeed* deltaYMouse), static_cast<float>(rotSpeed * deltaXMouse) * -1, 0.0f};
	}

	m_Graphics->SetCameraTransform(dCameraPos, dCameraRot);
	// Do the frame processing for the graphics object.
	result = m_Graphics->Frame();
	if (!result)
	{
		return false;
	}

	return true;
}

LRESULT CALLBACK Game::MessageHandler(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam)
{
	switch (umsg)
	{
		// Check if a key has been pressed on the keyboard.
	case WM_KEYDOWN:
	{
		// If a key is pressed send it to the input object so it can record that state.
		m_Input->KeyDown((unsigned int)wparam);
		return 0;
	}

	// Check if a key has been released on the keyboard.
	case WM_KEYUP:
	{
		// If a key is released then send it to the input object so it can unset the state for that key.
		m_Input->KeyUp((unsigned int)wparam);
		return 0;
	}

	// Any other messages send to the default message handler as our application won't make use of them.
	default:
	{
		return DefWindowProc(hwnd, umsg, wparam, lparam);
	}
	}
}

void Game::InitializeWindows(int& screenWidth, int& screenHeight)
{
	WNDCLASSEX wc;
	DEVMODE dmScreenSettings;
	int posX, posY;


	// Get an external pointer to this object.
	ApplicationHandle = this;

	// Get the instance of this application.
	m_hinstance = GetModuleHandle(NULL);

	// Give the application a name.
	m_applicationName = L"Game";

	// Setup the windows class with default settings.
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = m_hinstance;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hIconSm = wc.hIcon;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = m_applicationName;
	wc.cbSize = sizeof(WNDCLASSEX);

	// Register the window class.
	RegisterClassEx(&wc);

	// Determine the resolution of the clients desktop screen.
	screenWidth = GetSystemMetrics(SM_CXSCREEN);
	screenHeight = GetSystemMetrics(SM_CYSCREEN);

	// Setup the screen settings depending on whether it is running in full screen or in windowed mode.
	if (FULL_SCREEN)
	{
		// If full screen set the screen to maximum size of the users desktop and 32bit.
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth = (unsigned long)screenWidth;
		dmScreenSettings.dmPelsHeight = (unsigned long)screenHeight;
		dmScreenSettings.dmBitsPerPel = 32;
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		// Change the display settings to full screen.
		ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);

		// Set the position of the window to the top left corner.
		posX = posY = 0;
	}
	else
	{
		// If windowed then set it to 800x800 resolution.
		screenWidth = 800;
		screenHeight = 600;

		// Place the window in the middle of the screen.
		posX = (GetSystemMetrics(SM_CXSCREEN) - screenWidth) / 2;
		posY = (GetSystemMetrics(SM_CYSCREEN) - screenHeight) / 2;
	}

	// Create the window with the screen settings and get the handle to it.
	m_hwnd = CreateWindowEx(WS_EX_APPWINDOW, m_applicationName, m_applicationName,
		WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP,
		posX, posY, screenWidth, screenHeight, NULL, NULL, m_hinstance, NULL);

	// Bring the window up on the screen and set it as main focus.
	ShowWindow(m_hwnd, SW_SHOW);
	SetForegroundWindow(m_hwnd);
	SetFocus(m_hwnd);

	// Hide the mouse cursor.
	ShowCursor(true);

	return;
}

void Game::ShutdownWindows()
{
	// Show the mouse cursor.
	ShowCursor(true);

	// Fix the display settings if leaving full screen mode.
	if (FULL_SCREEN)
	{
		ChangeDisplaySettings(NULL, 0);
	}

	// Remove the window.
	DestroyWindow(m_hwnd);
	m_hwnd = NULL;

	// Remove the application instance.
	UnregisterClass(m_applicationName, m_hinstance);
	m_hinstance = NULL;

	// Release the pointer to this class.
	ApplicationHandle = NULL;

	return;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam)
{
	switch (umessage)
	{
		// Check if the window is being destroyed.
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	}

	// Check if the window is being closed.
	case WM_CLOSE:
	{
		PostQuitMessage(0);
		return 0;
	}

	// All other messages pass to the message handler in the system class.
	default:
	{
		return ApplicationHandle->MessageHandler(hwnd, umessage, wparam, lparam);
	}
	}
}

// Get the horizontal and vertical screen sizes in pixel
void GetDesktopResolution(int& horizontal, int& vertical)
{
	RECT desktop;
	// Get a handle to the desktop window
	const HWND hDesktop = GetDesktopWindow();
	// Get the size of screen to the variable desktop
	GetWindowRect(hDesktop, &desktop);
	// The top left corner will have coordinates (0,0)
	// and the bottom right corner will have coordinates
	// (horizontal, vertical)
	horizontal = desktop.right;
	vertical = desktop.bottom;
}


void Game::SetCursorToCenter()
{
	int x, y;
	GetDesktopResolution(x, y);

	x /= 2;
	y /= 2;

	SetCursorPos(x, y);
}

POINT Game::GetMouseDelta()
{
	int x, y;
	GetDesktopResolution(x, y);
	x /= 2;
	y /= 2;

	POINT delta, curPos;

	GetCursorPos(&curPos);

	delta.x = curPos.x - x;
	delta.y = curPos.y - y;

	return delta;
}
