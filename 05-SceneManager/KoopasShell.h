#pragma once
#include "Goomba.h"
#include "CRandomBrick.h"

#define SHELL_BBOX_W 15
#define SHELL_BBOX_H 15
#define SHELL_MOVE_SPEED 0.25f 
#define SHELL_DESPAWN_DISTANCE 240.0f
#define SHELL_STATE_NORMAL 101
#define SHELL_STATE_REVIVING 102

#define SHELL_REVIVE_TIMEOUT    9000       // 5 s hoàn toàn tỉnh lại
#define SHELL_REVIVE_WARNING    3000       // 1,5 s cuối bắt đầu rung
#define SHELL_SHAKE_SPEED       0.01f


class CKoopasShell :
    public CGoomba
{
private:
	bool       isHeld;
	ULONGLONG  revive_start = 0;

	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithRandomBrick(LPCOLLISIONEVENT e);

public:
	CKoopasShell(float x, float y) : CGoomba(x, y)
	{
		vx = ax = 0.0f;          
		isHeld = false;
		revive_start = GetTickCount64();
	}
	void GetBoundingBox(float& left, float& top, float& right, float& bottom) override;
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) override;
	void Render() override;

	void OnNoCollision(DWORD dt) override;
	void OnCollisionWith(LPCOLLISIONEVENT e) override;
	
	void SetState(int state) override;

	int IsCollidable() override { return 1; };
	int IsBlocking() override { return 0; }

	void Activate(float dir); //direction
	float GetVx() { return vx; }

	void SetHeld();       // gán / hủy trạng thái được cầm
	bool IsHeld() { return isHeld; }
};

