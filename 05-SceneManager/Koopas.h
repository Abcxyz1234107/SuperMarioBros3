#pragma once
#include "Goomba.h"
#include "KoopasShell.h"

class CKoopas :
    public CGoomba
{
private:
	float spawnX, spawnY;

	bool sleep = false;  // Koopas 'ngủ' sau khi chết
	bool passedSpawn = false;

public:
    CKoopas(float x, float y) : CGoomba(x, y)
    {
		spawnX = x;
		spawnY = y;
    }

	void GetBoundingBox(float& left, float& top, float& right, float& bottom) override;
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) override;
	void Render() override;

	void OnNoCollision(DWORD dt) override;
	void OnCollisionWith(LPCOLLISIONEVENT e) override;

	int IsCollidable() override { return 1; };
	int IsBlocking() override { return 0; }
};

