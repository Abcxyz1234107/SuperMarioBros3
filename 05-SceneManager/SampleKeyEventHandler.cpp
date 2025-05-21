#include "SampleKeyEventHandler.h"

#include "debug.h"
#include "Game.h"

#include "Mario.h"
#include "PlayScene.h"

void CSampleKeyHandler::OnKeyDown(int KeyCode)
{
	//DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	CMario* mario = (CMario *)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer(); 

	switch (KeyCode)
	{
	case DIK_C:
		if (mario->GetLevel() == MARIO_LEVEL_FLY)
			mario->SetGlide(true); 
		break;
	case DIK_DOWN:
		mario->SetState(MARIO_STATE_SIT);
		break;
	case DIK_SPACE:
		if (mario->GetLevel() == MARIO_LEVEL_FLY && mario->IsPowerFull())
		{
			mario->AddFlyPress();                 // ghi thời điểm
			mario->SetState(MARIO_STATE_FLY);
		}
		else
			mario->SetState(MARIO_STATE_JUMP);
		break;
	case DIK_LCONTROL:
		if (mario->GetLevel() == MARIO_LEVEL_FLY)
		{
			mario->SetState(MARIO_STATE_FLY);
		}
		break;
	case DIK_F:
		mario->SetImmortal(true);
		break;
	case DIK_K:
		mario->SetImmortal(false);
		break;
	case DIK_1:
		mario->SetLevel(MARIO_LEVEL_SMALL);
		break;
	case DIK_2:
		mario->SetLevel(MARIO_LEVEL_BIG);
		break;
	case DIK_3:
		mario->SetLevel(MARIO_LEVEL_FLY);
		break;
	case DIK_0:
		mario->SetState(MARIO_STATE_DIE);
		break;
	case DIK_R: // reset
		CGame::GetInstance()->ReloadScene(1);
		break;
	}
}

void CSampleKeyHandler::OnKeyUp(int KeyCode)
{
	//DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);

	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	switch (KeyCode)
	{
	case DIK_SPACE:
		if (mario->IsFly())
			mario->SetState(MARIO_STATE_RELEASE_FLY);
		else
			mario->SetState(MARIO_STATE_RELEASE_JUMP);
		break;
	case DIK_LCONTROL:
		if (mario->GetLevel() == MARIO_LEVEL_FLY)
		{
			mario->SetState(MARIO_STATE_RELEASE_FLY);
		}
		break;
	case DIK_DOWN:
		mario->SetState(MARIO_STATE_SIT_RELEASE);
		break;
	case DIK_C:
		mario->SetGlide(false); 
		break;
	}
}

void CSampleKeyHandler::KeyState(BYTE *states)
{
	LPGAME game = CGame::GetInstance();
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	if (mario->IsImmortal())
	{
		if (game->IsKeyDown(DIK_W))
		{
			mario->SetPosition(mario->GetX(), mario->GetY() - 10);
		}
		else if (game->IsKeyDown(DIK_S))
		{
			mario->SetPosition(mario->GetX(), mario->GetY() + 10);
		}
		else if (game->IsKeyDown(DIK_A))
		{
			mario->SetPosition(mario->GetX() - 10, mario->GetY());
		}
		else if (game->IsKeyDown(DIK_D))
		{
			mario->SetPosition(mario->GetX() + 10, mario->GetY());
		}
	}
	else
	{
		if (game->IsKeyDown(DIK_RIGHT))
		{
			if (game->IsKeyDown(DIK_D))
				mario->SetState(MARIO_STATE_RUNNING_RIGHT);
			else
				mario->SetState(MARIO_STATE_WALKING_RIGHT);
		}
		else if (game->IsKeyDown(DIK_LEFT))
		{
			if (game->IsKeyDown(DIK_A))
				mario->SetState(MARIO_STATE_RUNNING_LEFT);
			else
				mario->SetState(MARIO_STATE_WALKING_LEFT);
		}
		else
			mario->SetState(MARIO_STATE_IDLE);
	}
}