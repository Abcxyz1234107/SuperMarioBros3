#pragma once
#include "PipeBody.h"
class Border :
    public CPipeBody

{
    Border(float x, float y) : CPipeBody(x, y, 2, 1000, 5, 12300)
    {

    }
};


