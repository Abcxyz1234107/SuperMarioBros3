#include "CoinBrickFragment.h"

void CoinBrickFragment::Render()
{
    CSprites::GetInstance()->Get(ID_SPRITE_COINBRICK_FRAGMENT)->Draw(x, y);
    //RenderBoundingBox();
}

void CoinBrickFragment::Update(DWORD dt, vector<LPGAMEOBJECT>*)
{
    vy += COINBRICK_FRAGMENT_GRAVITY * dt;

    x += vx * dt;
    y += vy * dt;

    if (GetTickCount64() - lifetime > COINBRICK_FRAGMENT_LIFETIME)
        Delete();
}