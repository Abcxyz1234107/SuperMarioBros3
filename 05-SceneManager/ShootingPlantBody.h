#pragma once
#include "PipeBody.h"
class CShootingPlantBody :
    public CPipeBody
{
public:
    CShootingPlantBody(float x, float y,
        float cellWidth, float cellHeight, int length,
        int spriteId = ID_SPRITE_SHOOTINGPLANT_BODY) : 
        CPipeBody(x, y, cellWidth, cellHeight, length, spriteId)
    {
        z = 2;
    }

    void GetBoundingBox(float& l, float& t, float& r, float& b) override;
};

