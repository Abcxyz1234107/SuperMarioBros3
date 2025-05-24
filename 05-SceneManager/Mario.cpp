#include <algorithm>
#include "debug.h"

#include "Mario.h"
#include "Game.h"

#include "Goomba.h"
#include "CRandomBrick.h"
#include "Portal.h"
#include "Coin.h"
#include "ShootingPlant.h"
#include "VoidSpike.h"
#include "CRandomBrick.h"
#include "CoinBrick.h"
#include "Koopas.h"
#include "KoopasGreen.h"
#include "RandomLeaf.h"
#include "GoombaRed.h"
#include "ButtonCoinBrick.h"
#include "BlackPipe.h"

#include "Collision.h"

void CMario::StartTeleport(int dir, int sceneId, float distance)
{
	teleportDir = dir;
	teleportSceneId = sceneId;
	isTeleporting = true;

	vy = dir * MARIO_TELEPORT_SPEED;
	ay = 0.0f;
	teleportTargetY = y + dir * distance;

	isOnPlatform = false;

	SetState(MARIO_STATE_TELEPORT);
}

void CMario::SetGlide(bool g)
{
	isGlide = g;
}

void CMario::StartTailHit()
{
	if (level != MARIO_LEVEL_FLY || isTailHit) return;   // chỉ level 3
	isTailHit = true;
	tailHit_start = GetTickCount64();
}

void CMario::TailHitGoomba(LPGAMEOBJECT goomba) //Helper để gọi gián tiếp OnCollisionWithGoomba
{
	CGoombaRed* rg = dynamic_cast<CGoombaRed*>(goomba);
	if (rg)
	{
		if (rg->HasWings())
		{
			score += 100;
			rg->AddCharacter(C_100);
			rg->RemoveWing();
			return; // không flip
		}
	}

	CGoomba* g = dynamic_cast<CGoomba*>(goomba);
	if (!g || g->GetState() == GOOMBA_STATE_FLIPPED) return;

	float nxTail = (nx > 0) ? 1.0f : -1.0f;
	float nyTail = -1.0f; 	/*  ny = -1 vì các OnCollisionWithGoomba() chỉ nhận đòn có ny < 0 (đạp đầu) */

	CCollisionEvent tailEvt(0.0f, nxTail, nyTail, 0.0f, 0.0f, goomba, this);

	OnCollisionWithGoomba(&tailEvt);

	g->SetState(GOOMBA_STATE_FLIPPED);
	g->AddCharacter(C_ANI_HIT);
}


void CMario::TailAttack(const vector<LPGAMEOBJECT>* coObjects)
{
	float l, t, r, b;
	GetBoundingBox(l, t, r, b);

	float tailL, tailR;
	if (nx > 0) { tailL = r; tailR = r + MARIO_TAIL_HIT_RANGE; }
	else { tailR = l; tailL = l - MARIO_TAIL_HIT_RANGE; }

	float tailT = t - MARIO_TAIL_HIT_RANGE_Y;
	float tailB = b + MARIO_TAIL_HIT_RANGE_Y;

	for (auto obj : *coObjects)
	{
		if (!dynamic_cast<CGoomba*>(obj)) continue;

		float el, et, er, eb;
		obj->GetBoundingBox(el, et, er, eb);

		bool overlapX = !(tailR < el || tailL > er);
		bool overlapY = !(tailB < et || tailT > eb);

		if (overlapX && overlapY)
		{
			TailHitGoomba(obj);
		}
	}
}


