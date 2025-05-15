#include "RandomMushroom.h"
#include "Mario.h"

void CRandomMushroom::Render()
{
	CSprites* sprite = CSprites::GetInstance();
	sprite->Get(ID_SPRITE_RANDOMUSHROOM)->Draw(x, y);

	//RenderBoundingBox();
}
void CRandomMushroom::OnCollisionWith(LPCOLLISIONEVENT e)
{
    CGoomba::OnCollisionWith(e);
    if (dynamic_cast<CMario*>(e->obj) && !emerging)
        OnCollisionWithMario(e);
}
void CRandomMushroom::OnCollisionWithMario(LPCOLLISIONEVENT e)
{
    this->Delete();
    CMario* mario = dynamic_cast<CMario*>(e->obj);
    if (mario->GetLevel() == MARIO_LEVEL_SMALL)
    {
        mario->SetScore(mario->GetScore() + 1000);
        mario->SetLevel(MARIO_LEVEL_BIG);
    }
}
void CRandomMushroom::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
    if (emerging)
    {
        y += vy * dt;

        // Khi đã trồi ra khỏi bounding box viên gạch
        if (spawnY - y >= RandomMushroom_BBOX_HEIGHT)
        {
            emerging = false;
            // Bật lại chuyển động bình thường
            vx = MUSHROOM_WALKING_SPEED * nx;
            ay = GOOMBA_GRAVITY;
        }
    }
    else
    {
        // Sau khi trồi xong, dùng cơ chế di chuyển của Goomba
        CGoomba::Update(dt, coObjects);
    }
}

void CRandomMushroom::GetBoundingBox(float& l, float& t, float& r, float& b)
{
    l = x - RandomMushroom_BBOX_WIDTH / 2;
    t = y - RandomMushroom_BBOX_HEIGHT / 2;
    r = l + RandomMushroom_BBOX_WIDTH;
    b = t + RandomMushroom_BBOX_HEIGHT;
}