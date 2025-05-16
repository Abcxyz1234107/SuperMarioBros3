#include "BlackPipe.h"

void CBlackPipe::Render()
{
	CSprites* s = CSprites::GetInstance();
	s->Get(ID_SPRITE_BP)->Draw(x, y);
	//RenderBoundingBox();
}

void CBlackPipe::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - BP_W / 2;
	t = y - BP_H / 2;
	r = l + BP_W;
	b = t + BP_H;
}