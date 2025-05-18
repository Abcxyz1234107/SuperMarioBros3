#pragma once
#include "GameObject.h"
#define SHOOTINGPLANTBULLET_W 8
#define SHOOTINGPLANTBULLET_H 8
#define SHOOTINGPLANT_BULLET_SPEED 0.075f

class CShootingPlantBullet :
    public CGameObject
{
private:
    void OnCollisionWithMario(LPCOLLISIONEVENT e);

public:
    CShootingPlantBullet(float x, float y, float vvx, float vvy)
         : CGameObject(x, y) 
    {
        vx = vvx;
        vy = vvy;
    }

    void Update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects) override;
    void Render() override;
    void GetBoundingBox(float& left, float& top, float& right, float& bottom) override;

    void OnNoCollision(DWORD dt);
    void OnCollisionWith(LPCOLLISIONEVENT e);

    int IsCollidable() override { return 0; } 
    int IsBlocking()   override { return 0; }
};

