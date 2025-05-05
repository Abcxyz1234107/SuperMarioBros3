#pragma once
#include "Platform.h"

class CBGBush :
    public CPlatform
{
public:
	CBGBush(float x, float y, int length,
		float cell_width = 16, float cell_height = 1, 
		int sprite_id_begin = 54301)
		: CPlatform(x, y, cell_width, cell_height, length, sprite_id_begin, sprite_id_begin,
			sprite_id_begin) 
	{
		z = 0;
	}

	void GetBoundingBox(float& l, float& t, float& r, float& b) {}
	void RenderBoundingBox() {}
	int IsDirectionColliable(float nx, float ny) { return 0; }
};

