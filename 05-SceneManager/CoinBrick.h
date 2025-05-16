#pragma once
#include "GameObject.h"

#define COINBRICK_BBOX_W 16
#define COINBRICK_BBOX_H 16

#define CB_MAX_Y 8.0f
#define CB_SPEED_Y 0.1f

#define CB_STATE_TOUCHED 1

class CoinBrick :
    public CGameObject
{
protected:
    float startY;
    bool  isBouncing = false;

public:
    CoinBrick(float x, float y) : CGameObject(x, y)
    {
        startY = y;
    }

    
    void GetBoundingBox(float& l, float& t, float& r, float& b) override;
    void SetState(int state);
    void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) override;

    virtual void Render();
    virtual void Activate();

    void ChangeToCoin();
    void Bounce();
};

