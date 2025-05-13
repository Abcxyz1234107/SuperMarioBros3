#include "Shadow.h"
#include "Game.h"
#include "debug.h"

void Shadow::Update(DWORD dt)
{
	this->x = owner->GetX() + Shadow_x;
	this->y = owner->GetY() + Shadow_y;
}

void Shadow::Render()
{
	CSprites* sprite = CSprites::GetInstance();
	float drawX = owner->GetX() + Shadow_x;
	float drawY = owner->GetY() + Shadow_y;
	sprite->Get(spriteId)->Draw(drawX, drawY, D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
}