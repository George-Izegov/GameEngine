#include "Light.h"
#include <iostream>

Vector3 Light::GetDirection()
{
	direction.Normalize();
	return direction;

}

Vector3 Light::GetIntencity()
{
	return intencity;
}

void Light::Init(ID3D11Device* device)
{
	position = -50 * GetDirection();
	m_viewMatrix = Matrix::CreateLookAt(position, Vector3::Zero, Vector3::Up);

	float fieldOfView, screenAspect;


	// Setup field of view and screen aspect for a square light source.
	fieldOfView = (float)3.14 / 2;
	screenAspect = 1.0f;

	// Create the projection matrix for the light.
	//m_projMatrix = Matrix::CreatePerspectiveFieldOfView(fieldOfView, screenAspect, 1.0f, 100.0f);
	m_projMatrix = Matrix::CreateOrthographic(128, 128, 1.0f, 100.0f);
}

void Light::Draw(ID3D11DeviceContext* deviceContext)
{
}
