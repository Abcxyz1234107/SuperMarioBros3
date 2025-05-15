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

    int        coin = mario->GetCoin();
    long long  score = mario->GetScore();
    int        life = mario->GetLife();

    const float offset_text_Y = drawY + SB_TEXT_Y;

    // Score
    DrawNumber(score, 7, drawX + SB_SCORE_X, offset_text_Y);

    // Life
    DrawNumber(life, 1, drawX + SB_LIFE_X, offset_text_Y);

    // Coin
    DrawNumber(coin, 1, drawX + SB_COIN_X, offset_text_Y - 8);

    // Timer
    ULONGLONG elapsedMs = GetTickCount64() - timer;
    int elapsedSec = int(elapsedMs / 1000);
    int remain = max(0, SB_MAX_TIME - elapsedSec);
    DrawNumber(remain, 3, drawX + SB_TIMER_X, offset_text_Y);

    if (remain <= 0) mario->SetState(MARIO_STATE_DIE);
}