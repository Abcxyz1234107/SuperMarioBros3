#pragma once
#include "GameObject.h"

#define LEAF_BBOX_W 16
#define LEAF_BBOX_H 14

class CRandomLeaf :
    public CGameObject
{
public:
    CRandomLeaf(float x, float y) : CGameObject(x, y)
    {
        
    }

    void Render() override;
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }
	int IsCollidable() override { return 1; }

	void OnNoCollision(DWORD dt) override;
	void OnCollisionWith(LPCOLLISIONEVENT e) override;
};

