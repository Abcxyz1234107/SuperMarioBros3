#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "CRandomBrick.h"

#define ID_ANI_COIN 11000
#define	COIN_WIDTH 10
#define COIN_BBOX_WIDTH 10
#define COIN_BBOX_HEIGHT 16


class CRandomCoin :
    public CGameObject
{
private:
	void OnCollisionWithRandomBrick(LPCOLLISIONEVENT e);

public:
	CRandomCoin(float x, float y) : CGameObject(x, y)
	{
		vy = 0.0f;
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }
	int IsCollidable() override { return 1; }

	void OnNoCollision(DWORD dt) override;
	void OnCollisionWith(LPCOLLISIONEVENT e) override;
};

