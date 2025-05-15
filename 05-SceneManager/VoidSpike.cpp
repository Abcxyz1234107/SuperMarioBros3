#include "VoidSpike.h"

void CVoidSpike::Render()
{
	CSprites* s = CSprites::GetInstance();
	float xx = x;
	for (size_t i = 0; i < length; i++)
	{
		s->Get(ID_VOIDSPIKE)->Draw(xx, y);
		xx += VS_W;
	}
	
}

void CVoidSpike::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - VS_W / 2;
	t = y - VS_H / 2;
	r = l + VS_W * length;
	b = t + VS_H;
}