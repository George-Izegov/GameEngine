#include "Camera.h"

Camera::Camera()
{
	m_positionX = 0.0f;
	m_positionY = 0.0f;
	m_positionZ = 0.0f;

	m_rotationX = 0.0f;
	m_rotationY = 0.0f;
	m_rotationZ = 0.0f;
}


Camera::Camera(const Camera& other)
{
}


Camera::~Camera()
{
}

void Camera::SetPosition(float x, float y, float z)
{
	m_positionX = x;
	m_positionY = y;
	m_positionZ = z;
	return;
}


void Camera::SetRotation(float x, float y, float z)
{
	m_rotationX = x;
	m_rotationY = y;
	m_rotationZ = z;
	return;
}

DirectX::SimpleMath::Vector3 Camera::GetPosition()
{
	return DirectX::SimpleMath::Vector3(m_positionX, m_positionY, m_positionZ);
}


DirectX::SimpleMath::Vector3 Camera::GetRotation()
{
	return DirectX::SimpleMath::Vector3(m_rotationX, m_rotationY, m_rotationZ);
}

DirectX::SimpleMath::Vector3 Camera::GetDirection()
{
	return DirectX::SimpleMath::Vector3(XMScalarSin(GetRotation().y) * XMScalarCos(GetRotation().x),
		XMScalarSin(GetRotation().x), 
		XMScalarCos(GetRotation().y) * XMScalarCos(GetRotation().x));
}

void Camera::Render()
{
	DirectX::SimpleMath::Vector3 up, position, lookAt;
	DirectX::SimpleMath::Vector3 upVector, positionVector, lookAtVector;
	float yaw, pitch, roll;
	DirectX::SimpleMath::Matrix rotationMatrix;


	// Setup the vector that points upwards.
	up.x = 0.0f;
	up.y = 1.0f;
	up.z = 0.0f;

	// Load it into a XMVECTOR structure.
	upVector = up;

	// Setup the position of the camera in the world.
	position.x = m_positionX;
	position.y = m_positionY;
	position.z = m_positionZ;

	// Load it into a XMVECTOR structure.
	positionVector = position;

	// Setup where the camera is looking by default.
	lookAt.x = 0.0f;
	lookAt.y = 0.0f;
	lookAt.z = 1.0f;

	// Load it into a XMVECTOR structure.
	lookAtVector = lookAt;

	// Set the yaw (Y axis), pitch (X axis), and roll (Z axis) rotations in radians.
	pitch = m_rotationX;
	yaw = m_rotationY;
	roll = m_rotationZ;

	// Create the rotation matrix from the yaw, pitch, and roll values.
	rotationMatrix = rotationMatrix.CreateFromYawPitchRoll(yaw, pitch, roll);

	// Transform the lookAt and up vector by the rotation matrix so the view is correctly rotated at the origin.
	lookAtVector = lookAtVector.Transform(lookAtVector, rotationMatrix);
	upVector = upVector.Transform(upVector, rotationMatrix);

	// Translate the rotated camera position to the location of the viewer.
	lookAtVector += positionVector;

	// Finally create the view matrix from the three updated vectors.

	m_viewMatrix = m_viewMatrix.CreateLookAt(positionVector, lookAtVector, upVector);

	return;
}

void Camera::GetViewMatrix(DirectX::SimpleMath::Matrix& viewMatrix)
{
	viewMatrix = m_viewMatrix;
	return;
}



