#pragma once
#include "GameObject.h"
#include "Character.h"

class Character;

#define LEAF_BBOX_W 16
#define LEAF_BBOX_H 14

#define LEAF_GRAVITY           0.0002f
#define LEAF_RISE_SPEED        0.25f
#define LEAF_FALL_SPEED_MAX    0.05f
#define LEAF_FALL_SPEED_X      0.04f // tốc độ lượn ngang
#define LEAF_AMPLITUDE         24.0f // biên độ dao động trái-phải

#define LEAF_STATE_RISING          0
#define LEAF_STATE_FALLING_LEFT    1
#define LEAF_STATE_FALLING_RIGHT   2

 
class CRandomLeaf :
    public CGameObject
{
private:
	int   state;
	float xPivot;  // gốc để đo biên dao động

	Character* character;
public:
    CRandomLeaf(float x, float y) : CGameObject(x, y)
    {
		state = LEAF_STATE_RISING;
		xPivot = x;
		vx = 0.0f;
		vy = -LEAF_RISE_SPEED;
		character = nullptr;
    }

    void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }
	int IsCollidable() override { return 0; }

	void OnNoCollision(DWORD dt) override;
	void OnCollisionWith(LPCOLLISIONEVENT e) override;

	void SetState(int state) override;

	void AddCharacter(int c);
};

