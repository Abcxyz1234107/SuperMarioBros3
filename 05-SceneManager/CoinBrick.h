#pragma once
#include "GameObject.h"

#define COINBRICK_BBOX_W 16
#define COINBRICK_BBOX_H 16

class CoinBrick :
    public CGameObject
{
public:
    CoinBrick(float x, float y) : CGameObject(x, y)
    {

    }

    void Render();
    void GetBoundingBox(float& l, float& t, float& r, float& b) override;

    void Activate();
};

