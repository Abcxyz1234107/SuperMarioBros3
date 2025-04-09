#include "BGCloud.h"

void CBGCloud::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_BGCLOUD)->Render(x, y);
}

void CBGCloud::GetBoundingBox(float& l, float& t, float& r, float& b)
{

}