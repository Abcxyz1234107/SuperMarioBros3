#include "Koopas.h"

#include "RandomMushroom.h"
#include "Mario.h"
#include "PlayScene.h"

void CKoopas::Render()
{
    if (sleep) return; // ẩn khi đang 'ngủ'

    CAnimations* animations = CAnimations::GetInstance();
    int aniId = (vx >= 0) ? ID_ANI_KOOPAS_WALK_RIGHT : ID_ANI_KOOPAS_WALK_LEFT;
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
    LPPLAYSCENE scene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
    CMario*     mario = (CMario*)scene->GetPlayer();
    float       camW = (float)CGame::GetInstance()->GetBackBufferWidth();

    /* 1. Bị dẫm  ->  sinh vỏ & chuyển sang sleep */
    if (state == GOOMBA_STATE_DIE && sleep == false)
    {
        scene->AddObject(new CKoopasShell(x, y));
        sleep = true;
        vx = vy = 0;
        return;  // Koopa 'biến mất'
    }

    /* 2. chờ Mario đi rồi quay lại để respawn */
    if (sleep)
    {
        if (!passedSpawn && (mario->GetX() - spawnX) > camW * 0.6)
            passedSpawn = true;  // vượt qua 0.6 màn hình

        /* Khi Mario quay lại */
        if (passedSpawn && abs(mario->GetX() - spawnX) < camW)
        {
            x = spawnX;                         // reset vị trí gốc
            y = spawnY;
            this->ay = GOOMBA_GRAVITY;
            SetState(GOOMBA_STATE_WALKING);

            sleep = false;
            passedSpawn = false;
        }
        return;
    }

    /* 3. Xử lý gốc */
    CGoomba::Update(dt, coObjects);
}

void CKoopas::GetBoundingBox(float& l, float& t, float& r, float& b)
{
    l = x - KOOPAS_BBOX_W / 2;
    t = y - KOOPAS_BBOX_H / 2;
    r = l + KOOPAS_BBOX_W;
    b = t + KOOPAS_BBOX_H - 1;
}