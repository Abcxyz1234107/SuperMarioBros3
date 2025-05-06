#pragma once
#include "PipeBody.h"
#include "PipeHead.h"

class CPipe : public CGameObject
{
private:
	CPipeBody* body;
	CPipeHead* head;
    float totalWidth; //Total width of Body only.
    float totalHeight;
public:
	CPipe(float x, float y,
        int bodyLength, float cellWidth = 30, float cellHeight = 16,
        int spriteId = ID_SPRITE_PIPEBODY)
        : CGameObject(x, y)
    {
        this->head = new CPipeHead(x-1, y);
        this->body = new CPipeBody(x, y, cellWidth, cellHeight, bodyLength, spriteId);
        totalHeight = cellHeight * bodyLength;
        totalWidth = cellWidth;
    }
    void Render();
    void GetBoundingBox(float& l, float& t, float& r, float& b);

    CPipeHead* GetHead() { return head; }
    CPipeBody* GetBody() { return body; }
};

