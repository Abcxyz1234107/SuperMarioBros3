#pragma once
#include "GameObject.h"
#include "Character.h" 

class Character;

#define GOOMBA_GRAVITY 0.002f
#define GOOMBA_WALKING_SPEED 0.05f


#define GOOMBA_BBOX_WIDTH 16
#define GOOMBA_BBOX_HEIGHT 14
#define GOOMBA_BBOX_HEIGHT_DIE 7

#define GOOMBA_DIE_TIMEOUT 500

#define GOOMBA_STATE_WALKING 100
#define GOOMBA_STATE_DIE 200
#define GOOMBA_STATE_SLEEPING 300
#define GOOMBA_STATE_FLIPPED  400

#define ID_ANI_GOOMBA_WALKING 5000
#define ID_ANI_GOOMBA_DIE 5001
#define ID_ANI_GOOMBA_FLIPPED  5700

class CGoomba : public CGameObject
{
protected:
	bool spawned = false;
	bool hitByTail = false;

	float ax;				
	float ay; 

	ULONGLONG die_start;

	Character* character;

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render();

	virtual int IsCollidable() { return spawned ? 1 : 0; }
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public: 	
	CGoomba(float x, float y);
	virtual void SetState(int state);

	void AddCharacter(int c);
	void RenderCharacter();

	void setHitByTail(bool i) { hitByTail = i; }
	bool isHitByTail() { return hitByTail; }
};