#pragma once
#include "Platform.h"
#define ANI_ID_RANDOMBRICK 20111

class CRandomBrick :
    public CPlatform
{
public:
	CRandomBrick(float x, float y,
		float cell_width, float cell_height, int length,
		int aniIdBegin, int aniIdMiddle, int aniIdEnd, int isAni = 1)
		: CPlatform(x, y, cell_height, cell_height, length, aniIdBegin, aniIdMiddle, aniIdEnd, isAni) {}
};

