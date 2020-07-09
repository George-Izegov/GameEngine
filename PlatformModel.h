#pragma once

#include "Model.h"

class Platform : public Model
{
public:
	bool InitializeBuffers(ID3D11Device* device, DirectX::SimpleMath::Vector3 pos, float scale);
};

class Square : public Model
{
public:

	Square(Material mat)
	{
		_mat = mat;
	}

	bool InitializeBuffers(ID3D11Device* device, DirectX::SimpleMath::Vector3 pos, float scale);
};