#pragma once
#include "PipeBody.h"
#include "PipeHead.h"
#include "ShootingPlant.h"
#include "EatingPlant.h"

class CPipe : public CGameObject
{
private:
	CPipeBody* body;
	CPipeHead* head = nullptr;
    CShootingPlant* splant = nullptr;
    CEatingPlant* eplant = nullptr;
    int plantType; //0 normal, 1 no head, 2 shootingPlant, 3 GREEN splant, 4 GREEN eating plant
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

        if (pType >= 2)
        {
            if (pType == 4)
            {
                splant = new CEatingPlant(x, y + 10, pLength, pRange, pType);
                eplant = static_cast<CEatingPlant*>(splant);
            }
            else
            {
                splant = new CShootingPlant(x, y + 10, pLength, pRange, pType);
            }
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
    CEatingPlant* GetEPlant() { return eplant; }
};

