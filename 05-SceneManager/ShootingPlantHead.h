﻿#pragma once
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

	int type = 2;
public:
	CShootingPlantHead(float x, float y, int type = 2) : CGameObject(x, y)
	{
		z = 2;
		orient = 0;
		this->type = type;
	}

	void SetOrient(int o) { orient = o; }
	int GetOrient() { return orient; }
	int GetType() { return type; }
	void UseStatic(int id) { useStatic = true;  staticSpriteId = id; }
	void ClearStatic() { useStatic = false; }
	void Render();
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};

