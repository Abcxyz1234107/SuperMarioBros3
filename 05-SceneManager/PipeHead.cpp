#include "PipeHead.h"

void CPipeHead::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_PIPEHEAD)->Render(x, y);
	//RenderBoundingBox();
}

void CPipeHead::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - PIPEHEAD_BBOX_WIDTH / 2;
	t = y - PIPEHEAD_BBOX_HEIGHT / 2;
	r = l + PIPEHEAD_BBOX_WIDTH;
	b = t + PIPEHEAD_BBOX_HEIGHT;
}