#include "PipeBody.h"
#include "Sprites.h"
#include "Animations.h"
#include "Game.h"

void CPipeBody::Render()
{
    if (this->length <= 0) return;

    float yy = y;
    CSprites* s = CSprites::GetInstance();

    yy += this->cellHeight;
    for (int i = 0; i < this->length; i++)
    {
        s->Get(this->spriteId)->Draw(x, yy);
        yy += this->cellHeight;
    }

    RenderBoundingBox();
}

void CPipeBody::GetBoundingBox(float& l, float& t, float& r, float& b)
{
    // Lấy nửa chiều rộng & cao (đang quy ước x, y là tâm)
    float halfW = this->cellWidth / 2.0f;
    float halfH = this->cellHeight / 2.0f;

    // Box bắt đầu từ (x - halfW, y - halfH)
    l = x - halfW;
    t = y - halfH;

    // Chiều rộng là cellWidth
    r = l + this->cellWidth;

    // Chiều cao tổng = cellHeight * length
    b = t + (this->cellHeight * this->length);
}