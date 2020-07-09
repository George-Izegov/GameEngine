#include "CubeModel.h"

bool CubeModel::InitializeBuffers(ID3D11Device* device, DirectX::SimpleMath::Vector3 pos, float scale)
{
	VertexType* vertices;
	unsigned long* indices;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;




	// Set the number of vertices in the vertex array.
	m_vertexCount = 24;

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
	vertices[0].position = DirectX::SimpleMath::Vector3(1.0f, 1.0f, -1.0f);
	//vertices[0].color = DirectX::SimpleMath::Vector4(0.5f, 0.0f, 0.0f, 1.0f);

	vertices[1].position = DirectX::SimpleMath::Vector3(-1.0f, -1.0f, -1.0f);
	//vertices[1].color = DirectX::SimpleMath::Vector4(0.5f, 0.0f, 0.0f, 1.0f);

	vertices[2].position = DirectX::SimpleMath::Vector3(1.0f, -1.0f, -1.0f);
	//vertices[2].color = DirectX::SimpleMath::Vector4(0.5f, 0.0f, 0.0f, 1.0f);

	vertices[3].position = DirectX::SimpleMath::Vector3(-1.0f, 1.0f, -1.0f);
	//vertices[3].color = DirectX::SimpleMath::Vector4(0.5f, 0.0f, 0.0f, 1.0f);

	vertices[4].position = DirectX::SimpleMath::Vector3(1.0f, 1.0f, 1.0f);
	//vertices[4].color = DirectX::SimpleMath::Vector4(0.5f, 0.0f, 0.5f, 1.0f);

	vertices[5].position = DirectX::SimpleMath::Vector3(-1.0f, -1.0f, 1.0f);
	//vertices[5].color = DirectX::SimpleMath::Vector4(0.5f, 0.0f, 0.5f, 1.0f);

	vertices[6].position = DirectX::SimpleMath::Vector3(1.0f, -1.0f, 1.0f);
	//vertices[6].color = DirectX::SimpleMath::Vector4(0.5f, 0.0f, 0.5f, 1.0f);

	vertices[7].position = DirectX::SimpleMath::Vector3(-1.0f, 1.0f, 1.0f);
	//vertices[7].color = DirectX::SimpleMath::Vector4(0.5f, 0.0f, 0.5f, 1.0f);

	vertices[8].position = DirectX::SimpleMath::Vector3(1.0f, 1.0f, -1.0f);
	//vertices[8].color = DirectX::SimpleMath::Vector4(0.5f, 0.5f, 0.0f, 1.0f);

	vertices[9].position = DirectX::SimpleMath::Vector3(-1.0f, -1.0f, -1.0f);
	//vertices[9].color = DirectX::SimpleMath::Vector4(0.0f, 0.5f, 0.5f, 1.0f);

	vertices[10].position = DirectX::SimpleMath::Vector3(1.0f, -1.0f, -1.0f);
	//vertices[10].color = DirectX::SimpleMath::Vector4(0.5f, 0.5f, 0.0f, 1.0f);

	vertices[11].position = DirectX::SimpleMath::Vector3(-1.0f, 1.0f, -1.0f);
	//vertices[11].color = DirectX::SimpleMath::Vector4(0.0f, 0.5f, 0.5f, 1.0f);

	vertices[12].position = DirectX::SimpleMath::Vector3(1.0f, 1.0f, 1.0f);
	//vertices[12].color = DirectX::SimpleMath::Vector4(0.5f, 0.5f, 0.0f, 1.0f);

	vertices[13].position = DirectX::SimpleMath::Vector3(-1.0f, -1.0f, 1.0f);
	//vertices[13].color = DirectX::SimpleMath::Vector4(0.0f, 0.5f, 0.5f, 1.0f);

	vertices[14].position = DirectX::SimpleMath::Vector3(1.0f, -1.0f, 1.0f);
	//vertices[14].color = DirectX::SimpleMath::Vector4(0.5f, 0.5f, 0.0f, 1.0f);

	vertices[15].position = DirectX::SimpleMath::Vector3(-1.0f, 1.0f, 1.0f);
	//vertices[15].color = DirectX::SimpleMath::Vector4(0.0f, 0.5f, 0.5f, 1.0f);

	vertices[16].position = DirectX::SimpleMath::Vector3(1.0f, 1.0f, -1.0f);
	//vertices[16].color = DirectX::SimpleMath::Vector4(0.0f, 0.5f, 0.0f, 1.0f);

	vertices[17].position = DirectX::SimpleMath::Vector3(-1.0f, 1.0f, 1.0f);
	//vertices[17].color = DirectX::SimpleMath::Vector4(0.0f, 0.5f, 0.0f, 1.0f);

	vertices[18].position = DirectX::SimpleMath::Vector3(1.0f, 1.0f, 1.0f);
	//vertices[18].color = DirectX::SimpleMath::Vector4(0.0f, 0.5f, 0.0f, 1.0f);

	vertices[19].position = DirectX::SimpleMath::Vector3(-1.0f, 1.0f, -1.0f);
	//vertices[19].color = DirectX::SimpleMath::Vector4(0.0f, 0.5f, 0.0f, 1.0f);

	vertices[20].position = DirectX::SimpleMath::Vector3(-1.0f, -1.0f, -1.0f);
	//vertices[20].color = DirectX::SimpleMath::Vector4(1.0f, 0.4f, 0.5f, 1.0f);

	vertices[21].position = DirectX::SimpleMath::Vector3(1.0f, -1.0f, -1.0f);
	//vertices[21].color = DirectX::SimpleMath::Vector4(1.0f, 0.4f, 0.5f, 1.0f);

	vertices[22].position = DirectX::SimpleMath::Vector3(-1.0f, -1.0f, 1.0f);
	//vertices[22].color = DirectX::SimpleMath::Vector4(1.0f, 0.4f, 0.5f, 1.0f);

	vertices[23].position = DirectX::SimpleMath::Vector3(1.0f, -1.0f, 1.0f);
	//vertices[23].color = DirectX::SimpleMath::Vector4(1.0f, 0.4f, 0.5f, 1.0f);

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
	indices[6] = 9;
	indices[7] = 11;
	indices[8] = 15;
	indices[9] = 15;
	indices[10] = 13;
	indices[11] = 9;
	indices[12] = 6;
	indices[13] = 5;
	indices[14] = 4;
	indices[15] = 7;
	indices[16] = 4;
	indices[17] = 5;
	indices[18] = 12;
	indices[19] = 8;
	indices[20] = 10;
	indices[21] = 14;
	indices[22] = 12;
	indices[23] = 10;
	indices[24] = 17;
	indices[25] = 19;
	indices[26] = 16;
	indices[27] = 18;
	indices[28] = 17;
	indices[29] = 16;
	indices[30] = 21;
	indices[31] = 20;
	indices[32] = 22;
	indices[33] = 21;
	indices[34] = 22;
	indices[35] = 23;


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
