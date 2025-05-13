#include "Shadow.h"
#include "Game.h"
#include "debug.h"

void Shadow::Update(DWORD dt)
{
	this->x = owner->GetX() + offsetX;
	this->y = owner->GetY() + offsetY;
}

void Shadow::Render()
{
	CSprites* sprite = CSprites::GetInstance();
	float drawX = owner->GetX() + offsetX;
	float drawY = owner->GetY() + offsetY;
	sprite->Get(spriteId)->Draw(drawX, drawY, D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
}