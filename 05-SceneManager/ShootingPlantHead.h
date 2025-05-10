#pragma once
#include "GameObject.h"
#define SHOOTINGPLANT_HEAD_W  16
#define SHOOTINGPLANT_HEAD_H  16

class CShootingPlantHead : 
	public CGameObject
{
private:
	int orient; 
	bool useStatic = false;
	int  staticSpriteId = -1;
	// 0‑BottomLeft 
	// 1‑TopRight
	// 2‑TopLeft
	// 3‑BottomRight
public:
	CShootingPlantHead(float x, float y) : CGameObject(x, y) 
	{
		z = 2;
		this->orient = 0;
	}

	void SetOrient(int o) { orient = o; }
	int GetOrient() { return orient; }
	void UseStatic(int id) { useStatic = true;  staticSpriteId = id; }
	void ClearStatic() { useStatic = false; }
	void Render();
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};

