#pragma once
#include "BGObject.h"
class CBGBrick :
    public CBGObject
{
public:
    CBGBrick(float x, float y) : CBGObject(x, y) {}
    void Render() override;
};

