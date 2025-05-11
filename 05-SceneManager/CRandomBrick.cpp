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

void CRandomBrick::Activate()
{
    if (this->GetState() != RANDOMBRICK_STATE_TOUCHED)
    {
        LPPLAYSCENE scene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
        CMario* mario = (CMario*)scene->GetPlayer();

        this->SetState(RANDOMBRICK_STATE_TOUCHED);

        if (this->GetType() == 1)
        {
            CRandomCoin* coin = new CRandomCoin(x, y - 16.0f);
            coin->SetVy(-0.25f);
            scene->AddObject(coin);
        }
        else if (mario->GetLevel() == MARIO_LEVEL_SMALL) // Mushroom
        {
            CRandomMushroom* mushroom = new CRandomMushroom(x, y);
            scene->AddObject(mushroom);
        }
        else
        {
            CRandomLeaf* leaf = new CRandomLeaf(x, y - 16.0f);
            leaf->SetVy(-0.125f);
            scene->AddObject(leaf);
        }
    }
}

