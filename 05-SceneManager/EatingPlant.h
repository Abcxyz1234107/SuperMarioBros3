#pragma once
#include "ShootingPlant.h"

class CEatingPlant :
    public CShootingPlant

{
public:
    CEatingPlant(float x, float y,
        int bodyLength,
        float detectRange, int type = 4) :
        CShootingPlant(x, y, bodyLength, detectRange, type)
    {

    }

    void WAIT_TOP() override;
    void Detect_Mario() override;
};

