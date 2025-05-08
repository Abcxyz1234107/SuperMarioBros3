#include "ShootingPlantHead.h"

void CShootingPlantHead::Render() 
{
    if (useStatic)
    {
        CSprites::GetInstance()->Get(staticSpriteId)->Draw(x, y);
        return;
    }
    else 
    {
        CAnimations* animations = CAnimations::GetInstance();
        int ani = ID_ANI_SHOOTINGPLANT_RED_BOTTOMLEFT;
        switch (orient)
        {
        case 1: ani = ID_ANI_SHOOTINGPLANT_RED_TOPRIGHT;  break;
        case 2: ani = ID_ANI_SHOOTINGPLANT_RED_TOPLEFT;    break;
        case 3: ani = ID_ANI_SHOOTINGPLANT_RED_BOTTOMRIGHT;  break;
        }
        animations->Get(ani)->Render(x, y);
    }
}

void CShootingPlantHead::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - SHOOTINGPLANT_HEAD_W / 2 + 2;
	t = y - SHOOTINGPLANT_HEAD_H / 2 + 2;
	r = l + SHOOTINGPLANT_HEAD_W - 2;
	b = t + SHOOTINGPLANT_HEAD_H - 2;
}