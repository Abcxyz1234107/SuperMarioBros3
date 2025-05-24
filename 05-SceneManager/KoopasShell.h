#pragma once
#include "Goomba.h"

#define SHELL_BBOX_W 15
#define SHELL_BBOX_H 15
#define SHELL_MOVE_SPEED 0.25f 
#define SHELL_DESPAWN_DISTANCE 240.0f
#define SHELL_STATE_NORMAL 101
#define SHELL_STATE_REVIVING 102
#define SHELL_STATE_PRE_REVIVING 103

#define SHELL_REVIVE_TIMEOUT    9000       // 9 s hoàn toàn tỉnh lại
#define SHELL_REVIVE_PREWARNING 500 
#define SHELL_REVIVE_WARNING    3000       // 3 s cuối đổi thành animation
#define SHELL_SHAKE_SPEED       0.01f


class CKoopasShell :
    public CGoomba
{
private:
	bool       isHeld;
	ULONGLONG  revive_start = 0;

	int aniId;
	int spriteId;
	int type = 0;

	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithRandomBrick(LPCOLLISIONEVENT e);
	void OnCollisionWithCoinBrick(LPCOLLISIONEVENT e);

public:
	CKoopasShell(float x, float y, int type = 0) : CGoomba(x, y)
	{
		vx = vy = ax = 0.0f;    
		ay = GOOMBA_GRAVITY;
		isHeld = false;
		revive_start = GetTickCount64();
		this->type = type;

		if (type == 0)
		{
			spriteId = ID_SPRITE_KOOPAS_SHELL;
			aniId = ID_ANI_KOOPAS_SHELL_RESPAWN;
		}
		else 
		{
			spriteId = ID_SPRITE_GREEN_KOOPAS_SHELL;
			aniId = ID_ANI_GREEN_KOOPAS_SHELL_RESPAWN;
		}
	}
	void GetBoundingBox(float& left, float& top, float& right, float& bottom) override;
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) override;
	void Render() override;

	void OnNoCollision(DWORD dt) override;
	void OnCollisionWith(LPCOLLISIONEVENT e) override;
	
	void SetState(int state) override;

	int IsCollidable() override { return 1; };
	int IsBlocking() override { return 1; }

	void Activate(float dir); //direction
	float GetVx() { return vx; }

	void SetHeld();       // gán / hủy trạng thái được cầm
	bool IsHeld() { return isHeld; }
};

