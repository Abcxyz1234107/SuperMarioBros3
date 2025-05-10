#include "RandomLeaf.h"

void CRandomLeaf::Render()
{
	CSprites* sprite = CSprites::GetInstance();
	sprite->Get(ID_SPRITE_RANDOMLEAF)->Draw(x, y);
	//RenderBoundingBox();
}

void CRandomLeaf::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += 0.0005f * dt;

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CRandomLeaf::OnNoCollision(DWORD dt)
{
	y += vy * dt;
}

void CRandomLeaf::OnCollisionWith(LPCOLLISIONEVENT e)
{
	
}

void CRandomLeaf::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - LEAF_BBOX_W / 2;
	t = y - LEAF_BBOX_H / 2;
	r = l + LEAF_BBOX_W;
	b = t + LEAF_BBOX_H;
}