#pragma once

#include "Graphics.h"
#include <set>
#include "Light.h"
#include "PlatformModel.h"
#include "depthshaderclass.h"
#include "rendertextureclass.h"

#define PI 3.14159265358979323846

class KatamariGraphics : public Graphics
{
public:

	KatamariGraphics();
	bool Initialize(int, int, HWND);
	bool Render();
	void SetPosOfModels(DirectX::SimpleMath::Vector3, DirectX::SimpleMath::Vector3);

	std::set<ObjModel*> environment;

private:
	ObjModel* Player;
	Square* floor;
	Light* _light;
	vector<ObjModel*> attachment;
	DirectX::SimpleMath::Vector3 ballPos;
	DirectX::SimpleMath::Vector3 ballRot; //in radians

	DepthShaderClass* m_depthShader;
	RenderTextureClass* m_renderTexture;

private:
	void RenderToTexture();
};
