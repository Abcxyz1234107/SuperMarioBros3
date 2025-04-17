#pragma once
#include "GameObject.h"
class CBGObject :
    public CGameObject
{
protected:
	int length;				// Unit: cell 
	float cellWidth;
	float cellHeight;
	int spriteIdBegin, spriteIdMiddle, spriteIdEnd;
	int isAni;

public:
	CBGObject(float x, float y) : CGameObject(x, y) {}
	CBGObject(float x, float y,
		float cell_width, float cell_height, int length,
		int sprite_id_begin, int sprite_id_middle, int sprite_id_end, int isAni = 0) :CGameObject(x, y)
	{
		this->length = length;
		this->cellWidth = cell_width;
		this->cellHeight = cell_height;
		this->spriteIdBegin = sprite_id_begin;
		this->spriteIdMiddle = sprite_id_middle;
		this->spriteIdEnd = sprite_id_end;
		this->isAni = isAni;
	}
	virtual void Render() {}
	void GetBoundingBox(float& l, float& t, float& r, float& b) {}
};

