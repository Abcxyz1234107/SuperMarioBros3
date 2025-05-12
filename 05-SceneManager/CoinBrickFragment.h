#pragma once
#include "GameObject.h"

#define COINBRICK_FRAGMENT_GRAVITY       0.002f
#define COINBRICK_FRAGMENT_LIFETIME      1000

class CoinBrickFragment :
    public CGameObject
{
private:
    ULONGLONG lifetime;
public:
    CoinBrickFragment(float x, float y, float vx, float vy)
        : CGameObject(x, y)
    {
        this->vx = vx;
        this->vy = vy;
        lifetime = GetTickCount64();
    }

    void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = nullptr) override;
    void Render() override;
    void GetBoundingBox(float& l, float& t, float& r, float& b) override {}
};

