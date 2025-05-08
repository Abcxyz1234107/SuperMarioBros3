#pragma once
#include "Goomba.h"

#define SHELL_BBOX_W 15
#define SHELL_BBOX_H 15

#define SHELL_STATE_SLEEP 100
#define SHELL_SLEEP_TIMEOUT 500

class CKoopasShell :
    public CGoomba
{
private:

public:
	CKoopasShell(float x, float y) : CGoomba(x, y)
	{

	}
	void GetBoundingBox(float& left, float& top, float& right, float& bottom) override;
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) override;
	void Render() override;

	void OnNoCollision(DWORD dt) override;
	void OnCollisionWith(LPCOLLISIONEVENT e) override;

	int IsCollidable() override { return 1; };
	int IsBlocking() override { return 0; }
};

