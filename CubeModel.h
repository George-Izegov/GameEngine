#include "Model.h"

class CubeModel : public Model
{
public:
	bool InitializeBuffers(ID3D11Device* device, DirectX::SimpleMath::Vector3 pos, float scale);
};