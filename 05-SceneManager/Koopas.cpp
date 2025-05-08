#include "Koopas.h"

#include "RandomMushroom.h"
#include "Mario.h"
#include "PlayScene.h"

#define KOOPAS_BBOX_W 15
#define KOOPAS_BBOX_H 25

#define KOOPAS_STATE_SLEEP 100
#define KOOPAS_SLEEP_TIMEOUT 500

void CKoopas::Render()
{
    CAnimations* animations = CAnimations::GetInstance();
    int aniId = -1;
    
    if (vx >= 0)
        aniId = ID_ANI_KOOPAS_WALK_RIGHT;
    else
        aniId = ID_ANI_KOOPAS_WALK_LEFT;

    animations->Get(aniId)->Render(x, y);
}
void CKoopas::OnCollisionWith(LPCOLLISIONEVENT e)
{
    CGoomba::OnCollisionWith(e);
}
void CKoopas::OnNoCollision(DWORD dt)
{
    CGoomba::OnNoCollision(dt);
}

void CKoopas::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
    if ((state == GOOMBA_STATE_DIE))
    {
        isDeleted = true;
        CKoopasShell* shell = new CKoopasShell(this->GetX(), this->GetY());
        shell->SetVx(0.25f);
        LPPLAYSCENE currentScene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
        currentScene->AddObject(shell);
        return;
    }
    CGoomba::Update(dt, coObjects);
}

void CKoopas::GetBoundingBox(float& l, float& t, float& r, float& b)
{
    l = x - KOOPAS_BBOX_W / 2;
    t = y - KOOPAS_BBOX_H / 2;
    r = l + KOOPAS_BBOX_W;
    b = t + KOOPAS_BBOX_H;
}