#include "Button.h"
#include "ButtonCoinBrick.h"
#include "PlayScene.h"

void Button::Render()
{
    CAnimations* animations = CAnimations::GetInstance();
    animations->Get(ID_ANI_BUTTON)->Render(x, y);

    //RenderBoundingBox();
}

void Button::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - B_W / 2;
	t = y - B_H / 2;
	r = l + B_W;
	b = t + B_H;
}

void Button::Activate()
{
	this->Delete();

    CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
    vector<LPGAMEOBJECT> coObjects = scene->GetObjects();
    for (LPGAMEOBJECT obj : coObjects)
    {
        if (obj == dynamic_cast<CoinBrick*>(obj))
        {
            CoinBrick* cb = (CoinBrick*)obj;
            if (cb != dynamic_cast<ButtonCoinBrick*>(cb)) cb->ChangeToCoin();
        }
    }
}