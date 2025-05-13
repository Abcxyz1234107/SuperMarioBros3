#pragma once
#include "GameObject.h"

#define Shadow_x 10
#define Shadow_y 10

class Shadow :
    public CGameObject
{
private:
    CGameObject* owner; //Để update theo owner
    int spriteId;
public:
    Shadow(CGameObject* owner, int id)
        : CGameObject(owner->GetX() + 10, owner->GetY() + 10)
    {
        this->spriteId = id;
        this->owner = owner;
        this->z = owner->GetZ() - 1;
    }

    void Render();
    void Update(DWORD dt);
    void GetBoundingBox(float &l, float &t, float &b, float &r) override {}
};

