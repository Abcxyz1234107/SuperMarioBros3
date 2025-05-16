#include "ButtonCoinBrick.h"
#include "PlayScene.h"

void ButtonCoinBrick::Render()
{
    CAnimations* animations = CAnimations::GetInstance();

    if (GetState() != CB_STATE_TOUCHED)
        animations->Get(ID_ANI_COINBRICK)->Render(x, y);
    else
    {
        CSprites* s = CSprites::GetInstance();
        s->Get(ID_SPRITE_ACTIVATED)->Draw(x, y);
    }
    //RenderBoundingBox();
}

void ButtonCoinBrick::Activate()
{
    if (this->GetState() != CB_STATE_TOUCHED)
    {
        LPPLAYSCENE scene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
        CMario* mario = (CMario*)scene->GetPlayer();

        SetState(CB_STATE_TOUCHED);

        Button* b = new Button(x, y - 16.0f);
        b->SetVy(-0.15f);
        scene->AddObject(b);
    }
}