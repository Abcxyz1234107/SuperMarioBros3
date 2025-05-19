#pragma once
#include "PipeBody.h"
#include "PipeHead.h"
#include "ShootingPlant.h"

class CPipe : public CGameObject
{
private:
	CPipeBody* body;
	CPipeHead* head = nullptr;
    CShootingPlant* splant = nullptr;
    int plantType; //0: normal, 1: splant, 2: cplant
    int plantLength;
    float plantRange;
public:
    CPipe(float x, float y,
        int bodyLength, int pType, int pLength, float pRange,
        float cellWidth = 32, float cellHeight = 16,
        int spriteId = ID_SPRITE_PIPEBODY)
        : CGameObject(x, y)
    {
        z = 3;

        if (pType != 1) 
            this->head = new CPipeHead(x - 1, y);

        if (pType == 2)
        {
            this->splant = new CShootingPlant(x, y + 10, pLength, pRange);
        }

        body = new CPipeBody(x, y, cellWidth, cellHeight, bodyLength, spriteId);
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

