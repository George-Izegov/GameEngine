#pragma once

#include "d3d11.h"
#include "SimpleMath.h"
#include <set>

using namespace DirectX::SimpleMath;

class Light
{

	DirectX::SimpleMath::Matrix ViewProjMatrix;

public:
	ID3D11ShaderResourceView* DepthShaderView;

	const int ShadowMapSize = 3000;

public:
	Light()
	{
		direction = { 0.5, -0.8, 0.5};
		intencity = { 1, 1, 1 };
		DepthShaderView = 0;
	}

	Light(Vector3 dir, Vector3 I) :
		direction(dir), intencity(I)
	{}

	Vector3 GetDirection();
	Vector3 GetIntencity();

	DirectX::SimpleMath::Matrix GetViewMatrix() { return m_viewMatrix; }

	DirectX::SimpleMath::Matrix GetProjMatrix() { return m_projMatrix; }

	void Init(ID3D11Device*);

	void Draw(ID3D11DeviceContext* deviceContext);


private:
	Vector3 direction;
	Vector3 intencity;
	Vector3 position;
	Matrix m_viewMatrix;
	Matrix m_projMatrix;
};