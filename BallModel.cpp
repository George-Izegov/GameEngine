#include "BallModel.h"


bool Ball::InitializeBuffers(ID3D11Device* device, DirectX::SimpleMath::Vector3 pos, float scale)
{
	VertexType* vertices;
	unsigned long* indices;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;

	// Set the number of vertices in the vertex array.
	m_vertexCount = 13;

	// Set the number of indices in the index array.
	m_indexCount = 36;

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
	for (int i = 0; i < 12; i++)
	{
		vertices[i].position = DirectX::SimpleMath::Vector3(1.0f*DirectX::XMScalarCos(30.0*i/180.0*PI),
			1.0f * DirectX::XMScalarSin(30.0 * i / 180.0 * PI), -1.0f);

		
	}



	vertices[12].position = DirectX::SimpleMath::Vector3(0, 0, -1.0f);

	for (int i = 0; i < m_vertexCount; i++)
	{
		vertices[i].position = vertices[i].position * (scale / 2.0) + pos;
		vertices[i].texPos = DirectX::SimpleMath::Vector2(0.5f * DirectX::XMScalarCos(30.0 * i / 180.0 * PI)+0.5f,
			0.5f * DirectX::XMScalarSin(30.0 * i / 180.0 * PI)+0.5f);
	}

	// Load the index array with data.
	int k = 0;
	for (int i = 0; i < m_indexCount; i++)
	{
		if (i % 3 == 0)
		{
			indices[i] = 12;
		}

		if (i % 3 == 1)
		{
			indices[i] = k;
		}

		if (i % 3 == 2)
		{
			indices[i] = k+ 1;
			k++;
			if (i == 35)
			{
				indices[i] = 0;
			}
		}
	}
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