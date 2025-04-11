#pragma once
#include "PipeBody.h"
class BGTreeEdge :
    public CPipeBody
{
public:
    BGTreeEdge(float x, float y,
        float cellWidth, float cellHeight, int length,
        int spriteId)
        : CPipeBody(x, y, cellWidth, cellHeight, length, spriteId) {}

    void GetBoundingBox(float& l, float& t, float& r, float& b) {}
    int IsBlocking() { return 0; }
};

