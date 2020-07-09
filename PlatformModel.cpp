#include "PlatformModel.h"


bool Platform::InitializeBuffers(ID3D11Device* device, DirectX::SimpleMath::Vector3 pos, float scale)
{
VertexType* vertices;
unsigned long* indices;
D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
D3D11_SUBRESOURCE_DATA vertexData, indexData;
HRESULT result;

// Set the number of vertices in the vertex array.
m_vertexCount = 4;

// Set the number of indices in the index array.
m_indexCount = 6;

// Create the vertex array.
vertices = new VertexType[m_vertexCount];
if (!vertices)
{
	return false;
}

// Create the index array.
indices = new unsigned long[m_indexCount];
if (!indices)
{
	return false;
}

// Load the vertex array with data. 
vertices[0].position = DirectX::SimpleMath::Vector3(1.0f, 0.2f, -1.0f);
vertices[0].texPos = DirectX::SimpleMath::Vector2(1.0f, 1.0f);

vertices[1].position = DirectX::SimpleMath::Vector3(-1.0f, -0.2f, -1.0f);
vertices[1].texPos = DirectX::SimpleMath::Vector2(1.0f, 0.0f);

vertices[2].position = DirectX::SimpleMath::Vector3(1.0f, -0.2f, -1.0f);
vertices[2].texPos = DirectX::SimpleMath::Vector2(0.0f, 0.0f);

vertices[3].position = DirectX::SimpleMath::Vector3(-1.0f, 0.2f, -1.0f);
vertices[3].texPos = DirectX::SimpleMath::Vector2(0.0f, 1.0f);


for (int i = 0; i < m_vertexCount; i++)
{
	vertices[i].position = vertices[i].position * (scale / 2.0) + pos;
}

// Load the index array with data.
indices[0] = 0;
indices[1] = 1;
indices[2] = 2;
indices[3] = 1;
indices[4] = 0;
indices[5] = 3;


// Set up the description of the static vertex buffer.
vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
vertexBufferDesc.ByteWidth = sizeof(VertexType) * m_vertexCount;
vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
vertexBufferDesc.CPUAccessFlags = 0;
vertexBufferDesc.MiscFlags = 0;
vertexBufferDesc.StructureByteStride = 0;

// Give the subresource structure a pointer to the vertex data.
vertexData.pSysMem = vertices;
vertexData.SysMemPitch = 0;
vertexData.SysMemSlicePitch = 0;

// Now create the vertex buffer.
result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);
if (FAILED(result))
{
	return false;
}

// Set up the description of the static index buffer.
indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
indexBufferDesc.ByteWidth = sizeof(unsigned long) * m_indexCount;
indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
indexBufferDesc.CPUAccessFlags = 0;
indexBufferDesc.MiscFlags = 0;
indexBufferDesc.StructureByteStride = 0;

// Give the subresource structure a pointer to the index data.
indexData.pSysMem = indices;
indexData.SysMemPitch = 0;
indexData.SysMemSlicePitch = 0;

// Create the index buffer.
result = device->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer);
if (FAILED(result))
{
	return false;
}

// Release the arrays now that the vertex and index buffers have been created and loaded.
delete[] vertices;
vertices = 0;

delete[] indices;
indices = 0;

return true;

}

bool Square::InitializeBuffers(ID3D11Device* device, DirectX::SimpleMath::Vector3 pos, float scale)
{
	VertexType* vertices;
	unsigned long* indices;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;

	// Set the number of vertices in the vertex array.
	m_vertexCount = 4;

	// Set the number of indices in the index array.
	m_indexCount = 6;

	// Create the vertex array.
	vertices = new VertexType[m_vertexCount];
	if (!vertices)
	{
		return false;
	}

	// Create the index array.
	indices = new unsigned long[m_indexCount];
	if (!indices)
	{
		return false;
	}

	// Load the vertex array with data. 
	vertices[0].position = DirectX::SimpleMath::Vector3(1.0f, 0.0f, 1.0f);
	vertices[0].texPos = DirectX::SimpleMath::Vector2(1.0f, 1.0f);

	vertices[1].position = DirectX::SimpleMath::Vector3(-1.0f, 0.0f, -1.0f);
	vertices[1].texPos = DirectX::SimpleMath::Vector2(1.0f, 0.0f);

	vertices[2].position = DirectX::SimpleMath::Vector3(1.0f, 0.0f, -1.0f);
	vertices[2].texPos = DirectX::SimpleMath::Vector2(0.0f, 0.0f);

	vertices[3].position = DirectX::SimpleMath::Vector3(-1.0f, 0.0f, 1.0f);
	vertices[3].texPos = DirectX::SimpleMath::Vector2(0.0f, 1.0f);


	for (int i = 0; i < m_vertexCount; i++)
	{
		vertices[i].position = vertices[i].position * (scale / 2.0) + pos;
		vertices[i].texPos *= scale/5;
	}

	// Load the index array with data.
	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;
	indices[3] = 1;
	indices[4] = 0;
	indices[5] = 3;


	// Set up the description of the static vertex buffer.
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(VertexType) * m_vertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the vertex data.
	vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	// Now create the vertex buffer.
	result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);
	if (FAILED(result))
	{
		return false;
	}

	// Set up the description of the static index buffer.
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned long) * m_indexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the index data.
	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	// Create the index buffer.
	result = device->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer);
	if (FAILED(result))
	{
		return false;
	}

	// Release the arrays now that the vertex and index buffers have been created and loaded.
	delete[] vertices;
	vertices = 0;

	delete[] indices;
	indices = 0;

	return true;

}