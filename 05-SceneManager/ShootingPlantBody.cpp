#include "ShootingPlantBody.h"

void CShootingPlantBody::GetBoundingBox(float& l, float& t, float& r, float& b)
{
    l = x - cellWidth / 2 + 8;
    t = y - cellHeight / 2 + 8;
    r = l + cellWidth - 12;
    b = t + totalHeight - 12;
}