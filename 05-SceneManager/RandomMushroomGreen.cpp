#include "RandomMushroomGreen.h"

void CRandomMushroomGreen::Render()
{
	CSprites* sprite = CSprites::GetInstance();
	sprite->Get(ID_SPRITE_GREEN_RANDOMMUSHROOM)->Draw(x, y);

	//RenderBoundingBox();
}

void CRandomMushroomGreen::OnCollisionWith(LPCOLLISIONEVENT e)
{
    CGoomba::OnCollisionWith(e);
    if (dynamic_cast<CMario*>(e->obj) && !emerging)
        OnCollisionWithMario(e);
}
void CRandomMushroomGreen::OnCollisionWithMario(LPCOLLISIONEVENT e)
{
    this->Delete();
    CMario* mario = dynamic_cast<CMario*>(e->obj);
    mario->SetScore(mario->GetScore() + 1000);
    mario->SetLife(mario->GetLife() + 1);
}