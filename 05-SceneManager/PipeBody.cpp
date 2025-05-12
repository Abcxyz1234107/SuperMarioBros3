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

    //RenderBoundingBox();
}

void CPipeBody::GetBoundingBox(float& l, float& t, float& r, float& b)
{
    float halfW = cellWidth / 2.0f;
    float halfH = cellHeight / 2.0f;

    l = x - halfW;
    t = (y + cellHeight) - halfH;
    r = l + cellWidth;
    b = t + cellHeight * length;
}