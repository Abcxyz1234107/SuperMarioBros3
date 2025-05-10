#pragma once
#include "Platform.h"
#include "Animation.h"
#include "Animations.h"

#define BGCLOUD_WIDTH 16
#define BGCLOUD_BBOX_WIDTH 16
#define BGCLOUD_BBOX_HEIGHT 16

class CBGCloud : public CPlatform
{
public:
	CBGCloud(float x, float y,
		float cell_width, float cell_height, int length,
		int sprite_id_begin, int sprite_id_middle, int sprite_id_end,
		int isAni = 0)
		: CPlatform(x, y, cell_width, cell_height, length, sprite_id_begin, sprite_id_middle,
			sprite_id_end)
	{

	}

	void GetBoundingBox(float& l, float& t, float& r, float& b) override {}
	int IsDirectionColliable(float nx, float ny) override { return 0; }
};

