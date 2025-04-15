#include "RandomMushroom.h"

void CRandomMushroom::Render()
{
	CSprites* sprite = CSprites::GetInstance();
	sprite->Get(ID_SPRITE_RANDOMUSHROOM)->Draw(x, y);

	//RenderBoundingBox();
}