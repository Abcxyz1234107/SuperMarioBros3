#pragma once
#include "Koopas.h"
#include "Wing.h"

class CKoopasGreen :
    public CKoopas

{
private:
    CWing* leftWing = nullptr;
    CWing* rightWing = nullptr;
    bool    hasWing = false;

    int allowWing;

public:
    CKoopasGreen(float x, float y, int hasWing = 1) : CKoopas(x, y)
    {
        type = 1;
        if (hasWing == 1) AddWing();

        allowWing = hasWing;
    }

    bool HasWings() { return hasWing; }
    void AddWing();
    void RemoveWing();
    void UpdateWing();
    void RenderWing();

    void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) override;
    void OnCollisionWith(LPCOLLISIONEVENT e) override;
    void Render() override;
};

