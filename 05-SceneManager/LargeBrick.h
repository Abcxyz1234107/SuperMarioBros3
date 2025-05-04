#pragma once
#include "GameObject.h"
class CLargeBrick :
    public CGameObject
{
private:
    int spriteID;
    int bboxWidth, bboxHeight;
public:
    CLargeBrick(int x, int y, int bboxWidth, int bboxHeight, int spriteID, int z) : 
        CGameObject(x, y)
    {
        this->spriteID = spriteID;
        this->bboxHeight = bboxHeight;
        this->bboxWidth = bboxWidth;
        this->z = z;
    }
    void Render();
    void GetBoundingBox(float& l, float& t, float& r, float& b);

    int IsDirectionColliable(float nx, float ny);
};

