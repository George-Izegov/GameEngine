#define TINYOBJLOADER_IMPLEMENTATION // define this in only *one* .cc
#include "../MeshLoader/tinyobjloader-master/tiny_obj_loader.h"
#include "MeshOBJ.h"
#include <iostream>


ObjModel::ObjModel(std::string fName, Material mat)
{
	fileName = fName;
	_mat = mat;
	sphereColision = new BoundingSphere;
	
}

bool ObjModel::InitializeBuffers(ID3D11Device* device, DirectX::SimpleMath::Vector3 pos, float scale)
{
	position = pos*scale;
	if (fileName.size() < 1)
	{
		std::cout << "Can't find obj model!" << std::endl;
		return false;
	}
    std::string inputfile = fileName;
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;

    std::string warn;
    std::string err;

	bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, inputfile.c_str());

    if (!warn.empty()) {
        std::cout << warn << std::endl;
    }

    if (!err.empty()) {
        std::cerr << err << std::endl;
    }

    if (!ret) {
        exit(1);
    }

   

	VertexType* vertices;
	unsigned long* indices;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;
	size_t shapeNum;
	long long polygonNum;

	float minX, minY, minZ, maxX, maxY, maxZ;
	minX = minY = minZ = INFINITY;
	maxX = maxY = maxZ = -1*INFINITY;

	shapeNum = shapes.size();
	polygonNum = 0;

	// Set the number of vertices in the vertex array.
	m_vertexCount = 0;

	// Set the number of indices in the index array.
	m_indexCount = 0;

	for (size_t s = 0; s < shapes.size(); s++) {
		// Loop over faces(polygon)
		polygonNum += shapes[s].mesh.num_face_vertices.size();
	
	}

	m_vertexCount = polygonNum * 3;
	m_indexCount =  m_vertexCount;

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
	
	long long vertItr;
	vertItr = 0;
	// Loop over shapes
	for (size_t s = 0; s < shapes.size(); s++) {
		// Loop over faces(polygon)
		

		size_t index_offset = 0;
		for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
			int fv = shapes[s].mesh.num_face_vertices[f];

			// Loop over vertices in the face.
			for (size_t v = 0; v < fv; v++) {
				// access to vertex
				tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
				vertices[vertItr].position.x = attrib.vertices[(idx.vertex_index * 3) + 2] + pos.x;
				vertices[vertItr].position.y = attrib.vertices[(3 * idx.vertex_index) + 1] + pos.y;
				vertices[vertItr].position.z = attrib.vertices[(3 * idx.vertex_index) + 0] + pos.z;
				vertices[vertItr].position *= scale;

				if (vertices[vertItr].position.x > maxX) maxX = vertices[vertItr].position.x;
				if (vertices[vertItr].position.y > maxY) maxY = vertices[vertItr].position.y;
				if (vertices[vertItr].position.z > maxZ) maxZ = vertices[vertItr].position.z;
				if (vertices[vertItr].position.x < minX) minX = vertices[vertItr].position.x;
				if (vertices[vertItr].position.y < minY) minY = vertices[vertItr].position.y;
				if (vertices[vertItr].position.z < minZ) minZ = vertices[vertItr].position.z;

				vertices[vertItr].normal.x = attrib.normals[(3 * idx.normal_index) + 2];
				vertices[vertItr].normal.y = attrib.normals[(3 * idx.normal_index) + 1];
				vertices[vertItr].normal.z = attrib.normals[(3 * idx.normal_index) + 0];
				/*vertices[vertItr].texPos.x = attrib.texcoords[(2 * idx.texcoord_index) + 0];
				vertices[vertItr].texPos.y = attrib.texcoords[(2 * idx.texcoord_index) + 1];*/
				/*vertices[vertItr].texPos.x =  0.01f*(vertItr%100);
				vertices[vertItr].texPos.y =  0.01f * (vertItr % 100);*/
				vertices[vertItr].texPos.x = vertices[vertItr].position.x;
				vertices[vertItr].texPos.y = vertices[vertItr].position.y;

				indices[vertItr] = (int) vertItr;
				vertItr++;

			}
			index_offset += fv;

			// per-face material
			//shapes[s].mesh.material_ids[f];
		}
	}

	//create sphere collision

	XMFLOAT3 edgePoints[8] = { {minX,minY,minZ}, {minX,minY,maxZ}, {minX,maxY,minZ}, {maxX,minY,minZ}, {minX,maxY,maxZ}, {maxX,minY,maxZ}, {maxX,maxY,minZ}, {maxX,maxY,maxZ} };
	sphereColision->Center = { (maxX + minX)/2, (maxY + minY)/2, (maxZ + minZ)/2 };
	sphereColision->Radius = sqrt((maxX - minX) * (maxX - minX) + (maxY - minY) * (maxY - minY) + (maxZ - minZ) * (maxZ - minZ))/5;

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