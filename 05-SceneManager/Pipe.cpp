#include "Pipe.h"

void CPipe::Render()
{
	this->head->Render();
	this->body->Render();
}

void CPipe::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - totalWidth / 2;
	t = (y+16) - totalHeight / 2;
	r = l + totalWidth;
	b = t + totalHeight;
}