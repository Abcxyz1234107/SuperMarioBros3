#include "BGBrick.h"


void CBGBrick::Render()
{
	CSprites* sprite = CSprites::GetInstance();
	sprite->Get(ID_SPRITE_BGBRICK)->Draw(x, y);
}