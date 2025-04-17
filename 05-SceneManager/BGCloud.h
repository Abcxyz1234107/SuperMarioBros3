#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_BGCLOUD 54111
#define BGCLOUD_WIDTH 16
#define BGCLOUD_BBOX_WIDTH 16
#define BGCLOUD_BBOX_HEIGHT 16

class CBGCloud : public CGameObject
{
public:
	CBGCloud(float x, float y) : CGameObject(x, y) {}
	void Render();
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};

