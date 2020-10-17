
#ifndef _GAME_H_
#define _GAME_H_

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include "../Graphics/Graphics.h"
#include "Timer.h"
#include "Input.h"
#include <iostream>

#define PI 3.14159265358979323846

class Game
{
public:
	Game();
	Game(const Game&);
	~Game();

	bool Initialize();
	void Shutdown();
	void Run();
	LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);

protected:
	virtual bool Frame();
	void InitializeWindows(int&, int&);
	void ShutdownWindows();

	void SetCursorToCenter();
	POINT GetMouseDelta();

protected:
	LPCWSTR m_applicationName;
	HINSTANCE m_hinstance;
	HWND m_hwnd;

	Input* m_Input;
	Graphics* m_Graphics;

	Timer* m_Timer;

	double DeltaSeconds;

};

static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
static Game* ApplicationHandle = 0;

#endif