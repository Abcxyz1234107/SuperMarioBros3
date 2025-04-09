#pragma once
#include "Platform.h"

class CBGBush :
    public CPlatform
{
public:
	CBGBush(float x, float y,
		float cell_width, float cell_height, int length,
		int sprite_id_begin)
		: CPlatform(x, y, cell_width, cell_height, length, sprite_id_begin, sprite_id_begin,
			sprite_id_begin) {}

	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void RenderBoundingBox();
	int IsDirectionColliable(float nx, float ny);
};

