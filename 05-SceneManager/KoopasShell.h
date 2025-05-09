#pragma once
#include "Goomba.h"
#include "CRandomBrick.h"

#define SHELL_BBOX_W 15
#define SHELL_BBOX_H 15

#define SHELL_MOVE_SPEED 0.25f 
#define SHELL_DESPAWN_DISTANCE 240.0f
#define SHELL_STATE_SLEEP 100
#define SHELL_SLEEP_TIMEOUT 500

class CKoopasShell :
    public CGoomba
{
private:
	bool isHeld;

	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithRandomBrick(LPCOLLISIONEVENT e);

public:
	CKoopasShell(float x, float y) : CGoomba(x, y)
	{
		vx = 0.0f;          
		ax = 0.0f;

		isHeld = false;
	}
	void GetBoundingBox(float& left, float& top, float& right, float& bottom) override;
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) override;
	void Render() override;

	void OnNoCollision(DWORD dt) override;
	void OnCollisionWith(LPCOLLISIONEVENT e) override;

	int IsCollidable() override { return 1; };
	int IsBlocking() override { return 0; }

	void Activate(float dir); //direction
	float GetVx() { return vx; }

	void SetHeld();       // gán / hủy trạng thái được cầm
	bool IsHeld() { return isHeld; }
};

