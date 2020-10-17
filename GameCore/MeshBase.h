#ifndef _MODEL_H_
#define _MODEL_H_

#include <d3d11.h>
#include <directxmath.h>
#include "SimpleMath.h"
#include "WICTextureLoader.h"
#include "../ActorsCore/Material.h"


using namespace DirectX;


class Mesh
{
 protected:

	struct VertexType
	{
		DirectX::SimpleMath::Vector3 position;
		DirectX::SimpleMath::Vector2 texPos;
		DirectX::SimpleMath::Vector3 normal;
	};

public:
	Mesh();
	Mesh(const Mesh&);
	~Mesh();

	bool Initialize(ID3D11Device*, ID3D11DeviceContext*, DirectX::SimpleMath::Vector3, float, const wchar_t*);
	void Shutdown();
	void Render(ID3D11DeviceContext*);

	int GetIndexCount();

	ID3D11ShaderResourceView* GetTexture() { return m_textureView; }
	Material GetMaterial() { return _mat; }

protected:
	virtual bool InitializeBuffers(ID3D11Device*, DirectX::SimpleMath::Vector3, float);
	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext*);
	bool InitializeTexture(ID3D11Device*, ID3D11DeviceContext*, const wchar_t*);

protected:
	ID3D11Buffer* m_vertexBuffer, * m_indexBuffer;
	long long m_vertexCount, m_indexCount;
	ID3D11ShaderResourceView* m_textureView;
	Material _mat;
};

#endif