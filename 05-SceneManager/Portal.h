#pragma once

#include "GameObject.h"

/*
	Object that triggers scene switching
*/
class CPortal : public CGameObject
{
	int scene_id;	// target scene to switch to 
public:
	CPortal(float l, float t, int scene_id);
	void Render();
	void GetBoundingBox(float &l, float &t, float &r, float &b);

	void RenderBoundingBox();
	
	int GetSceneId() { return scene_id;  }
	int IsBlocking() { return 0; }
};