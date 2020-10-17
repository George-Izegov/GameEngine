#include "Camera.h"

Camera::Camera()
{
	Position = { 0,0,0 };
	Rotation = { 0,0,0 };
}


Camera::Camera(const Camera& other)
{
}


Camera::~Camera()
{
}

void Camera::SetPosition(Vector3 newPos)
{
	Position = newPos;
	return;
}


void Camera::SetRotation(Vector3 newRot)
{
	Rotation = newRot;
	return;
}

Vector3 Camera::GetPosition()
{
	return Position;
}


Vector3 Camera::GetRotation()
{
	return Rotation;
}

Vector3 Camera::GetForwardVector()
{
	return Vector3(XMScalarSin(GetRotation().y) * XMScalarCos(GetRotation().x),
		-1*XMScalarSin(GetRotation().x), 
		XMScalarCos(GetRotation().y) * XMScalarCos(GetRotation().x));
}

Vector3 Camera::GetRightVector()
{
	Vector3 resultVector;
	resultVector = Vector3(-1 * XMScalarCos(GetRotation().y) * XMScalarCos(GetRotation().x),
		0.0f,
		XMScalarSin(GetRotation().y) * XMScalarCos(GetRotation().x));

	resultVector.Normalize();

	return resultVector;
}

void Camera::Render()
{
	Vector3 up, position, lookAt;
	Vector3 upVector, positionVector, lookAtVector;
	float yaw, pitch, roll;
	Matrix rotationMatrix;


	// Setup the vector that points upwards.
	up.x = 0.0f;
	up.y = 1.0f;
	up.z = 0.0f;

	// Load it into a XMVECTOR structure.
	upVector = up;

	// Setup the position of the camera in the world.
	position = Position;

	// Load it into a XMVECTOR structure.
	positionVector = position;

	// Setup where the camera is looking by default.
	lookAt.x = 0.0f;
	lookAt.y = 0.0f;
	lookAt.z = 1.0f;

	// Load it into a XMVECTOR structure.
	lookAtVector = lookAt;

	// Set the yaw (Y axis), pitch (X axis), and roll (Z axis) rotations in radians.
	pitch = Rotation.x;
	yaw = Rotation.y;
	roll = Rotation.z;

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



