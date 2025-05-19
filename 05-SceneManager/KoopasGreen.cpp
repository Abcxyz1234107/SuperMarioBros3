#include "KoopasGreen.h"

#define WING_OFFSET 1
#define KG_JUMP 2

#define KG_JUMP_SPEED 0.2f

void CKoopasGreen::AddWing()
{
    RemoveWing();

    LPPLAYSCENE s = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();

    bool goLeft = (vx < 0);
    if (goLeft)
    {
        rightWing = new CWing(
            x + GOOMBA_BBOX_WIDTH / 2 - WING_OFFSET,
            y - GOOMBA_BBOX_HEIGHT / 2 + WING_OFFSET,
            2);
        rightWing->SetStatic(false);
        s->AddObject(rightWing);
    }
    else
    {
        leftWing = new CWing(
            x - GOOMBA_BBOX_WIDTH / 2 + WING_OFFSET,
            y - GOOMBA_BBOX_HEIGHT / 2 + WING_OFFSET,
            1);
        leftWing->SetStatic(false);
        s->AddObject(leftWing);
    }

    hasWing = true;
}

void CKoopasGreen::RemoveWing()
{
    if (!hasWing) return;

    if (leftWing) { leftWing->Delete();  leftWing = nullptr; }
    if (rightWing) { rightWing->Delete(); rightWing = nullptr; }

    hasWing = false;
}

void CKoopasGreen::RenderWing()
{
    if (!hasWing) return;
    if (leftWing)  leftWing->Render();
    if (rightWing) rightWing->Render();
}

void CKoopasGreen::UpdateWing()
{
    if (!hasWing) return;

    /* cập nhật vị trí hiện có */
    if (leftWing)
        leftWing->SetPosition(
            x - GOOMBA_BBOX_WIDTH / 2 + WING_OFFSET,
            y - GOOMBA_BBOX_HEIGHT / 2);

    if (rightWing)
        rightWing->SetPosition(
            x + GOOMBA_BBOX_WIDTH / 2 - WING_OFFSET,
            y - GOOMBA_BBOX_HEIGHT / 2);

    /* nếu hướng thay đổi, tạo cánh mới ở phía tương ứng */
    if (vx < 0 && rightWing)         // đang đi trái nhưng còn cánh phải
    {
        RemoveWing();
        AddWing();                   // tạo cánh bên trái
    }
    else if (vx > 0 && leftWing)     // đang đi phải nhưng còn cánh trái
    {
        RemoveWing();
        AddWing();                   // tạo cánh bên phải
    }
}

void CKoopasGreen::OnCollisionWith(LPCOLLISIONEVENT e)
{
    CKoopas::OnCollisionWith(e);

    if (hasWing && e->ny < 0 && e->obj->IsBlocking())
    {
        vy = -KG_JUMP_SPEED;
    }

    if (hasWing && (e->nx < 0 || e->nx >= 0) && e->obj->IsBlocking())
    {
        AddWing();
    }
}

void CKoopasGreen::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
    LPPLAYSCENE scene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
    CMario* mario = (CMario*)scene->GetPlayer();
    float       camW = (float)CGame::GetInstance()->GetBackBufferWidth();

    if (shell && shell->IsDeleted())
    {
        shell = nullptr;
    }

    /* 1. Turn to Shell */
    if (state == GOOMBA_STATE_DIE && sleep == false)
    {
        CKoopasShell* fakeShell = new CKoopasShell(x, y, type);
        scene->AddObject(fakeShell);
        shell = fakeShell;
        sleep = true;
        vx = vy = 0;
        RemoveWing();
        return;
    }

    /* 2. Respawn */
    if (sleep)
    {
        if (shell) return;

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
            if (allowWing == 1) AddWing();
        }
        return;
    }

    if (hasWing)
        ay = GOOMBA_GRAVITY / 4; 
    else
        ay = GOOMBA_GRAVITY;

    /* 3. Xử lý gốc */
    CGoomba::Update(dt, coObjects);
    UpdateWing();
}

void CKoopasGreen::Render()
{
    if (!spawned) return;
    if (sleep) return; // ẩn khi đang 'ngủ'

    CAnimations* animations = CAnimations::GetInstance();
    int aniId = (vx >= 0) ? ID_ANI_GREEN_KOOPAS_WALK_RIGHT : ID_ANI_GREEN_KOOPAS_WALK_LEFT;
    animations->Get(aniId)->Render(x, y);

    RenderCharacter();
    RenderWing();
}