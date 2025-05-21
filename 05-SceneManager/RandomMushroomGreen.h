#pragma once
#include "RandomMushroom.h"

#define ID_SPRITE_GREEN_RANDOMMUSHROOM 31301

class CRandomMushroomGreen :
    public CRandomMushroom

{
private:
    void OnCollisionWithMario(LPCOLLISIONEVENT e) override;

public:
    CRandomMushroomGreen(float x, float y) : CRandomMushroom(x, y)
    {

    }

    void Render() override;
    void OnCollisionWith(LPCOLLISIONEVENT e) override;
};

