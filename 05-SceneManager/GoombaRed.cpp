#include "GoombaRed.h"
#include "Mario.h"

#define WING_OFFSET 1

void CGoombaRed::AddWing()
{
    if (hasWing) return;
    LPPLAYSCENE s = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();

    leftWing = new CWing(x - GOOMBA_BBOX_WIDTH / 2 + WING_OFFSET, y - GOOMBA_BBOX_HEIGHT / 2, 1);
    rightWing = new CWing(x + GOOMBA_BBOX_WIDTH / 2 - WING_OFFSET, y - GOOMBA_BBOX_HEIGHT / 2, 2);

    s->AddObject(leftWing);
    s->AddObject(rightWing);
    hasWing = true;
}

void CGoombaRed::RemoveWing()
{
    if (!hasWing) return;
    leftWing->Delete();
    rightWing->Delete();
    leftWing = rightWing = nullptr;
    hasWing = false;
}

void CGoombaRed::RenderWing()
{
    if (!hasWing) return;
    if (!leftWing || !rightWing) return;

    leftWing->Render();
    rightWing->Render();
}

void CGoombaRed::UpdateWing()
{
    if (hasWing)
    {
        leftWing->SetPosition(x - GOOMBA_BBOX_WIDTH / 2 + WING_OFFSET, y - GOOMBA_BBOX_HEIGHT / 2);
        rightWing->SetPosition(x + GOOMBA_BBOX_WIDTH / 2 - WING_OFFSET, y - GOOMBA_BBOX_HEIGHT / 2);
    }
}

void CGoombaRed::DetectMario()
{
    ULONGLONG now = GetTickCount64();
    bool inCD = (cycleStart && now - cycleStart < REDGOOMBA_CYCLE_COOLDOWN);

    LPPLAYSCENE scene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
    CMario* mario = (CMario*)scene->GetPlayer();

    float mx, my;  mario->GetPosition(mx, my);
    float dx = mx - x, dy = my - y;
    bool  inRange = (dx * dx + dy * dy) <= detectRange * detectRange;

    if (!hasWing)
    {
        nx = -mario->GetNx();
        return;
    }

    if (inRange)
    {
        if (dx < 0 && vx > 0) vx = -vx;
        if (dx > 0 && vx < 0) vx = -vx;
    }
    if (!inRange || inCD) return;

    // Chu kỳ nhảy
    switch (state)
    {
    case 0:  // bắt đầu
        state = REDGOOMBA_PREPARE_JUMP;
        shortJumpsLeft = REDGOOMBA_SHORT_JUMP_COUNT;
        if (hasWing) { leftWing->SetStatic(false); rightWing->SetStatic(false); }
        vy = -REDGOOMBA_SHORT_JUMP_SPEED;
        shortJumpsLeft--;
        break;

    case REDGOOMBA_PREPARE_JUMP: // nhảy ngắn
        if (vy == 0)
        {
            if (shortJumpsLeft > 0)
            {
                vy = -REDGOOMBA_SHORT_JUMP_SPEED;
                shortJumpsLeft--;
            }
            else
            {
                state = REDGOOMBA_JUMP;
                vy = -REDGOOMBA_HIGH_JUMP_SPEED;
            }
        }
        break;

    case REDGOOMBA_JUMP: // nhảy cao
        if (vy == 0)
        {
            state = 0;
            if (hasWing) { leftWing->SetStatic(true); rightWing->SetStatic(true); }
            cycleStart = now;  // CD 0.5 s
        }
        break;
    }
}

void CGoombaRed::Render()
{
    CAnimations* animations = CAnimations::GetInstance();
    int aniId = (this->GetState() != GOOMBA_STATE_DIE) ? ID_ANI_RED_GOOMBA_WALK 
        : ID_ANI_RED_GOOMBA_DIE;
    animations->Get(aniId)->Render(x, y);

    RenderWing();
    RenderCharacter();
}
void CGoombaRed::OnCollisionWith(LPCOLLISIONEVENT e)
{
    CGoomba::OnCollisionWith(e);
}
void CGoombaRed::OnNoCollision(DWORD dt)
{
    CGoomba::OnNoCollision(dt);
}

void CGoombaRed::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
    CGoomba::Update(dt, coObjects);

    DetectMario();

    UpdateWing();
}

void CGoombaRed::GetBoundingBox(float& l, float& t, float& r, float& b)
{
    l = x - GOOMBA_BBOX_WIDTH / 2;
    t = y - GOOMBA_BBOX_HEIGHT / 2;
    r = l + GOOMBA_BBOX_WIDTH;
    b = t + GOOMBA_BBOX_HEIGHT;
}