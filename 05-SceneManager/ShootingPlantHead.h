#pragma once
#include "GameObject.h"
#define SHOOTINGPLANT_HEAD_W  16
#define SHOOTINGPLANT_HEAD_H  16

class CShootingPlantHead : 
	public CGameObject
{
private:
	int orient; 
	// 0‑BottomLeft 
	// 1‑TopRight
	// 2‑TopLeft
	// 3‑BottomRight
public:
	CShootingPlantHead(int x, int y) : CGameObject(x, y) 
	{
		this->orient = 0;
	}

	void SetOrient(int o) { orient = o; }
	int GetOrient() { return orient; }
	void Render();
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};

