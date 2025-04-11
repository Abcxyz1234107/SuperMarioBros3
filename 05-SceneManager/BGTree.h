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
    BGTreeEdge* edge;
    BGTreeHead* head;
    int edgeLeftRight;
public:
    BGTree(float x, float y, int bodyLength, int edgeLength, int i = 1,
        float cellWidth = 30, float cellHeight = 16,
        int spriteId_Body = ID_SPRITE_BGTREEBODY, int spriteId_Edge = ID_SPRITE_BGTREEEDGE)
        : CGameObject(x, y) 
    {
        edgeLeftRight = i * 15;
        this->head = new BGTreeHead(x, y);
        this->body = new BGTreeBody(x, y, cellWidth, cellHeight, bodyLength, spriteId_Body);
        this->edge = new BGTreeEdge(x + edgeLeftRight, y, cellWidth, cellHeight, edgeLength, spriteId_Edge);
    }
    void Render() { head->Render(); body->Render(); edge->Render(); }
    void GetBoundingBox(float& l, float& t, float& r, float& b) {}
    int IsBlocking() { return 0; }
};

