

#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

#include <windows.h>
#include"d3dclass.h"

#include "Camera.h"
#include "Model.h"
#include "Colorshaderclass.h"
#include <vector>
#include "ObjModel.h"



const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;


class Graphics
{
public:
	Graphics();
	Graphics(const Graphics&);
	~Graphics();

	bool Initialize(int, int, HWND);
	void Shutdown();
	bool Frame();
	void GoCameraForward(int);
	void RotateCameraToRight(int);
	void RotateCameraToUp(int);

protected:
	virtual bool Render();

protected:
	D3DClass* m_D3D;
	Camera* m_Camera;
	ColorShaderClass* m_ColorShader;
	vector<ObjModel*> models;
};

#endif