void CMario::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	if (immortal) return;

	vx += ax * dt;

	//-------------------------------------FLY------------------------//
	bool isRunning =
		abs(ax) == MARIO_ACCEL_RUN_X &&            // đang giữ A/D
		abs(vx) >= MARIO_RUNNING_SPEED * 0.9f;     // đạt speed chạy

	ULONGLONG now = GetTickCount64();

	if (isRunning)                    // ---- TĂNG POWER ----
	{
		powerDelay = 0;
		if (power < MARIO_POWER_MAX &&
			now - powerTick >= MARIO_POWER_INC_TIME)
		{
			power++;
			powerTick = now;
			if (power == MARIO_POWER_MAX) powerFull = true;
		}
	}
	else                              // ---- GIẢM POWER ----
	{
		if (power > 0)
		{
			if (powerDelay == 0) powerDelay = now;
			else if (now - powerDelay >= MARIO_POWER_DEC_DELAY &&
				now - powerTick >= MARIO_POWER_DEC_TIME)
			{
				power--;
				powerTick = now;
				if (power == 0)
				{
					powerFull = false;
					powerDelay = 0;
				}
			}
		}
		else powerFull = false;
	}

	if (level == MARIO_LEVEL_FLY && powerFull)
	{
		bool recentlyPressed = now - lastFlyPress <= MARIO_FLY_PRESS_TIMEOUT;
		isFly = recentlyPressed;              // bay khi còn spam Space
	}
	else isFly = false;

	if (power < MARIO_POWER_MAX) powerFull = false;

	//-------------------------------------GLIDE------------------------//

	bool glideCandidate = level == MARIO_LEVEL_FLY          // có cánh
		&& !isOnPlatform                    // đang trên không
		&& !isFly;                          // KHÔNG bay

	bool glideActive = glideCandidate &&
		(now - lastGlidePress <= MARIO_GLIDE_PRESS_TIMEOUT);

	isGlide = glideActive;

	//-------------------------------------TAIL_HIT------------------------//
	if (isTailHit)
	{
		ULONGLONG now = GetTickCount64();
		TailAttack(coObjects);
		if (now - tailHit_start >= MARIO_TAIL_HIT_DURATION)
			isTailHit = false;  // hết 200 ms
	}

	if (level == MARIO_LEVEL_FLY && !isOnPlatform)
	{
		if (isFly)                       // đang bay
			vy = -MARIO_RUNNING_SPEED;
		else                             // rơi / glide
		{
			ay = (isGlide && vy > 0) ? MARIO_GLIDE_GRAVITY     // giảm rơi
				: MARIO_GRAVITY;
			vy += ay * dt;
		}
	}
	else                                 // các level khác
	{
		ay = immortal ? 0.0f : MARIO_GRAVITY;
		vy += ay * dt;
	}

	//-------------------------------------TIME_OUT------------------------//

	if (timer > 0)
	{
		ULONGLONG now = GetTickCount64();
		ULONGLONG delta = now - ref;

		if (delta >= 1000) // 1 giây
		{
			int secPassed = (int)(delta / 1000);
			timer = max(0, timer - secPassed);
			ref += secPassed * 1000;   // tham chiếu

			if (timer == 0)
				SetState(MARIO_STATE_DIE);
		}
	}

	//-------------------------------------TELEPORT------------------------//

	if (state == MARIO_STATE_TELEPORT && isTeleporting)
	{
		vy = teleportDir * MARIO_TELEPORT_SPEED;
		y += vy * dt;

		if ((teleportDir == 1 && y >= teleportTargetY) ||
			(teleportDir == -1 && y <= teleportTargetY))
		{
			y = teleportTargetY;
			vy = 0;
			ay = MARIO_GRAVITY;
			isTeleporting = false;

			if (teleportSceneId >= 0)
			{
				CGame::GetInstance()->InitiateSwitchScene(teleportSceneId);
				if (desX != -1) 
				{
					x = desX;
					y = desY;

					arrived = true;
				}
			}
				
			else SetState(MARIO_STATE_IDLE);

		}
		return;	// bỏ qua xử lý va chạm khi đang dịch chuyển
	}


	if (abs(vx) > abs(maxVx)) vx = maxVx;

	// reset untouchable timer if untouchable time has passed
	if ( GetTickCount64() - untouchable_start > MARIO_UNTOUCHABLE_TIME) 
	{
		untouchable_start = 0;
		untouchable = 0;
	}

	if (level == MARIO_LEVEL_FLY && isFly)
		vy = -MARIO_RUNNING_SPEED;

	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CMario::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
	isOnPlatform = false;
}

