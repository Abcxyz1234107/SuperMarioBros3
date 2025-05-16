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

    const float offset_text_Y = drawY + SB_TEXT_Y;

    // Score
    DrawNumber(score, 7, drawX + SB_SCORE_X, offset_text_Y);

    // Life
    DrawNumber(life, 1, drawX + SB_LIFE_X, offset_text_Y);

    // Coin
    DrawNumber(coin, 1, drawX + SB_COIN_X, offset_text_Y - 8);

    // Timer
    DrawNumber(timer, 3, drawX + SB_TIMER_X, offset_text_Y);
}