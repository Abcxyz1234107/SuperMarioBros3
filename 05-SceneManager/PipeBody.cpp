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
    l = x - cellWidth / 2;
    t = y - cellHeight / 2;
    r = l + cellWidth;
    b = t + totalHeight;
}