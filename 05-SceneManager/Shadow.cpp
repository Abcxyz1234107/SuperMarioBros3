#include "Shadow.h"
#include "Game.h"
#include "debug.h"

void Shadow::Render()
{
	CSprites* sprite = CSprites::GetInstance();
	float drawX = x;
	float drawY = y;

	if (owner)
	{
		drawX = owner->GetX() + offsetX;
		drawY = owner->GetY() + offsetY;
	}
	
	if (color == 1)
		sprite->Get(spriteId)->Draw(drawX, drawY, black);
	else
		sprite->Get(spriteId)->Draw(drawX, drawY, white);
}