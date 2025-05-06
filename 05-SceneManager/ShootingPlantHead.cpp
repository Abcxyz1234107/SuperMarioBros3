#include "ShootingPlantHead.h"

void CShootingPlantHead::Render() 
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_SHOOTINGPLANT_RED)->Render(x, y);
}

void CShootingPlantHead::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - width / 2 + 2;
	t = y - height / 2 + 2;
	r = l + width - 2;
	b = t + height - 2;
}