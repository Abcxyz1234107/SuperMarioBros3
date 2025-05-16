#pragma once
#include "GameObject.h"

#define ID_ANI_BUTTON 20030
#define B_W 15
#define B_H 16

class Button :
    public CGameObject
{
public:
    Button(float x, float y) : CGameObject(x, y)
    {

    }

    void Render();
    void GetBoundingBox(float& l, float& t, float& r, float& b) override;

    void Activate();
};