void CMario::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (e->ny != 0 && e->obj->IsBlocking())
	{
		vy = 0;
		if (e->ny < 0) isOnPlatform = true;
	}
	else 
	if (e->nx != 0 && e->obj->IsBlocking())
	{
		vx = 0;
	}

	if (dynamic_cast<CGoomba*>(e->obj))
		OnCollisionWithGoomba(e);
	else if (dynamic_cast<CCoin*>(e->obj))
		OnCollisionWithCoin(e);
	else if (dynamic_cast<CPortal*>(e->obj))
		OnCollisionWithPortal(e);
	else if (dynamic_cast<Button*>(e->obj))
		OnCollisionWithButton(e);
	else if (dynamic_cast<CRandomBrick*>(e->obj))
		OnCollisionWithRandomBrick(e);
	else if (dynamic_cast<CRandomLeaf*>(e->obj))
		OnCollisionWithRandomLeaf(e);
	else if (dynamic_cast<CoinBrick*>(e->obj))
		OnCollisionWithCoinBrick(e);
	else if (dynamic_cast<CVoidSpike*>(e->obj))
		OnCollisionWithVoidSpike(e);
	else if (dynamic_cast<CShootingPlantHead*>(e->obj) || dynamic_cast<CShootingPlantBody*>(e->obj) 
		|| dynamic_cast<CShootingPlantBullet*>(e->obj))
		OnCollisionWithRandomShootingPlant(e);
}

void CMario::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);

	if (dynamic_cast<CRandomMushroom*>(goomba))
	{
		OnCollisionWithRandomMushroom(e);
	}
	else if (dynamic_cast<CKoopas*>(goomba))
	{
		if (dynamic_cast<CKoopasGreen*>(goomba))
			OnCollisionWithKoopasGreen(e);
		else
			OnCollisionWithKoopas(e);
	}
	else if (dynamic_cast<CKoopasShell*>(goomba))
	{
		OnCollisionWithKoopasShell(e);
	}
	else if (dynamic_cast<CGoombaRed*>(goomba))
	{
		OnCollisionWithGoombaRed(e);
	}
	else
	{
		if (e->ny < 0)
		{
			if (goomba->GetState() != GOOMBA_STATE_DIE)
			{
				score += 100;
				goomba->AddCharacter(C_100);
				goomba->SetState(GOOMBA_STATE_DIE);
				if (!isTailHit) vy = -MARIO_JUMP_DEFLECT_SPEED;
			}
		}
		else
		{
			if (untouchable == 0)
			{
				if (goomba->GetState() != GOOMBA_STATE_DIE)
				{
					if (level > MARIO_LEVEL_SMALL)
					{
						level--;
						StartUntouchable();
					}
					else
					{
						DebugOut(L">>> Mario DIE >>> \n");
						SetState(MARIO_STATE_DIE);
					}
				}
			}
		}
	}
}

void CMario::OnCollisionWithCoin(LPCOLLISIONEVENT e)
{
	e->obj->Delete();
	coin++;
	score += 50;
}

void CMario::OnCollisionWithButton(LPCOLLISIONEVENT e)
{
	Button* b = (Button*)e->obj;
	b->Activate();
}

void CMario::OnCollisionWithCoinBrick(LPCOLLISIONEVENT e)
{
	CoinBrick* cb = (CoinBrick*)e->obj;
	
	if (e->ny > 0)
	{
		cb->Bounce();
		if (dynamic_cast<ButtonCoinBrick*>(e->obj)) cb->Activate();
	}
}

void CMario::OnCollisionWithVoidSpike(LPCOLLISIONEVENT e)
{
	DebugOut(L">>> Mario DIE >>> \n");
	SetState(MARIO_STATE_DIE);
}

