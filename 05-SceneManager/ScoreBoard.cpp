#include "ScoreBoard.h"
#include "Game.h"
#include "Mario.h"
#include "PlayScene.h"

void CScoreBoard::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
    
}

void CScoreBoard::Render()
{
    //Lấy tọa độ cam và render ngay lập tức để tránh độ trễ
    float camX, camY;
    CGame::GetInstance()->GetCamPos(camX, camY);

    const float drawX = camX + offsetX;
    const float drawY = camY + offsetY;

    CSprites::GetInstance()->Get(SCOREBOARD_ID)->Draw(drawX, drawY);
}