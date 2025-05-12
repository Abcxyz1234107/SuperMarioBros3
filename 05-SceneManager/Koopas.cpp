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
    CMario* mario = (CMario*)scene->GetPlayer();
    float       camW = (float)CGame::GetInstance()->GetBackBufferWidth();
    /* 1. Turn to Shell */
    if (state == GOOMBA_STATE_DIE && sleep == false)
    {
        CKoopasShell* fakeShell = new CKoopasShell(x, y);
        scene->AddObject(fakeShell);
        sleep = true;
        vx = vy = 0;
        return;
    }

    /* 2. Respawn */
    if (sleep)
    {
        if (!passedSpawn && abs(mario->GetX() - spawnX) > camW * 0.51)
            passedSpawn = true;

        if (passedSpawn && abs(mario->GetX() - spawnX) < camW)
        {
            x = spawnX;
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

    /* 4. Quay đầu */
    float dx = vx * dt; //Khoảng cách bước tiêp theo

    if (vy == 0 && HasGroundAhead(coObjects, dx))
        vx = -vx;
}

void CKoopas::GetBoundingBox(float& l, float& t, float& r, float& b)
{
    l = x - KOOPAS_BBOX_W / 2;
    t = y - KOOPAS_BBOX_H / 2;
    r = l + KOOPAS_BBOX_W;
    b = t + KOOPAS_BBOX_H - 1;
}

bool CKoopas::HasGroundAhead(vector<LPGAMEOBJECT>* coObjects, float dx)
{
    float l, t, r, b;
    GetBoundingBox(l, t, r, b);

    float nextL = l + dx;
    float nextR = r + dx;
    float probeX = (dx > 0) ? nextR + 1.0f : nextL - 1.0f;
    float probeY = b + 2.0f;

    for (LPGAMEOBJECT obj : *coObjects)
    {
        if (!obj->IsBlocking()) continue;

        float ol, ot, orr, ob;
        obj->GetBoundingBox(ol, ot, orr, ob);

        if (probeX >= ol - 10 && probeX <= orr + 10 && probeY >= ot && probeY <= ot + 3.0f)
            return false;
    }
    return true; // không có nền -> mép
}