#include "KoopasShell.h"
#include "PlayScene.h"

#define SHELL_BBOX_W 15
#define SHELL_BBOX_H 15

#define SHELL_MOVE_SPEED 0.25f 
#define SHELL_DESPAWN_DISTANCE 240.0f
#define SHELL_STATE_DIE 101
#define SHELL_STATE_REVIVING 102

#define SHELL_REVIVE_TIMEOUT    9000       // 5 s hoàn toàn tỉnh lại
#define SHELL_REVIVE_WARNING    3000       // 1,5 s cuối bắt đầu rung
#define SHELL_SHAKE_SPEED       0.01f

void CKoopasShell::Render()
{
    if (state == SHELL_STATE_DIE)
    {
        CSprites* sprite = CSprites::GetInstance();
        sprite->Get(ID_SPRITE_KOOPAS_SHELL)->Draw(x, y);
    }
    else
    {
        CAnimations* animation = CAnimations::GetInstance();
        animation->Get(ID_ANI_KOOPAS_SHELL_RESPAWN)->Render(x, y);
    }
}

void CKoopasShell::Activate(float dir)
{
    vx = dir * SHELL_MOVE_SPEED;
    revive_start = 0;               // khi mai lăn thì huỷ timer
}

void CKoopasShell::SetHeld()
{
    isHeld = true;
    vx = ax = 0;  // đứng yên
    vy = 0;
}

void CKoopasShell::OnCollisionWith(LPCOLLISIONEVENT e)
{
    CGoomba::OnCollisionWith(e);

    if (dynamic_cast<CGoomba*>(e->obj))
        OnCollisionWithGoomba(e);
    else if (dynamic_cast<CRandomBrick*>(e->obj))
        OnCollisionWithRandomBrick(e);
}

void CKoopasShell::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
    dynamic_cast<CGoomba*>(e->obj)->SetState(GOOMBA_STATE_DIE);
}
void CKoopasShell::OnCollisionWithRandomBrick(LPCOLLISIONEVENT e)
{
    dynamic_cast<CRandomBrick*>(e->obj)->Activate();
}

void CKoopasShell::OnNoCollision(DWORD dt)
{
    x += vx * dt;
    y += vy * dt;
}

void CKoopasShell::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
    LPPLAYSCENE scene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
    CMario* mario = (CMario*)scene->GetPlayer();
    bool isReviving = (isHeld || vx == 0);

    if (isReviving)
    {
        if (revive_start == 0) revive_start = GetTickCount64();

        ULONGLONG elapsed = GetTickCount64() - revive_start;

        /* 1. Hiệu ứng rung & đổi animation trong 1,5 s cuối */
        if (elapsed >= SHELL_REVIVE_TIMEOUT - SHELL_REVIVE_WARNING - 500)
        {
            float dir = ((elapsed / 100) & 1) ? 1.f : -1.f;
            x += dir * SHELL_SHAKE_SPEED * dt;

            if (elapsed >= SHELL_REVIVE_TIMEOUT - SHELL_REVIVE_WARNING)
                if (state != SHELL_STATE_REVIVING) this->SetState(SHELL_STATE_REVIVING);
        }
        else
        {
            if (state != SHELL_STATE_DIE) this->SetState(SHELL_STATE_DIE);
            vx = 0;  // đứng yên
        }

        /* 2. Hết thời gian -> biến lại Koopas */
        if (elapsed >= SHELL_REVIVE_TIMEOUT)
        {
            scene->AddObject(new CKoopas(x, y - SHELL_BBOX_H));
            isDeleted = true;
            return;
        }
    }
    else revive_start = 0;      // mai đang lăn -> reset timer

    // khi được Mario cầm
    if (isHeld && mario)
    {
        x = mario->GetX() + (mario->GetNx() > 0 ? SHELL_BBOX_W : -SHELL_BBOX_W);
        y = mario->GetY() - SHELL_BBOX_H / 2;;

        // thả mai rùa khi Mario không còn giữ nút chạy
        if (abs(mario->GetAx()) != MARIO_ACCEL_RUN_X)
        {
            isHeld = false;
            vx = mario->GetNx() * SHELL_MOVE_SPEED;
        }
        return;
    }

    vx += ax * dt;
    vy += ay * dt;
    CGoomba::Update(dt, coObjects);

    // despawn
    if (abs(mario->GetX() - this->x) > SHELL_DESPAWN_DISTANCE)
    {
        isDeleted = true;
        return;
    }
}

void CKoopasShell::GetBoundingBox(float& l, float& t, float& r, float& b)
{
    l = x - SHELL_BBOX_W / 2;
    t = y - SHELL_BBOX_H / 2;
    r = l + SHELL_BBOX_W;
    b = t + SHELL_BBOX_H - 1;
}

void CKoopasShell::SetState(int state)
{
    CGoomba::SetState(state);
    switch (state)
    {
    case SHELL_STATE_REVIVING:
        break;

    case SHELL_STATE_DIE:
        vx = vy = 0;
        break;
    }
}