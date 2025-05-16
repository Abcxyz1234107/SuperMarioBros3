#pragma once
#include "GameObject.h"

class Shadow :
    public CGameObject
{
private:
    float offsetX, offsetY;
    CGameObject* owner; //Để update theo owner
    int spriteId;

    D3DXCOLOR black = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
    D3DXCOLOR white = D3DXCOLOR(255, 255, 255, 1.0f);

    int color; //1: black, 2: white
public:
    Shadow(CGameObject* owner, float offsetX, float offsetY, int id)
        : CGameObject(owner->GetX() + 10, owner->GetY() + 10)
    {
        this->offsetX = offsetX;
        this->offsetY = offsetY;
        this->spriteId = id;
        this->owner = owner;
        this->z = owner->GetZ() - 1;
        color = 1;
    }

    Shadow(float x, float y, int z, int id, int c)
        : CGameObject(x, y)
    {
        spriteId = id;
        owner = nullptr;
        offsetX = offsetY = 0;
        this->z = z;
        color = c;
    }

    void Render();
    void GetBoundingBox(float &l, float &t, float &b, float &r) override {}
};

