#pragma once
#include "GameObject.h"
#include "Character.h"

class Character;

#define WING_BBOX_W 8
#define WING_BBOX_H 13

#define ID_ANI_STATIC_WING_LEFT 5006
#define ID_ANI_STATIC_WING_RIGHT 5008

class CWing :
    public CGameObject
{
private:
    int position; //1: left, 2: right
    bool isStatic = true;
    Character* character;

public:
    CWing(float x, float y, int p) : CGameObject(x, y)
    {
        position = p;
        character = nullptr;
    }

    void GetBoundingBox(float& left, float& top, float& right, float& bottom) override;
    void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) override;
    void Render() override;

    int IsCollidable() override { return 0; };
    int IsBlocking() override { return 0; }

    void AddCharacter(int c);
    void RenderCharacter();

    void SetStatic(bool b) { isStatic = b; }
    bool IsStatic() { return isStatic; }
};

