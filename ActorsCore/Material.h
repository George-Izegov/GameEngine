#pragma once

#include "SimpleMath.h"

using namespace DirectX::SimpleMath;

struct Material
{
	Vector4 ambientColor;
	Vector4 diffuseColor;
	Vector4 specularColor;
	float specularPower;
};

static Material M_Silver = { { 0.23,0.23,0.23, 1.0f }, { 0.28,0.28,0.28, 1.0f }, { 0.77, 0.77, 0.77, 1.0f }, 90.f };
static Material M_Plastic = { { 0.5, 0.5, 0.5, 1.0f}, { 0.01, 0.01, 0.01, 1.0f }, { 0.5, 0.5, 0.5, 1.0f }, 32.f };
static Material M_Brass = { { 0.33, 0.22, 0.03, 1.0f}, { 0.78, 0.57, 0.11, 1.0f }, { 0.99, 0.84, 0.81, 1.0f }, 28.f };
static Material M_Wood = { { 0.2, 0.2, 0.2, 1.0f}, { 0.7, 0.7, 0.7, 1.0f }, { 0.05, 0.05, 0.05, 1.0f }, 32.f };
static Material M_Simple = { { 1, 1, 1, 1.0f}, { 0.0, 0.0, 0.0, 1.0f }, { 0.00, 0.00, 0.00, 1.0f }, 1.f };


