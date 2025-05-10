#pragma once
#include "Platform.h"

class CVoidSpike :
    public CPlatform
{

public:
	CVoidSpike(float x, float y,
		float cell_width, float cell_height, int length,
		int sprite_id_begin, int isAni = 0)
		: CPlatform(x, y, cell_width, cell_height, length, sprite_id_begin, sprite_id_begin,
			sprite_id_begin)
	{

	}

	
};

