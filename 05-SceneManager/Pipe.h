#pragma once
#include "PipeBody.h"
#include "PipeHead.h"

class CPipe : public CGameObject
{
private:
	CPipeBody* body;
	CPipeHead* head;
public:
	CPipe(float x, float y,
        int bodyLength, float cellWidth = 30, float cellHeight = 16,
        int spriteId = 21002)
        : CGameObject(x, y)
    {
        z = 2;
        this->head = new CPipeHead(x, y);
        this->body = new CPipeBody(x+0.75f, y, cellWidth, cellHeight, bodyLength, spriteId);
    }
    void Render();
    void GetBoundingBox(float& l, float& t, float& r, float& b) {}

    CPipeHead* GetHead() { return head; }
    CPipeBody* GetBody() { return body; }
};

