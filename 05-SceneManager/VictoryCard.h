#pragma once
#include "GameObject.h"

/*
#define ID_SPRITE_RANDOMUSHROOM 31101
#define ID_SPRITE_FLOWERCARD 31181
#define ID_SPRITE_STARCARD 31171
*/

#define VICTORYCARD_SWAP_INTERVAL 100

class CVictoryCard :
    public CGameObject
{
private:
    vector<int> sprites;
    int         current;
    ULONGLONG   lastSwitch;

public:
    CVictoryCard(float x, float y)
        : CGameObject(x, y), current(0), lastSwitch(GetTickCount64())
    {
        z = 4;
        vx = vy = 0;
        sprites = { ID_SPRITE_RANDOMUSHROOM, ID_SPRITE_FLOWERCARD, ID_SPRITE_STARCARD };
    }

    void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = nullptr) override;
    void Render() override;
    void GetBoundingBox(float& l, float& t, float& r, float& b) override;
};

