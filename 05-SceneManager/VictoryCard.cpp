#include "VictoryCard.h"

#define CARD_BBOX_W 16
#define CARD_BBOX_H 16

void CVictoryCard::Update(DWORD dt, vector<LPGAMEOBJECT>*)
{
    if (GetTickCount64() - lastSwitch >= VICTORYCARD_SWAP_INTERVAL)
    {
        current = (current + 1) % sprites.size();
        lastSwitch = GetTickCount64();
    }
}

void CVictoryCard::Render()
{
    CSprites::GetInstance()->Get(sprites[current])->Draw(x, y);
    //RenderBoundingBox();
}

void CVictoryCard::GetBoundingBox(float& l, float& t, float& r, float& b)
{
    l = x - CARD_BBOX_W / 2;
    t = y - CARD_BBOX_H / 2;
    r = l + CARD_BBOX_W;
    b = t + CARD_BBOX_H;
}