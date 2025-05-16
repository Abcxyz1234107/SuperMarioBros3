#include "CoinBrick.h"
#include "CoinBrickFragment.h"
#include "PlayScene.h"
#include "Coin.h"

void CoinBrick::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case CB_STATE_TOUCHED:
	{
		break;
	}
	}
}

void CoinBrick::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_COINBRICK)->Render(x, y);
	//RenderBoundingBox();
}

void CoinBrick::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - COINBRICK_BBOX_W / 2;
	t = y - COINBRICK_BBOX_H / 2;
	r = l + COINBRICK_BBOX_W;
	b = t + COINBRICK_BBOX_H;
}

void CoinBrick::Bounce()
{
    vy = -CB_SPEED_Y;
    isBouncing = true;
}

void CoinBrick::ChangeToCoin()
{
    this->Delete();
    LPPLAYSCENE scene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();

    scene->AddObject(new CCoin(x, y));
}

void CoinBrick::Activate()
{
    this->Delete();

    float cx = x, cy = y;
    const float vx = 0.08f;
    const float vy = 0.20f;

    LPPLAYSCENE scene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();

    scene->AddObject(new CoinBrickFragment(cx, cy, -vx, -vy));
    scene->AddObject(new CoinBrickFragment(cx, cy, vx, -vy));
    scene->AddObject(new CoinBrickFragment(cx, cy, -vx, vy));
    scene->AddObject(new CoinBrickFragment(cx, cy, vx, vy));
}

void CoinBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
    if (!isBouncing) return;

    y += vy * dt;

    if (vy < 0 && startY - y >= CB_MAX_Y) // đạt đỉnh
        vy = CB_SPEED_Y;

    // trở lại vị trí
    if (vy > 0 && y >= startY)
    {
        y = startY;
        vy = 0;
        isBouncing = false;
    }
}