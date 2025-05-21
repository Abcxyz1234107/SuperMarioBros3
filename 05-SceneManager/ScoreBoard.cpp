#include "ScoreBoard.h"
#include "Game.h"
#include "Mario.h"
#include "PlayScene.h"

void CScoreBoard::DrawNumber(long long value, int digitLength, float xx, float yy)
{
    for (int i = 0; i < digitLength; ++i)
    {
        int digit = int(value % 10);
        value /= 10;

        float drawX = xx - i * SB_DIGIT_W;
        CSprites::GetInstance()->Get(C_0 + digit)->Draw(drawX, yy);
    }
}

void CScoreBoard::Render()
{
    //Lấy tọa độ cam và render ngay lập tức để tránh độ trễ
    float camX, camY;
    CGame::GetInstance()->GetCamPos(camX, camY);

    const float drawX = camX + offsetX;
    const float drawY = camY + offsetY;

    CSprites::GetInstance()->Get(SCOREBOARD_ID)->Draw(drawX, drawY);

    LPPLAYSCENE scene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
    CMario* mario = (CMario*)scene->GetPlayer();
    if (!mario) return;

    coin = mario->GetCoin();
    score = mario->GetScore();
    life = mario->GetLife();
    timer = mario->GetTimer();

    power = mario->GetPower();
    powerFull = mario->IsPowerFull();

    const float offset_text_Y = drawY + SB_TEXT_Y;

    // Score
    DrawNumber(score, 7, drawX + SB_SCORE_X, offset_text_Y);

    // Life
    DrawNumber(life, 1, drawX + SB_LIFE_X, offset_text_Y);

    // Coin
    DrawNumber(coin, 2, drawX + SB_COIN_X, offset_text_Y - 8);

    // Timer
    DrawNumber(timer, 3, drawX + SB_TIMER_X, offset_text_Y);

    power = mario->GetPower();
    powerFull = mario->IsPowerFull();
    bool isFlying = mario->IsFly();

    for (int i = 0; i < MARIO_POWER_MAX; ++i)
    {
        int spr = (i < power) ? C_ARROW_WHITE : C_ARROW_BLACK;
        CSprites::GetInstance()->Get(spr) ->Draw(drawX + SB_POWER_X + i * SB_DIGIT_W, offset_text_Y - 8);
    }
    /* Chữ P */
    const int P_FLASH_TIME = 120; // ms
    ULONGLONG now = GetTickCount64();
    ULONGLONG lastPress = mario->GetLastFlyPress();
    bool pActive = powerFull && (now - lastPress <= P_FLASH_TIME);

    int sprP = pActive ? C_POWER_WHITE : C_POWER_BLACK;
    CSprites::GetInstance()->Get(sprP) ->Draw(drawX + SB_POWER_X + MARIO_POWER_MAX * SB_DIGIT_W + 5, offset_text_Y - 8);
}