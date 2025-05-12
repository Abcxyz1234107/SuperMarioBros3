#include "CoinBrick.h"
#include "CoinBrickFragment.h"
#include "PlayScene.h"

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