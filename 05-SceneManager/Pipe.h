#pragma once
#include "PipeBody.h"
#include "PipeHead.h"
#include "ShootingPlant.h"

class CPipe : public CGameObject
{
private:
	CPipeBody* body;
	CPipeHead* head;
    CShootingPlant* splant;
    int plantType; //0: normal, 1: splant, 2: cplant
    int plantLength;
    float plantRange;
    float totalWidth; //Total width of Body only.
    float totalHeight;
public:
    CPipe(float x, float y,
        int bodyLength,
        float cellWidth = 25, float cellHeight = 16,
        int spriteId = ID_SPRITE_PIPEBODY)
        : CGameObject(x, y)
    {
        this->head = new CPipeHead(x - 1, y);
        this->body = new CPipeBody(x, y, cellWidth, cellHeight, bodyLength, spriteId);
        this->splant = nullptr;

        totalHeight = cellHeight * bodyLength;
        totalWidth = cellWidth;
    }
    CPipe(float x, float y,
        int bodyLength, int pType, int pLength, float pRange,
        float cellWidth = 25, float cellHeight = 16,
        int spriteId = ID_SPRITE_PIPEBODY)
        : CGameObject(x, y)
    {
        this->head = new CPipeHead(x - 1, y);
        this->body = new CPipeBody(x, y, cellWidth, cellHeight, bodyLength, spriteId);
        this->splant = nullptr;

        if (pType == 1)
        {
            this->splant = new CShootingPlant(x, y + 10, pLength, pRange);
        }

        totalHeight = cellHeight * bodyLength;
        totalWidth = cellWidth;
        plantType = pType;
        plantLength = pLength;
        plantRange = pRange;
    }
    void Render();
    void GetBoundingBox(float& l, float& t, float& r, float& b) {}

    CPipeHead* GetHead() { return head; }
    CPipeBody* GetBody() { return body; }
    CShootingPlant* GetSPlant() { return splant; }
};

