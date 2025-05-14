#include "RandomCoin.h"
#include "CRandomBrick.h"
#include "debug.h"

void CRandomCoin::Render()
{
    CAnimations* animations = CAnimations::GetInstance();
    animations->Get(ID_ANI_COIN)->Render(x, y);

    if (!character) return; 
    if (character->IsDeleted()) { character = nullptr;  return; } 

    character->Render();

    //RenderBoundingBox();
}

void CRandomCoin::AddCharacter(int c)
{
    LPPLAYSCENE currentScene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
    character = new Character(x, y, c);
    currentScene->AddObject(character);
}


void CRandomCoin::GetBoundingBox(float& l, float& t, float& r, float& b)
{
    l = x - COIN_BBOX_WIDTH / 2;
    t = y - COIN_BBOX_HEIGHT / 2;
    r = l + COIN_BBOX_WIDTH;
    b = t + COIN_BBOX_HEIGHT - 2;
}

void CRandomCoin::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
    vy += 0.0005f * dt;

    CGameObject::Update(dt, coObjects);
    CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CRandomCoin::OnNoCollision(DWORD dt)
{
    y += vy * dt;
}

void CRandomCoin::OnCollisionWith(LPCOLLISIONEVENT e)
{
    if (dynamic_cast<CRandomBrick*>(e->obj))
        OnCollisionWithRandomBrick(e);
}

void CRandomCoin::OnCollisionWithRandomBrick(LPCOLLISIONEVENT e)
{
    AddCharacter(C_100);
    this->Delete();
}