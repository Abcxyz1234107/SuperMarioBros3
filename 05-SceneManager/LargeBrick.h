#pragma once
#include "GameObject.h"
#include "Shadow.h"

class CLargeBrick :
    public CGameObject
{
private:
    int spriteID;
    int bboxWidth, bboxHeight;

    Shadow* shadow;
public:
    CLargeBrick(float x, float y, int bboxWidth, int bboxHeight, int spriteID, int z) :
        CGameObject(x, y)
    {
        this->z = z;
        this->spriteID = spriteID;
        this->bboxHeight = bboxHeight;
        this->bboxWidth = bboxWidth;
        this->shadow = new Shadow(this, 10, 10, spriteID);
    }
    void Render();
    void GetBoundingBox(float& l, float& t, float& r, float& b);

    int IsDirectionColliable(float nx, float ny);

    Shadow* GetShadow() { return shadow; }
};

