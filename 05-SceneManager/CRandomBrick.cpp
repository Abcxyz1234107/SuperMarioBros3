#include "CRandomBrick.h"
#include "PlayScene.h"

void CRandomBrick::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
		case RANDOMBRICK_STATE_TOUCHED:
		{
		spriteIdBegin = spriteIdMiddle = spriteIdEnd = ID_SPRITE_RANDOMBRICK_TOUCHED;
		isAni = 0;
		break;
		}
	}
}

void CRandomBrick::OnCollisionWith(LPCOLLISIONEVENT e)
{
    //if (dynamic_cast<CRandomMushroom*>(e->obj))
    //    OnCollisionWithRandomMushroom(e);
}

void CRandomBrick::OnCollisionWithRandomMushroom(LPCOLLISIONEVENT e)
{
    //e->obj->SetVy(-0.25f);
}

void CRandomBrick::Activate()
{
    if (this->GetState() != RANDOMBRICK_STATE_TOUCHED)
    {
        LPPLAYSCENE scene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
        CMario* mario = (CMario*)scene->GetPlayer();

        SetState(RANDOMBRICK_STATE_TOUCHED);

        vy = -RB_SPEED_Y;
        isBouncing = true;

        if (type == 3)
        {
            CRandomMushroomGreen* mushroom = new CRandomMushroomGreen(x, y);
            scene->AddObject(mushroom);
        }
        else
        if (type == 1)
        {
            CRandomCoin* coin = new CRandomCoin(x, y - 16.0f);
            coin->SetVy(-0.25f);
            scene->AddObject(coin);
        }
        else
        if (mario->GetLevel() > MARIO_LEVEL_SMALL) // Leaf
        {
            CRandomLeaf* leaf = new CRandomLeaf(x, y - 16.0f);
            leaf->SetVy(-0.125f);
            scene->AddObject(leaf);
        }
    }
}

void CRandomBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
    if (!isBouncing) return;

    y += vy * dt;

    if (vy < 0 && startY - y >= RB_MAX_Y) // đạt đỉnh
        vy = RB_SPEED_Y;

    // trở lại vị trí
    if (vy > 0 && y >= startY)
    {
        LPPLAYSCENE scene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
        CMario* mario = (CMario*)scene->GetPlayer();

        if (state == RANDOMBRICK_STATE_TOUCHED && type == 2 && mario->GetLevel() == MARIO_LEVEL_SMALL)
        {
            CRandomMushroom* mushroom = new CRandomMushroom(x, y - 2);
            scene->AddObject(mushroom);
        }
        y = startY;
        vy = 0;
        isBouncing = false;
    }
}
