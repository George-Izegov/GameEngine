#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <d3d11.h>
#include <directxmath.h>
#include "SimpleMath.h"
using namespace DirectX;


class Camera
{
public:
	Camera();
	Camera(const Camera&);
	~Camera();

	void SetPosition(float, float, float);
	void SetRotation(float, float, float);

	DirectX::SimpleMath::Vector3 GetPosition();
	DirectX::SimpleMath::Vector3 GetRotation();

	void Render();
	void GetViewMatrix(DirectX::SimpleMath::Matrix&);
	DirectX::SimpleMath::Vector3 GetDirection();

private:
	float m_positionX, m_positionY, m_positionZ;
	float m_rotationX, m_rotationY, m_rotationZ;
	DirectX::SimpleMath::Matrix m_viewMatrix;
};

#endif
