#include "ShootingPlantHead.h"

void CShootingPlantHead::Render() 
{
    int aniId_bottomLeft;
    int aniId_topLeft;
    int aniId_bottomRight;
    int aniId_topRight;

    if (type == 2)
    {
        aniId_bottomLeft = ID_ANI_SHOOTINGPLANT_RED_BOTTOMLEFT;
        aniId_topRight = ID_ANI_SHOOTINGPLANT_RED_TOPRIGHT;
        aniId_topLeft = ID_ANI_SHOOTINGPLANT_RED_TOPLEFT;
        aniId_bottomRight = ID_ANI_SHOOTINGPLANT_RED_BOTTOMRIGHT;
    }
    else if (type == 3)
    {
        aniId_bottomLeft = ID_ANI_SHOOTINGPLANT_GREEN_BOTTOMLEFT;
        aniId_topRight = ID_ANI_SHOOTINGPLANT_GREEN_TOPRIGHT;
        aniId_topLeft = ID_ANI_SHOOTINGPLANT_GREEN_TOPLEFT;
        aniId_bottomRight = ID_ANI_SHOOTINGPLANT_GREEN_BOTTOMRIGHT;
    }
    else
    {
        aniId_bottomLeft = ID_ANI_EATINGPLANT_GREEN;
        aniId_topRight = ID_ANI_EATINGPLANT_GREEN;
        aniId_topLeft = ID_ANI_EATINGPLANT_GREEN;
        aniId_bottomRight = ID_ANI_EATINGPLANT_GREEN;
    }

    if (useStatic)
    {
        CSprites::GetInstance()->Get(staticSpriteId)->Draw(x, y);
        return;
    }
    else 
    {
        CAnimations* animations = CAnimations::GetInstance();
        int ani = aniId_bottomLeft;
        switch (orient)
        {
        case 1: ani = aniId_topRight;  break;
        case 2: ani = aniId_topLeft;    break;
        case 3: ani = aniId_bottomRight;  break;
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