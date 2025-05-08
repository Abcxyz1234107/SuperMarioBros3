#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_PIPEHEAD 10011
#define PIPEHEAD_WIDTH 16
#define PIPEHEAD_BBOX_WIDTH 28
#define PIPEHEAD_BBOX_HEIGHT 16

class CPipeHead :
    public CGameObject
{
private:
public:
	CPipeHead(float x, float y) : CGameObject(x, y) 
	{
	}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};

