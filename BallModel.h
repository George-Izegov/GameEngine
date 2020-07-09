#include "Model.h"


#define PI 3.14159265358979323846

class Ball : public Model
{


public:
	bool InitializeBuffers(ID3D11Device* device, DirectX::SimpleMath::Vector3 pos, float scale);
};