#include "BGTreeHead.h"

void BGTreeHead::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_TREEHEAD)->Render(x, y);
	//RenderBoundingBox();
}