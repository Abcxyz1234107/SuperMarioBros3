#pragma once
#include "Goomba.h"
#define RandomMushroom_BBOX_WIDTH 10
#define RandomMushroom_BBOX_HEIGHT 16

class CRandomMushroom :
    public CGoomba
{
private:

public:
	CRandomMushroom(float x, float y) : CGoomba(x, y)
	{

	}
	void Render() override;
};

