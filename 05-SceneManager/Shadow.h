#pragma once
#include "GameObject.h"

class Shadow :
    public CGameObject
{
private:
    float offsetX, offsetY;
    CGameObject* owner; //Để update theo owner
    int spriteId;
public:
    Shadow(CGameObject* owner, float offsetX, float offsetY, int id)
        : CGameObject(owner->GetX() + 10, owner->GetY() + 10)
    {
        this->offsetX = offsetX;
        this->offsetY = offsetY;
        this->spriteId = id;
        this->owner = owner;
        this->z = owner->GetZ() - 1;
    }

    void Render();
    void Update(DWORD dt);
    void GetBoundingBox(float &l, float &t, float &b, float &r) override {}
};

