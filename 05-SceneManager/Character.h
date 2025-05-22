#pragma once
#include "GameObject.h"
#include "PlayScene.h"

#define C_100 10100
#define C_1000 10110
#define C_200 10200
#define C_2000 10220

#define C_0 10300
#define C_1 10301
#define C_2 10302
#define C_3 10303
#define C_4 10304
#define C_5 10305
#define C_6 10306
#define C_7 10307
#define C_8 10308
#define C_9 10309

#define C_1UP 10710

#define C_ARROW_BLACK 10310
#define C_ARROW_WHITE 10311

#define C_POWER_BLACK 10312
#define C_POWER_WHITE 10313

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

