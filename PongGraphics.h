#include "/Users/ddlis/source/repos/PongProject/Graphics.h"
#include "BallModel.h"
#include "PlatformModel.h"

class PongGraphics : public Graphics
{
public:

	PongGraphics();
	bool Initialize(int, int, HWND);
	bool Render();
	void SetPosOfModels(float, float, DirectX::SimpleMath::Vector2); //platf1, platf2, ball

	Ball* _ball;
	Platform* _plat1;
	Platform* _plat2;

private:
	float platform1Pos;
	float platform2Pos;
	DirectX::SimpleMath::Vector2 _ballPos;
};

