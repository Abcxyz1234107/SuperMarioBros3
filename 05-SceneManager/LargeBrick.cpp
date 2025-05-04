#include "LargeBrick.h"
#include "Textures.h"
#include "Game.h"

void CLargeBrick::Render()
{
	CSprites* sprite = CSprites::GetInstance();
	sprite->Get(spriteID)->Draw(x, y);
	//RenderBoundingBox();
}

void CLargeBrick::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - bboxWidth / 2;
	t = y - bboxHeight / 2;
	r = l + bboxWidth;
	b = t + bboxHeight;
}

int CLargeBrick::IsDirectionColliable(float nx, float ny)
{
	if (nx == 0 && ny == -1) return 1;
	else return 0;
}