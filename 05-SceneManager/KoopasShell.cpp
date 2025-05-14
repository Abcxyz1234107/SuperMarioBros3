#include "KoopasShell.h"
#include "CRandomBrick.h"
#include "VoidSpike.h"
#include "CoinBrick.h"
#include "PlayScene.h"
#include "Koopas.h"

void CKoopasShell::Render()
{
    if (state == SHELL_STATE_REVIVING)
    {
        CAnimations* animation = CAnimations::GetInstance();
        animation->Get(ID_ANI_KOOPAS_SHELL_RESPAWN)->Render(x, y);
    }
    else
    {
        CSprites* sprite = CSprites::GetInstance();
        sprite->Get(ID_SPRITE_KOOPAS_SHELL)->Draw(x, y);
    }

    RenderCharacter();
}

void CKoopasShell::Activate(float dir)
{
    isHeld = false;
    vx = dir * SHELL_MOVE_SPEED;
    this->SetState(SHELL_STATE_NORMAL);
    revive_start = 0;
}

void CKoopasShell::SetHeld()
{
    isHeld = true;
    vx = ax = 0;
    vy = 0;
}

void CKoopasShell::OnCollisionWith(LPCOLLISIONEVENT e)
{
    CGoomba::OnCollisionWith(e);

    if (dynamic_cast<CGoomba*>(e->obj))
        OnCollisionWithGoomba(e);
    else if (dynamic_cast<CRandomBrick*>(e->obj))
        OnCollisionWithRandomBrick(e);
    else if (dynamic_cast<CoinBrick*>(e->obj))
        OnCollisionWithCoinBrick(e);
    else if (dynamic_cast<CVoidSpike*>(e->obj))
        this->Delete();
}

void CKoopasShell::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
    AddCharacter(C_100);
    dynamic_cast<CGoomba*>(e->obj)->SetState(GOOMBA_STATE_DIE);
}

void CKoopasShell::OnCollisionWithRandomBrick(LPCOLLISIONEVENT e)
{
    dynamic_cast<CRandomBrick*>(e->obj)->Activate();
}

void CKoopasShell::OnCollisionWithCoinBrick(LPCOLLISIONEVENT e)
{
    if (vx != 0 && (e->nx < 0 || e->nx > 0))
        dynamic_cast<CoinBrick*>(e->obj)->Activate();
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

        /* 1. Hiệu ứng rung trong 3.5s cuối & đổi animation trong 3 s cuối */
        if (elapsed >= SHELL_REVIVE_TIMEOUT - SHELL_REVIVE_WARNING - SHELL_REVIVE_PREWARNING)
        {
            float dir = ((elapsed / 100) & 1) ? 1.f : -1.f;
            x += dir * SHELL_SHAKE_SPEED * dt;

            if (elapsed >= SHELL_REVIVE_TIMEOUT - SHELL_REVIVE_WARNING)
                if (state != SHELL_STATE_REVIVING) this->SetState(SHELL_STATE_REVIVING);
        }
        else
        {
            if (state != SHELL_STATE_NORMAL) this->SetState(SHELL_STATE_NORMAL);
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

        // thả mai rùa
        if (abs(mario->GetAx()) != MARIO_ACCEL_RUN_X)
        {
            isHeld = false;
            mario->SetHoldingShell(false);
            //mario->StartUntouchable();

            float dir = mario->GetNx();
            x = mario->GetX() + dir * (SHELL_BBOX_W - 2); //đẩy vỏ ra 2px để tránh kẹt

            this->Activate(dir);
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

    case SHELL_STATE_NORMAL:
        break;
    }
}