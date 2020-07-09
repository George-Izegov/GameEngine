
#ifndef _GAME_H_
#define _GAME_H_

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include "Graphics.h"
#include "Input.h"
#include <ctime>
#include <time.h>
#include <iostream>

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

	void StartCounter()
	{
		LARGE_INTEGER li;
		if (!QueryPerformanceFrequency(&li))
			std::cout << "QueryPerformanceFrequency failed!\n";
		PCFreq = double(li.QuadPart);

		QueryPerformanceCounter(&li);
		CounterStart = li.QuadPart;
	}
	double GetCounter()
	{
		LARGE_INTEGER li;
		QueryPerformanceCounter(&li);
		return double(li.QuadPart - CounterStart) / PCFreq;
	}

protected:
	LPCWSTR m_applicationName;
	HINSTANCE m_hinstance;
	HWND m_hwnd;

	Input* m_Input;
	Graphics* m_Graphics;

	double PCFreq = 0.0;
	__int64 CounterStart = 0;

	double dt;

};

static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
static Game* ApplicationHandle = 0;

#endif