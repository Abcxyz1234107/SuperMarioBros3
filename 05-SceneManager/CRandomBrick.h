#pragma once
#include "Platform.h"

#define ANI_ID_RANDOMBRICK 20111
#define RANDOMBRICK_STATE_TOUCHED 511
#define ID_SPRITE_RANDOMBRICK_TOUCHED 20105

class CRandomBrick :
    public CPlatform
{
public:
	CRandomBrick(float x, float y,
		float cell_width = 16, float cell_height = 16, int length = 1,
		int aniIdBegin = 20111, int isAni = 1)
		: CPlatform(x, y, cell_width, cell_height, length, aniIdBegin, aniIdBegin, aniIdBegin, isAni) {}
	void SetState(int state);
	int IsBlocking() override { return 1; }
};

