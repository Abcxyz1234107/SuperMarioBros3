#pragma once
#include "GameObject.h"
#define width 16
#define height 16

class CShootingPlantHead : 
	public CGameObject
{
public:
	CShootingPlantHead(int x, int y) : CGameObject(x, y) 
	{}

	void Render();
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};

