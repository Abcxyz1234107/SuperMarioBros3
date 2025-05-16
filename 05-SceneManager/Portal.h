#pragma once

#include "GameObject.h"

/*
	Object that triggers scene switching
*/
class CPortal : public CGameObject
{
	int scene_id;	// target scene to switch to 
	float desX, desY;

public:
	CPortal(float l, float t, float desX, float desY, int scene_id);
	void Render();
	void GetBoundingBox(float &l, float &t, float &r, float &b);

	void RenderBoundingBox();
	
	int GetSceneId() { return scene_id;  }
	int IsBlocking() { return 0; }

	float GetDesX() { return desX; }
	float GetDesY() { return desY; }

	void SetSceneId(int i) { scene_id = i; }
};