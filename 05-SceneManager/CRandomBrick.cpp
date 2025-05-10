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
			CRandomCoin* coin = new CRandomCoin(this->GetX(), this->GetY() - 16.0f);
			coin->SetVy(-0.25f);
			LPPLAYSCENE currentScene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
			currentScene->AddObject(coin);
		}
		else if (mario->GetLevel() == MARIO_LEVEL_SMALL)
		{
			CRandomMushroom* mushroom = new CRandomMushroom(this->GetX(), this->GetY());
			LPPLAYSCENE currentScene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
			currentScene->AddObject(mushroom);
		}
		else
		{
			CRandomLeaf* leaf = new CRandomLeaf(this->GetX(), this->GetY() - 16.0f);
			leaf->SetVy(-0.25f);
			LPPLAYSCENE currentScene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
			currentScene->AddObject(leaf);
		}
	}
}