void CMario::OnCollisionWithGoombaRed(LPCOLLISIONEVENT e)
{
	CGoombaRed* rg = (CGoombaRed*)e->obj;
	if (e->ny < 0)
	{
		if (rg->HasWings()) // lần 1
		{
			score += 100;
			rg->AddCharacter(C_100);
			rg->RemoveWing();
			if (!isTailHit) vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
		else if (rg->GetState() != GOOMBA_STATE_DIE)  // lần 2
		{
			score += 200;
			rg->AddCharacter(C_200);
			rg->SetState(GOOMBA_STATE_DIE);
			if (!isTailHit) vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
	}
	else
	{
		if (untouchable == 0)
		{
			if (rg->GetState() != GOOMBA_STATE_DIE)
			{
				if (level > MARIO_LEVEL_SMALL)
				{
					level--;
					StartUntouchable();
				}
				else
				{
					DebugOut(L">>> Mario DIE >>> \n");
					SetState(MARIO_STATE_DIE);
				}
			}
		}
	}
}

void CMario::OnCollisionWithKoopasShell(LPCOLLISIONEVENT e)
{
	CKoopasShell* shell = (CKoopasShell*)e->obj;
	if (shell->IsHeld()) return;

	/* 1. Mario chạy & shell đứng yên  ->  nhặt */
	if (shell->GetState() != SHELL_STATE_NORMAL && abs(ax) == MARIO_ACCEL_RUN_X)
	{
		shell->SetHeld();
		this->SetHoldingShell(true);
		return;
	}

	/* 2. Shell đứng yên nhưng Mario chạy -> đá */
	if (shell->GetState() != SHELL_STATE_NORMAL)
	{
		float dir = (x < shell->GetX()) ? 1.0f : -1.0f;

		if (e->ny < 0)
		{
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}

		score += hitShellOnce ? 100 : 200;
		shell->AddCharacter(hitShellOnce ? C_100 : C_200);
		hitShellOnce = true;

		shell->Activate(dir);
		return;
	}

	/* 3. Shell đang chạy */
	if (e->ny < 0)
	{
		vy = -MARIO_JUMP_DEFLECT_SPEED;
		shell->SetState(SHELL_STATE_REVIVING);

		score += hitShellOnce ? 100 : 200;
		shell->AddCharacter(hitShellOnce ? C_100 : C_200);
		hitShellOnce = true;
		return;
	}

	if (untouchable == 0)              // va chạm mario
	{
		if (level > MARIO_LEVEL_SMALL)
		{
			level--;
			StartUntouchable();
		}
		else
		{
			DebugOut(L">>> Mario DIE >>> \n");
			SetState(MARIO_STATE_DIE);
		}
	}
}

void CMario::OnCollisionWithRandomMushroom(LPCOLLISIONEVENT e)
{
	CRandomMushroom* mushroom = (CRandomMushroom*)e->obj;
	if (dynamic_cast<CRandomMushroomGreen*>(mushroom))
	{
		CRandomMushroomGreen* mg = dynamic_cast<CRandomMushroomGreen*>(mushroom);
		if (mg->IsEmerging() == false)
		{
			score += 1000;
			life++;
			mg->AddCharacter(C_1000);
			mg->AddCharacter(C_1UP);
			mg->Delete();
		}
	}
	else
	if (mushroom->IsEmerging() == false)
	{
		score += 1000;
		mushroom->AddCharacter(C_1000);
		mushroom->Delete();

		if (this->level == MARIO_LEVEL_SMALL)
		{
			this->SetLevel(MARIO_LEVEL_BIG);
		}
	}
}

void CMario::OnCollisionWithKoopas(LPCOLLISIONEVENT e)
{
	CKoopas* koopas = (CKoopas*)e->obj;
	if (e->ny < 0)
	{
		if (koopas->GetState() != GOOMBA_STATE_DIE)
		{
			score += 100;
			koopas->AddCharacter(C_100);
			koopas->SetState(GOOMBA_STATE_DIE);
			if (!isTailHit) vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
	}
	else
	{
		if (untouchable == 0)
		{
			if (koopas->GetState() != GOOMBA_STATE_DIE)
			{
				if (level > MARIO_LEVEL_SMALL)
				{
					level--;
					StartUntouchable();
				}
				else
				{
					DebugOut(L">>> Mario DIE >>> \n");
					SetState(MARIO_STATE_DIE);
				}
			}
		}
	}
}

void CMario::OnCollisionWithKoopasGreen(LPCOLLISIONEVENT e)
{
	CKoopasGreen* koopas = (CKoopasGreen*)e->obj;
	if (e->ny < 0)
	{
		if (koopas->HasWings()) 
		{
			score += 100;
			koopas->AddCharacter(C_100);
			koopas->RemoveWing();
			if (!isTailHit) vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
		else if (koopas->GetState() != GOOMBA_STATE_DIE)  // lần 2
		{
			score += 200;
			koopas->AddCharacter(C_200);
			koopas->SetState(GOOMBA_STATE_DIE);
			if (!isTailHit) vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
	}
	else
	{
		if (untouchable == 0)
		{
			if (koopas->GetState() != GOOMBA_STATE_DIE)
			{
				if (level > MARIO_LEVEL_SMALL)
				{
					level--;
					StartUntouchable();
				}
				else
				{
					DebugOut(L">>> Mario DIE >>> \n");
					SetState(MARIO_STATE_DIE);
				}
			}
		}
	}
}

void CMario::OnCollisionWithRandomShootingPlant(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<CShootingPlantBullet*>(e->obj)) e->obj->Delete();

	if (untouchable == 0)
	{
		if (level > MARIO_LEVEL_SMALL)
		{
			level--;
			StartUntouchable();
		}
		else
		{
			DebugOut(L">>> Mario DIE >>> \n");
			SetState(MARIO_STATE_DIE);
		}
	}
}

void CMario::OnCollisionWithRandomBrick(LPCOLLISIONEVENT e)
{
	CRandomBrick* randomBrick = dynamic_cast<CRandomBrick*>(e->obj);

	if (e->ny > 0)
	{
		randomBrick->Activate();
	}
}

void CMario::OnCollisionWithRandomLeaf(LPCOLLISIONEVENT e)
{
	CRandomLeaf* leaf = dynamic_cast<CRandomLeaf*>(e->obj);

	score += 1000;
	leaf->AddCharacter(C_1000);
	leaf->Delete();
	if (level < MARIO_LEVEL_FLY)
		SetLevel(level + 1);
}

void CMario::OnCollisionWithPortal(LPCOLLISIONEVENT e)
{
	if (isTeleporting) return;

	CPortal* p = (CPortal*)e->obj;

	int dir = (e->ny > 0) ? -1 : 1;	// đụng dưới -> lên, đụng trên -> xuống
	float distance = (level == MARIO_LEVEL_SMALL) ? MARIO_SMALL_BBOX_HEIGHT :MARIO_BIG_BBOX_HEIGHT;

	if (p->GetDesX() == -1) p->SetSceneId(-1);
	else
	{
		desX = p->GetDesX();
		desY = p->GetDesY();
	}

	p->SetPosition(-10, -10);
	StartTeleport(dir, p->GetSceneId(), distance);
}

//
// Get animation ID for small Mario
//
int CMario::GetAniIdSmall()
{
	int aniId = -1;
	if (this->GetState() == MARIO_STATE_TELEPORT)
		aniId = ID_ANI_MARIO_SMALL_TELEPORT;

	else
	if (!isOnPlatform)
	{
		if (abs(ax) == MARIO_ACCEL_RUN_X)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_SMALL_JUMP_RUN_RIGHT;
			else
				aniId = ID_ANI_MARIO_SMALL_JUMP_RUN_LEFT;
		}
		else
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_SMALL_JUMP_WALK_RIGHT;
			else
				aniId = ID_ANI_MARIO_SMALL_JUMP_WALK_LEFT;
		}
	}
	else
		if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_SIT_RIGHT;
			else
				aniId = ID_ANI_MARIO_SIT_LEFT;
		}
		else
			if (vx == 0)
			{
				if (nx > 0) aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;
				else aniId = ID_ANI_MARIO_SMALL_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				if (ax < 0)
					aniId = ID_ANI_MARIO_SMALL_BRACE_RIGHT;
				else if (ax == MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_SMALL_RUNNING_RIGHT;
				else if (ax == MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_SMALL_WALKING_RIGHT;
			}
			else // vx < 0
			{
				if (ax > 0)
					aniId = ID_ANI_MARIO_SMALL_BRACE_LEFT;
				else if (ax == -MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_SMALL_RUNNING_LEFT;
				else if (ax == -MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_SMALL_WALKING_LEFT;
			}

	if (aniId == -1) aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;

	return aniId;
}

int CMario::GetAniIdFly()
{
	int aniId = -1;
	if (this->GetState() == MARIO_STATE_TELEPORT)
		aniId = ID_ANI_MARIO_BIG_FLY_TELEPORT;

	else
	if (!isOnPlatform)
	{
		if (abs(ax) == MARIO_ACCEL_RUN_X || isFly || isGlide)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_BIG_FLY_JUMP_RUN_RIGHT;
			else
				aniId = ID_ANI_MARIO_BIG_FLY_JUMP_RUN_LEFT;
		}
		else
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_BIG_FLY_JUMP_WALK_RIGHT;
			else
				aniId = ID_ANI_MARIO_BIG_FLY_JUMP_WALK_LEFT;
		}
	}
	else
		if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_BIG_FLY_SIT_RIGHT;
			else
				aniId = ID_ANI_MARIO_BIG_FLY_SIT_LEFT;
		}
		else
			if (vx == 0)
			{
				if (nx > 0) aniId = ID_ANI_MARIO_BIG_FLY_IDLE_RIGHT;
				else aniId = ID_ANI_MARIO_BIG_FLY_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				if (ax < 0)
					aniId = ID_ANI_MARIO_BIG_FLY_BRACE_RIGHT;
				else if (ax == MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_BIG_FLY_RUNNING_RIGHT;
				else if (ax == MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_BIG_FLY_WALKING_RIGHT;
			}
			else // vx < 0
			{
				if (ax > 0)
					aniId = ID_ANI_MARIO_BIG_FLY_BRACE_LEFT;
				else if (ax == -MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_BIG_FLY_RUNNING_LEFT;
				else if (ax == -MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_BIG_FLY_WALKING_LEFT;
			}

	if (isTailHit) aniId = (nx >= 0) ? ID_ANI_MARIO_BIG_FLY_TAIL_HIT_RIGHT : ID_ANI_MARIO_BIG_FLY_TAIL_HIT_LEFT;
	if (aniId == -1) aniId = ID_ANI_MARIO_BIG_FLY_IDLE_RIGHT;

	return aniId;
}


//
// Get animdation ID for big Mario
//
int CMario::GetAniIdBig()
{
	int aniId = -1;
	if (this->GetState() == MARIO_STATE_TELEPORT)
		aniId = ID_ANI_MARIO_TELEPORT;

	else
	if (!isOnPlatform)
	{
		if (abs(ax) == MARIO_ACCEL_RUN_X)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_JUMP_RUN_RIGHT;
			else
				aniId = ID_ANI_MARIO_JUMP_RUN_LEFT;
		}
		else
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_JUMP_WALK_RIGHT;
			else
				aniId = ID_ANI_MARIO_JUMP_WALK_LEFT;
		}
	}
	else
		if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_SIT_RIGHT;
			else
				aniId = ID_ANI_MARIO_SIT_LEFT;
		}
		else
			if (vx == 0)
			{
				if (nx > 0) aniId = ID_ANI_MARIO_IDLE_RIGHT;
				else aniId = ID_ANI_MARIO_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				if (ax < 0)
					aniId = ID_ANI_MARIO_BRACE_RIGHT;
				else if (ax == MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_RUNNING_RIGHT;
				else if (ax == MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_WALKING_RIGHT;
			}
			else // vx < 0
			{
				if (ax > 0)
					aniId = ID_ANI_MARIO_BRACE_LEFT;
				else if (ax == -MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_RUNNING_LEFT;
				else if (ax == -MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_WALKING_LEFT;
			}

	if (aniId == -1) aniId = ID_ANI_MARIO_IDLE_RIGHT;

	return aniId;
}

void CMario::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = -1;

	if (state == MARIO_STATE_DIE)
		aniId = ID_ANI_MARIO_DIE;
	else if (level == MARIO_LEVEL_BIG)
		aniId = GetAniIdBig();
	else if (level == MARIO_LEVEL_SMALL)
		aniId = GetAniIdSmall();
	else if (level == MARIO_LEVEL_FLY)
		aniId = GetAniIdFly();

	bool skipRender = (untouchable && state != MARIO_STATE_TELEPORT &&
		((GetTickCount64() / 100) % 2 == 0));

	if (skipRender) return;

	auto ani = animations->Get(aniId);
	if (!ani)
	{
		DebugOut(L"[ERROR] Animation %d not found\n", aniId);
		return;
	}
	ani->Render(x, y);

	//RenderBoundingBox();
	
	
}

void CMario::SetState(int state)
{
	// DIE is the end state, cannot be changed! 
	if (this->state == MARIO_STATE_DIE) return;
	if (this->state == MARIO_STATE_TELEPORT && isTeleporting) return;

	switch (state)
	{
	case MARIO_STATE_RUNNING_RIGHT:
		if (isSitting) break;
		maxVx = MARIO_RUNNING_SPEED;
		ax = MARIO_ACCEL_RUN_X;
		nx = 1;
		break;
	case MARIO_STATE_RUNNING_LEFT:
		if (isSitting) break;
		maxVx = -MARIO_RUNNING_SPEED;
		ax = -MARIO_ACCEL_RUN_X;
		nx = -1;
		break;
	case MARIO_STATE_WALKING_RIGHT:
		if (isSitting) break;
		maxVx = MARIO_WALKING_SPEED;
		ax = MARIO_ACCEL_WALK_X;
		nx = 1;
		break;
	case MARIO_STATE_WALKING_LEFT:
		if (isSitting) break;
		maxVx = -MARIO_WALKING_SPEED;
		ax = -MARIO_ACCEL_WALK_X;
		nx = -1;
		break;
	case MARIO_STATE_JUMP:
		if (isSitting) break;
		if (isOnPlatform)
		{
			isOnPlatform = false;
			if (abs(this->vx) == MARIO_RUNNING_SPEED)
				vy = -MARIO_JUMP_RUN_SPEED_Y;
			else
				vy = -MARIO_JUMP_SPEED_Y;
		}
		break;

	case MARIO_STATE_RELEASE_JUMP:
		isOnPlatform = true;
		if (vy < 0) vy += MARIO_JUMP_SPEED_Y / 2;
		break;

	case MARIO_STATE_FLY:
		if (isSitting) break;

		isFly = true;
		isOnPlatform = false;
		if (abs(this->vx) == MARIO_RUNNING_SPEED)
			vy = -MARIO_RUNNING_SPEED;
		else
			vy = -MARIO_WALKING_SPEED;

		break;

	case MARIO_STATE_RELEASE_FLY:
		isFly = false;
		isOnPlatform = true;
		if (vy < 0) vy += MARIO_JUMP_SPEED_Y / 2;
		break;

	case MARIO_STATE_SIT:
		if (isOnPlatform && level != MARIO_LEVEL_SMALL)
		{
			state = MARIO_STATE_IDLE;
			isSitting = true;
			vx = 0; vy = 0.0f;
			y +=MARIO_SIT_HEIGHT_ADJUST;
		}
		break;

	case MARIO_STATE_SIT_RELEASE:
		if (isSitting)
		{
			isSitting = false;
			state = MARIO_STATE_IDLE;
			y -= MARIO_SIT_HEIGHT_ADJUST;
		}
		break;

	case MARIO_STATE_IDLE:
		ax = 0.0f;
		vx = 0.0f;
		break;
		
	case MARIO_STATE_TELEPORT:
		ax = vx = 0.0f;
		break;

	case MARIO_STATE_DIE:
		CGame::GetInstance()->ShowRetryPrompt();
		life--;
		vy = -MARIO_JUMP_DEFLECT_SPEED;
		vx = 0;
		ax = 0;
		break;
	}

	CGameObject::SetState(state);
}

void CMario::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	if (level==MARIO_LEVEL_BIG || level == MARIO_LEVEL_FLY)
	{
		if (isSitting)
		{
			left = x - MARIO_BIG_SITTING_BBOX_WIDTH / 2;
			top = y - MARIO_BIG_SITTING_BBOX_HEIGHT / 2;
			right = left + MARIO_BIG_SITTING_BBOX_WIDTH;
			bottom = top + MARIO_BIG_SITTING_BBOX_HEIGHT;
		}
		else 
		{
			left = x - MARIO_BIG_BBOX_WIDTH/2;
			top = y - MARIO_BIG_BBOX_HEIGHT/2;
			right = left + MARIO_BIG_BBOX_WIDTH;
			bottom = top + MARIO_BIG_BBOX_HEIGHT;
		}
	}
	else
	{
		left = x - MARIO_SMALL_BBOX_WIDTH/2;
		top = y - MARIO_SMALL_BBOX_HEIGHT/2;
		right = left + MARIO_SMALL_BBOX_WIDTH;
		bottom = top + MARIO_SMALL_BBOX_HEIGHT;
	}

	if (holdingShell)
	{
		if (nx > 0)  right += SHELL_BBOX_W;     // hướng phải
		else         left -= SHELL_BBOX_W;     // hướng trái
	}
}

void CMario::SetLevel(int l)
{
	// Adjust position to avoid falling off platform
	if (this->level == MARIO_LEVEL_SMALL)
	{
		y -= (MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT) / 2;
	}
	level = l;
}

