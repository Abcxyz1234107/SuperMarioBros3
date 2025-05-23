#pragma once
#include "Goomba.h"
#include "Wing.h"

#define REDGOOMBA_PREPARE_JUMP 1
#define REDGOOMBA_JUMP 2

#define REDGOOMBA_SHORT_JUMP_SPEED 0.15f
#define REDGOOMBA_HIGH_JUMP_SPEED  0.5f
#define REDGOOMBA_SHORT_JUMP_COUNT 3
#define REDGOOMBA_CYCLE_COOLDOWN   500

#define ID_ANI_REDGOOMBA_FLIPPED   5700

class CGoombaRed :
    public CGoomba
{
private:
    float spawnX, spawnY;

    float detectRange;
    int state = 0;

    bool hasWing;
    CWing* leftWing, * rightWing;

    int        shortJumpsLeft;
    ULONGLONG  cycleStart;

public:
    CGoombaRed(float x, float y, float detectRange = 100.0f) : CGoomba(x, y)
    {
        spawnX = x;
        spawnY = y;

        leftWing = rightWing = nullptr;
        hasWing = false;
        AddWing();

        this->detectRange = detectRange;

        shortJumpsLeft = 0;
        cycleStart = 0;
    }

    void GetBoundingBox(float& left, float& top, float& right, float& bottom) override;
    void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) override;
    void Render() override;

    void OnNoCollision(DWORD dt) override;
    void OnCollisionWith(LPCOLLISIONEVENT e) override;

    int IsCollidable() override { return 1; };
    int IsBlocking() override { return 0; }

    void DetectMario();


    bool HasWings() { return hasWing; }
    void AddWing();
    void RemoveWing();
    void UpdateWing();

    void RenderWing();
};

