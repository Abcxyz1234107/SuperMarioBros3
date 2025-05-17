#pragma once
#include "Platform.h"
#include "RandomCoin.h"
#include "RandomMushroom.h"
#include "RandomLeaf.h"

#define RB_MAX_Y 8.0f
#define RB_SPEED_Y 0.1f

#define ANI_ID_RANDOMBRICK 20111
#define RANDOMBRICK_STATE_TOUCHED 511
#define ID_SPRITE_RANDOMBRICK_TOUCHED 20105

class CRandomBrick :
    public CPlatform
{
private:
	int type; //1 for coin, 2 for mushroom
	float startY;
	bool  isBouncing = false;

	void OnCollisionWithRandomMushroom(LPCOLLISIONEVENT e);

public:
	CRandomBrick(float x, float y, int type,
		float cell_width = 15, float cell_height = 16, int length = 1,
		int aniIdBegin = 20111, int isAni = 1)
		: CPlatform(x, y, cell_width, cell_height, length, aniIdBegin, aniIdBegin, aniIdBegin, isAni) 
	{
		startY = y;
		this->type = type;
	}
	void SetState(int state);
	void Activate();
	int GetType() { return type; }
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) override;

	void OnCollisionWith(LPCOLLISIONEVENT e);
};

