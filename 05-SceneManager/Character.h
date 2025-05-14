#pragma once
#include "GameObject.h"
#include "PlayScene.h"

#define C_100 10100
#define C_1000 10110
#define C_200 10200
#define C_2000 10220

#define C_SPEED 0.05f
#define C_TIMEOUT 750

#define C_SLOWING 0.92f  // hệ số làm chậm
#define C_MIN_VY  0.002f  // ngưỡng xóa chữ

class Character :
    public CGameObject
{
private:
    int score;
    ULONGLONG timer;

public:
    Character(float x, float y, int score) : CGameObject(x, y)
    {
        timer = GetTickCount64();
        this->score = score;
        vy = C_SPEED;
    }

    void Render();
    void Update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects) override;
    void GetBoundingBox(float& l, float& t, float& b, float& r) override {}

    void OnNoCollision(DWORD dt);
};

