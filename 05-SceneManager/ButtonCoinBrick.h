#pragma once
#include "CoinBrick.h"
#include "Button.h"

#define ID_SPRITE_ACTIVATED 20025

class ButtonCoinBrick :
    public CoinBrick

{
public:
    ButtonCoinBrick(float x, float y) : CoinBrick(x, y)
    {

    }

    void Render() override;
    void Activate() override;
};

