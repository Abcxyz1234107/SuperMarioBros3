#pragma once
#include "GameObject.h"
#include "Game.h"

class CScoreBoard :
    public CGameObject
{
private:
    float offsetX;     // vị trí cố định trên màn hình
    float offsetY;

    ULONGLONG timer;
    int coin;
    long long score;
    int life;

public:
    CScoreBoard(float x, float y) : CGameObject(x, y), offsetX(x), offsetY(y)
    {
        SetZ(5);
    }

    void Render();
    void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL) override;
    void GetBoundingBox(float& l, float& t, float& r, float& b) override {}
};

