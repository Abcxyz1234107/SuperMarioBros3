#pragma once
#include "PipeBody.h"
#include "AssetIDs.h"

class BGTreeBody :
    public CPipeBody
{
public:
    BGTreeBody(float x, float y,
        float cellWidth, float cellHeight, int length,
        int spriteId)
        : CPipeBody(x, y, cellWidth, cellHeight, length, spriteId) {}

    void GetBoundingBox(float& l, float& t, float& r, float& b) {}
    int IsBlocking() { return 0; }
};

