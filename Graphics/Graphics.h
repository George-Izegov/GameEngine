

#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

#include <windows.h>
#include"d3dclass.h"

#include "../ActorsCore/Camera.h"
#include "../ActorsCore/Light.h"
#include "Colorshaderclass.h"
#include "depthshaderclass.h"
#include "rendertextureclass.h"
#include "../ActorsCore/MeshOBJ.h"
#include <vector>


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

	void SetCameraTransform(Vector3 deltaPos, Vector3 deltaRot);
	Camera* GetCamera() { return m_Camera; }

protected:
	virtual bool Render();
	void RenderToTexture();

protected:
	D3DClass* m_D3D;
	Camera* m_Camera;
	Light* _light;
	ColorShaderClass* m_ColorShader;
	DepthShaderClass* m_depthShader;
	RenderTextureClass* m_renderTexture;
	vector<ObjModel*> models;
};

#endif
