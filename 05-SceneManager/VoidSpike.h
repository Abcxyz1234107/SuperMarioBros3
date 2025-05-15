#pragma once
#include "Platform.h"

#define ID_VOIDSPIKE 99990
#define VS_W 525
#define VS_H 10

class CVoidSpike :
    public CGameObject
{
private:
	int length;

public:
	CVoidSpike(float x, float y, int length): CGameObject(x, y)
	{
		this->length = length;
	}

	void Render();
	void GetBoundingBox(float& l, float& t, float& r, float& b) override;
};

