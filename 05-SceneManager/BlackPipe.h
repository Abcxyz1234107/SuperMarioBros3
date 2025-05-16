#pragma once
#include "GameObject.h"

#define ID_SPRITE_BP 21101
#define BP_W 32
#define BP_H 32

class CBlackPipe :
    public CGameObject

{
private:

public:
    CBlackPipe(float x, float y) : CGameObject(x, y)
    {
        
    }

    void Render();
    void GetBoundingBox(float& l, float& t, float& r, float& b) override;
};

