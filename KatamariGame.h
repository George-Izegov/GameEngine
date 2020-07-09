#pragma once

#include "Game.h"
#include "KatamariGraphics.h"

#include <Windows.h>
#include <iostream>



class KatamariGame : public Game
{
public:
	KatamariGame();
	bool Initialize();
	bool Frame();

	KatamariGraphics* _Graphics;

private:
	DirectX::SimpleMath::Vector3 playerPos;
	DirectX::SimpleMath::Vector3 playerRot;
	float speed;
	float rotSpeed;

private:

};