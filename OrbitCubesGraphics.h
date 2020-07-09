#include "Graphics.h"
#include "CubeModel.h"


class OrbitCubesGraphics : public Graphics
{
public:

	OrbitCubesGraphics();
	bool Initialize(int, int, HWND);
	bool Render();

private:
	vector<Model*> models;
	float selfAngle[10];
	float uniAngle[10];
	float radius[10];

};
