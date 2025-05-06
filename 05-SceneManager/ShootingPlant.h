#pragma once
#include "GameObject.h"
#include "ShootingPlantBody.h"
#include "ShootingPlantHead.h"
class CShootingPlant :
    public CGameObject
{
private:
    CShootingPlantHead* head;
    CShootingPlantBody* body;
public:
    //CShootingPlantBody(float x, float y,
    //    float cellWidth, float cellHeight, int length,
    //    int spriteId = ID_SPRITE_SHOOTINGPLANT_BODY)
    CShootingPlant(float x, float y, int bodyLength) : CGameObject(x, y)
    {
        z = 1;
        head = new CShootingPlantHead(x, y-4);
        body = new CShootingPlantBody(x, y, 16, 8, bodyLength);
    }

    void Render();
    void GetBoundingBox(float& l, float& t, float& r, float& b) {}

    CShootingPlantHead* GetHead() { return head; }
    CShootingPlantBody* GetBody() { return body; }
};

