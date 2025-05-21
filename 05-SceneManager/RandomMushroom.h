#pragma once
#include "Goomba.h"
#include <vector>

#define RandomMushroom_BBOX_WIDTH 10
#define RandomMushroom_BBOX_HEIGHT 16
#define MUSHROOM_EMERGE_SPEED       0.01f
#define MUSHROOM_WALKING_SPEED      0.1f

class CRandomMushroom :
    public CGoomba
{
protected:
	float spawnY;    
	bool emerging; // flag cho biết đang trồi lên

	virtual void OnCollisionWithMario(LPCOLLISIONEVENT e);
public:
	CRandomMushroom(float x, float y) : CGoomba(x, y)
	{
		z = 1;
		spawnY = y;
		emerging = true;
		vy = -MUSHROOM_EMERGE_SPEED;  // đi lên từ từ
		vx = 0;                       // chưa di chuyển trong khi đang trồi
		ay = 0;                       // vô hiệu trọng lực lúc trồi
		nx = 1;
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) override;
	virtual void Render();
	void GetBoundingBox(float& l, float& t, float& r, float& b);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e) override;
	bool IsEmerging() { return emerging; }
};

