#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_PIPEBODY 10012
#define PIPEBODY_WIDTH 16
#define PIPEBODY_BBOX_WIDTH 30
#define PIPEBODY_BBOX_HEIGHT 16

class CPipeBody : public CGameObject
{
protected:
    float cellWidth;
    float cellHeight;
    int length;                  // số lượng ống
    int spriteId;

public:
    CPipeBody(float x, float y,
        float cellWidth, float cellHeight, int length,
        int spriteId)
        : CGameObject(x, y)
    {
        this->cellWidth = cellWidth;
        this->cellHeight = cellHeight;
        this->length = length;
        this->spriteId = spriteId;
    }

    void Render();
    void GetBoundingBox(float& l, float& t, float& r, float& b);
    int IsBlocking() { return 1; } 
};

