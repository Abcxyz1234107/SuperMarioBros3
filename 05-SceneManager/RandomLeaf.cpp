﻿#include "RandomLeaf.h"
#include "Mario.h"

void CRandomLeaf::Render()
{
	CSprites* sprite = CSprites::GetInstance();
	sprite->Get(ID_SPRITE_RANDOMLEAF)->Draw(x, y);

	if (!character) return;
	if (character->IsDeleted()) { character = nullptr;  return; }

	character->Render();
	//RenderBoundingBox();
}

void CRandomLeaf::AddCharacter(int c)
{
	LPPLAYSCENE currentScene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
	character = new Character(x, y, c);
	currentScene->AddObject(character);
}

void CRandomLeaf::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (state == LEAF_STATE_RISING)
	{
		vy += LEAF_GRAVITY * dt;
		if (vy >= 0)   // đã đạt đỉnh, chuyển sang rơi
		{
			vy = LEAF_FALL_SPEED_MAX;
			SetState(LEAF_STATE_FALLING_LEFT);
		}
	}
	else  // đang lượn
	{
		vy += LEAF_GRAVITY * dt;
		if (vy > LEAF_FALL_SPEED_MAX) vy = LEAF_FALL_SPEED_MAX;

		if (state == LEAF_STATE_FALLING_LEFT && x <= xPivot - LEAF_AMPLITUDE)
			SetState(LEAF_STATE_FALLING_RIGHT);
		else if (state == LEAF_STATE_FALLING_RIGHT && x >= xPivot + LEAF_AMPLITUDE)
			SetState(LEAF_STATE_FALLING_LEFT);
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CRandomLeaf::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void CRandomLeaf::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<CMario*>(e->obj))
	{
		CMario* mario = (CMario*)e->obj;
		if (mario->GetLevel() < MARIO_LEVEL_FLY)
			mario->SetLevel(mario->GetLevel() + 1);

		mario->SetScore(mario->GetScore() + 1000);
		AddCharacter(C_1000);

		this->Delete();
	}
}

void CRandomLeaf::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - LEAF_BBOX_W / 2;
	t = y - LEAF_BBOX_H / 2;
	r = l + LEAF_BBOX_W;
	b = t + LEAF_BBOX_H - 1;
}

void CRandomLeaf::SetState(int state)
{
	this->state = state;

	switch (state)
	{
	case LEAF_STATE_RISING:
		vx = 0.0f;
		break;

	case LEAF_STATE_FALLING_LEFT:
		vx = -LEAF_FALL_SPEED_X;
		xPivot = x;
		break;

	case LEAF_STATE_FALLING_RIGHT:
		vx = LEAF_FALL_SPEED_X;
		xPivot = x;
		break;
	}
}