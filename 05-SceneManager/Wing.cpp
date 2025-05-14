#include "Wing.h"

void CWing::AddCharacter(int c) { LPPLAYSCENE currentScene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene(); character = new Character(x, y, c); currentScene->AddObject(character); }
void CWing::RenderCharacter() { if (!character) return; if (character->IsDeleted()) { character = nullptr;  return; } character->Render(); }


void CWing::Render()
{
    CAnimations* animations = CAnimations::GetInstance();
    int aniId = (position == 1) ? ID_ANI_WING_LEFT
        : ID_ANI_WING_RIGHT;

    if (isStatic) 
    {
        aniId = (position == 1) ? ID_ANI_STATIC_WING_LEFT
            : ID_ANI_STATIC_WING_RIGHT;
    }

    animations->Get(aniId)->Render(x, y);

    RenderCharacter();
}

void CWing::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

}

void CWing::GetBoundingBox(float& l, float& t, float& r, float& b)
{
    l = x - WING_BBOX_W / 2;
    t = y - WING_BBOX_H / 2;
    r = l + WING_BBOX_W;
    b = t + WING_BBOX_H;
}