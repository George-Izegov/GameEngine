#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <d3d11.h>
#include <directxmath.h>
#include "SimpleMath.h"
using namespace DirectX::SimpleMath;
using namespace DirectX;

class Camera
{
public:
	Camera();
	Camera(const Camera&);
	~Camera();

	void SetPosition(Vector3 newPos);
	void SetRotation(Vector3 newRot);

	Vector3 GetPosition();
	Vector3 GetRotation();

	void Render();
	void GetViewMatrix(Matrix&);
	Vector3 GetForwardVector();
	Vector3 GetRightVector();

private:
	Vector3 Position;
	Vector3 Rotation;
	Matrix m_viewMatrix;
};

#endif
