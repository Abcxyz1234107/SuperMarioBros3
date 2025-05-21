#pragma once
#include "GameObject.h"
#include "Game.h"

/* khoảng cách giữa các chữ số (pixel) */
#define SB_DIGIT_W   8

#define SB_MAX_TIME     300 //s
#define SB_SCORE_X       -35
#define SB_COIN_X        5
#define SB_LIFE_X        -100
#define SB_TIMER_X       5
#define SB_TEXT_Y        -1

#define SB_POWER_X       -83


class CScoreBoard :
    public CGameObject
{
private:
    float offsetX;     // vị trí cố định trên màn hình
    float offsetY;

    ULONGLONG timer;
    int coin;
    long long score;
    int life;

    int power;
    bool powerFull;

public:
    CScoreBoard(float x, float y) : CGameObject(x, y), offsetX(x), offsetY(y)
    {
        SetZ(5);
    }

    void Render();
    void GetBoundingBox(float& l, float& t, float& r, float& b) override {}

    void SetCoin(int c) { coin = c; }
    void SetScore(int c) { score = c; }
    void SetLife(int c) { life = c; }

    void DrawNumber(long long value, int fixedDigits, float rightX, float y);
};

