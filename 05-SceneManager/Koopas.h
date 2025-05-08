#pragma once
#include "Goomba.h"

class CKoopas :
    public CGoomba
{
private:

public:
    CKoopas(float x, float y) : CGoomba(x, y)
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

