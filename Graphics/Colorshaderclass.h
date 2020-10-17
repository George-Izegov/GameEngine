#ifndef _COLORSHADERCLASS_H_
#define _COLORSHADERCLASS_H_

#pragma comment(lib, "d3dcompiler.lib")

#include <d3d11.h>
#include <d3dcompiler.h>
#include <directxmath.h>
#include <fstream>
#include "SimpleMath.h"
#include "../ActorsCore/Light.h"

using namespace DirectX;
using namespace std;

class ColorShaderClass
{
private:

	struct MatrixBufferType
	{
		DirectX::SimpleMath::Matrix world;
		DirectX::SimpleMath::Matrix view;
		DirectX::SimpleMath::Matrix projection;
		DirectX::SimpleMath::Matrix lightView;
		DirectX::SimpleMath::Matrix lightProjection;
	};

	struct LightBufferType
	{
		DirectX::SimpleMath::Vector4 ambientColor;
		DirectX::SimpleMath::Vector4 diffuseColor;
		DirectX::SimpleMath::Vector4 specularColor;
		DirectX::SimpleMath::Vector3 lightDirection;
		float specularPower;
		DirectX::SimpleMath::Vector3 cameraDirection;
		float padding;
	};

public:
	ColorShaderClass();
	ColorShaderClass(const ColorShaderClass&);
	~ColorShaderClass();

	bool Initialize(ID3D11Device*, HWND);
	void Shutdown();
	bool Render(ID3D11DeviceContext*, int, DirectX::SimpleMath::Matrix, DirectX::SimpleMath::Matrix, DirectX::SimpleMath::Matrix,
		ID3D11ShaderResourceView*, DirectX::SimpleMath::Vector4 aK, DirectX::SimpleMath::Vector4 dK, DirectX::SimpleMath::Vector4 sK,
		float sPow, DirectX::SimpleMath::Vector3 lDir, DirectX::SimpleMath::Vector3 cDir, DirectX::SimpleMath::Matrix lightViewMatrix,
		DirectX::SimpleMath::Matrix lightProjMatrix, ID3D11ShaderResourceView* depthMapTexture);
	bool Render(ID3D11DeviceContext*, int, DirectX::SimpleMath::Matrix, DirectX::SimpleMath::Matrix, DirectX::SimpleMath::Matrix,
		ID3D11ShaderResourceView*);

	void RenderToDepth(ID3D11DeviceContext* deviceContext, int indexCount, Matrix world, Matrix view, Matrix proj);

private:
	bool InitializeShader(ID3D11Device*, HWND,const wchar_t*,const wchar_t*);
	void ShutdownShader();
	void OutputShaderErrorMessage(ID3D10Blob*, HWND, WCHAR*);

	bool SetShaderParameters(ID3D11DeviceContext*, DirectX::SimpleMath::Matrix, DirectX::SimpleMath::Matrix, 
		DirectX::SimpleMath::Matrix, ID3D11ShaderResourceView* texture, DirectX::SimpleMath::Vector4 aK, DirectX::SimpleMath::Vector4 dK,
		DirectX::SimpleMath::Vector4 sK, float sPow, DirectX::SimpleMath::Vector3 lDir, DirectX::SimpleMath::Vector3 cDir, DirectX::SimpleMath::Matrix lightViewMatrix,
		DirectX::SimpleMath::Matrix lightProjMatrix, ID3D11ShaderResourceView* depthMapTexture);
	bool SetShaderParameters(ID3D11DeviceContext*, DirectX::SimpleMath::Matrix, DirectX::SimpleMath::Matrix,
		DirectX::SimpleMath::Matrix, ID3D11ShaderResourceView* texture);
	void RenderShader(ID3D11DeviceContext*, int);

private:
	ID3D11VertexShader* m_vertexShader;
	ID3D11PixelShader* m_pixelShader;
	ID3D11InputLayout* m_layout;
	ID3D11Buffer* m_matrixBuffer;
	ID3D11Buffer* m_lightBuffer;

	ID3D11SamplerState* m_sampleState;
	ID3D11SamplerState* m_sampleStateClamp;
};

#endif
