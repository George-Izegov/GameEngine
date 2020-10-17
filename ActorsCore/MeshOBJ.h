
#include "../GameCore/MeshBase.h"


class ObjModel : public Mesh
{
public:
	ObjModel(std::string, Material mat = M_Wood);
	bool InitializeBuffers(ID3D11Device* device, DirectX::SimpleMath::Vector3 pos, float scale);
public:
	BoundingSphere* sphereColision;
	DirectX::SimpleMath::Vector3 position;
	DirectX::SimpleMath::Vector3 rotation;
	DirectX::SimpleMath::Matrix worldMatrix;
private:
	std::string fileName;
	
};

