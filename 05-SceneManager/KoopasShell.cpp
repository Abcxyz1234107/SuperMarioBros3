#include "KoopasShell.h"

void CKoopasShell::Render()
{
    CSprites* sprite = CSprites::GetInstance();
    sprite->Get(ID_SPRITE_KOOPAS_SHELL)->Draw(x, y);
}
void CKoopasShell::OnCollisionWith(LPCOLLISIONEVENT e)
{
    CGoomba::OnCollisionWith(e);
}
void CKoopasShell::OnNoCollision(DWORD dt)
{
    CGoomba::OnNoCollision(dt);
}

void CKoopasShell::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
    vx += ax * dt;
    CGoomba::Update(dt, coObjects);
}

void CKoopasShell::GetBoundingBox(float& l, float& t, float& r, float& b)
{
    l = x - SHELL_BBOX_W / 2;
    t = y - SHELL_BBOX_H / 2;
    r = l + SHELL_BBOX_W;
    b = t + SHELL_BBOX_H;
}