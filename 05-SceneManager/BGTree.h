#pragma once
#include "GameObject.h"
#include "BGTreeBody.h"
#include "BGTreeEdge.h"
#include "BGTreeHead.h"
#include "Animation.h"
#include "Animations.h"

class BGTree :
    public CGameObject
{
private:
    BGTreeBody* body;
    BGTreeEdge* edgeRight;
    BGTreeEdge* edgeLeft;
    BGTreeHead* head;
public:
    BGTree(float x, float y, int bodyLength, int edgeRightLength, int edgeLeftLength,
        float cellWidth = 30, float cellHeight = 16,
        int spriteId_Body = ID_SPRITE_BGTREEBODY, int spriteId_Edge = ID_SPRITE_BGTREEEDGE)
        : CGameObject(x, y) 
    {
        this->head = new BGTreeHead(x, y);
        this->body = new BGTreeBody(x, y, cellWidth, cellHeight, bodyLength, spriteId_Body);
        this->edgeRight = new BGTreeEdge(x + 15, y, cellWidth, cellHeight, edgeRightLength, spriteId_Edge);
        this->edgeLeft = new BGTreeEdge(x - 15, y, cellWidth, cellHeight, edgeLeftLength, spriteId_Edge);
    }
    void Render() { head->Render(); body->Render(); edgeRight->Render(); edgeLeft->Render(); }
    void GetBoundingBox(float& l, float& t, float& r, float& b) {}
    int IsBlocking() { return 0; }
};

