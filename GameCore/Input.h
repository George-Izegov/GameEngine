

#ifndef _INPUT_H_
#define _INPUT_H_

#include <windows.h>

class Input
{
public:
	Input();
	Input(const Input&);
	~Input();

	void Initialize();

	void KeyDown(unsigned int);
	void KeyUp(unsigned int);

	bool IsKeyDown(unsigned int);

public:
	POINT MousePosition;
	// сдвиг позиции мыши по сравнению с предыдущим фреймом
	POINT MouseDelta;
private:
	bool m_keys[256];
};

#endif