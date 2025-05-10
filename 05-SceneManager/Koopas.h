#pragma once
#include "Goomba.h"
#include "KoopasShell.h"

#define KOOPAS_BBOX_W 15
#define KOOPAS_BBOX_H 25

#define KOOPAS_STATE_SLEEP 100
#define KOOPAS_SLEEP_TIMEOUT 500

class CKoopas :
    public CGoomba
{
private:
	CKoopasShell* shell = nullptr;

	float spawnX, spawnY;

	bool sleep = false;  // Koopas 'ngủ' sau khi chết
	bool passedSpawn = false;

	bool HasGroundAhead(vector<LPGAMEOBJECT>* coObjects, float dx);

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

