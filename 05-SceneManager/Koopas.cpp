#include "Koopas.h"

#include "RandomMushroom.h"
#include "Mario.h"

#define KOOPAS_BBOX_W 15
#define KOOPAS_BBOX_H 25

void CKoopas::Render()
{
    CAnimations* animations = CAnimations::GetInstance();
    int aniId = -1;
    
    if (vx >= 0)
        aniId = ID_ANI_KOOPAS_WALK_RIGHT;
    else
        aniId = ID_ANI_KOOPAS_WALK_LEFT;

    if (state == GOOMBA_STATE_DIE)
    {
        aniId = ID_ANI_KOOPAS_SHELL_RESPAWN;
    }

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
    CGoomba::Update(dt, coObjects);
}

void CKoopas::GetBoundingBox(float& l, float& t, float& r, float& b)
{
    l = x - KOOPAS_BBOX_W / 2;
    t = y - KOOPAS_BBOX_H / 2;
    r = l + KOOPAS_BBOX_W;
    b = t + KOOPAS_BBOX_H;
}