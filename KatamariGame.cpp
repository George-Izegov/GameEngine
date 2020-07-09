#include "KatamariGame.h"

KatamariGame::KatamariGame()
{
	dt = 0;
	_Graphics = 0;

	speed = 5.0f;
	rotSpeed = 45.0f;

	playerPos = { 0,0,0 };
	playerRot = { 0,0,0 };
	
}

bool KatamariGame::Initialize()
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
	_Graphics = new KatamariGraphics;
	if (!_Graphics)
	{
		return false;
	}

	// Initialize the graphics object.
	result = _Graphics->Initialize(screenWidth, screenHeight, m_hwnd);
	if (!result)
	{
		return false;
	}
	StartCounter();
	return true;
}

bool KatamariGame::Frame()
{
	bool result;
	dt = GetCounter();
	StartCounter();
	// Check if the user pressed escape and wants to exit the application.
	if (m_Input->IsKeyDown(27)) // ESC key
	{
		return false;
	}

	if (m_Input->IsKeyDown(68)) //d key
	{
		playerRot -= {0.0f, static_cast<float>(rotSpeed* dt), 0.0f};
	}

	if (m_Input->IsKeyDown(65)) //a key
	{
		playerRot += {0.0f, static_cast<float>(rotSpeed* dt), 0.0f};
	}

	if (m_Input->IsKeyDown(87)) //w key
	{
		playerPos += { static_cast<float>(XMScalarSin(playerRot.y* PI / 180.0f)* speed*dt), 0.0f, 
			static_cast<float>(XMScalarCos(playerRot.y* PI / 180.0f)* speed*dt)};
		playerRot += {static_cast<float>(rotSpeed* dt), 0.0f, 0.0f};
	}

	if (m_Input->IsKeyDown(83)) //s key
	{
		playerPos -= { static_cast<float>(XMScalarSin(playerRot.y* PI / 180.0f)* speed*dt), 0.0f, 
			static_cast<float>(XMScalarCos(playerRot.y* PI / 180.0f)* speed*dt)};
		playerRot -= {static_cast<float>(rotSpeed* dt), 0.0f, 0.0f};
	}

	if (m_Input->IsKeyDown(32)) //space key
	{

	}

	_Graphics->SetPosOfModels(playerPos, playerRot);
	// Do the frame processing for the graphics object.
	result = _Graphics->Frame();
	if (!result)
	{
		return false;
	}

	return true;
}
