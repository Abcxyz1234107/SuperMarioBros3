#include "Coin.h"

void CCoin::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_COIN)->Render(x, y);

	//RenderBoundingBox();
}

void CCoin::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - COIN_BBOX_WIDTH / 2;
	t = y - COIN_BBOX_HEIGHT / 2;
	r = l + COIN_BBOX_WIDTH;
	b = t + COIN_BBOX_HEIGHT;
}

void CCoin::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
    vy += 0.001f * dt;
    y += vy * dt;

    vector<LPCOLLISIONEVENT> coEvents;
    vector<LPCOLLISIONEVENT> coEventsResult;
    coEvents.clear();

    CCollision::GetInstance()->Scan(this, dt, coObjects, coEvents);

    if (coEvents.size() == 0)
    {
        x += vx * dt;
        y += vy * dt;
    }
    else
    {
        LPCOLLISIONEVENT colX = nullptr;
        LPCOLLISIONEVENT colY = nullptr;

        CCollision::GetInstance()->Filter(this, coEvents, colX, colY, 1, 0, 1); // chỉ filter Y

        if (colY != nullptr)
        {
            if (dynamic_cast<CRandomBrick*>(colY->obj) && colY->ny < 0)
                this->Delete();
        }

        y += vy * dt;
    }

    for (auto& e : coEvents) delete e;
}


void CCoin::OnCollisionWith(LPCOLLISIONEVENT e)
{
    // Nếu va chạm với CRandomBrick từ trên xuống (ny < 0) => coin biến mất
    if (dynamic_cast<CRandomBrick*>(e->obj) && e->ny < 0)
    {
        this->Delete();
    }
}