#pragma once
#include "GameObject.h"
#define SHOOTINGPLANTBULLET_W 8
#define SHOOTINGPLANTBULLET_H 8
#define SHOOTINGPLANT_BULLET_SPEED 0.05f

class CShootingPlantBullet :
    public CGameObject
{
private:
    float vx, vy;

    void OnCollisionWithMario(LPCOLLISIONEVENT e);

public:
    CShootingPlantBullet(float x, float y, float vx, float vy)
         : CGameObject(x, y), vx(vx), vy(vy) {}

    void Update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects = nullptr) override;
    void Render() override;
    void GetBoundingBox(float& left, float& top, float& right, float& bottom) override;
    void OnNoCollision(DWORD dt) override;
    void OnCollisionWith(LPCOLLISIONEVENT e) override;
};

