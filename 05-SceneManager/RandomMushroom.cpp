#include "RandomMushroom.h"

void CRandomMushroom::Render()
{
	CSprites* sprite = CSprites::GetInstance();
	sprite->Get(ID_SPRITE_RANDOMUSHROOM)->Draw(x, y);

	//RenderBoundingBox();
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