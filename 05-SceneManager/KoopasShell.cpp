#include "KoopasShell.h"
#include "PlayScene.h"

void CKoopasShell::Render()
{
    CSprites* sprite = CSprites::GetInstance();
    sprite->Get(ID_SPRITE_KOOPAS_SHELL)->Draw(x, y);
}

void CKoopasShell::Activate(float dir)
{
    vx = dir * SHELL_MOVE_SPEED;
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
    y += vy * dt;
}

void CKoopasShell::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
    LPPLAYSCENE scene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
    CMario* mario = (CMario*)scene->GetPlayer();

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
    b = t + SHELL_BBOX_H;
}