#pragma once
#include "GameObject.h"
#include "ShootingPlantBody.h"
#include "ShootingPlantHead.h"
#include "ShootingPlantBullet.h"

#define SPLANT_SPEED_EMERGE   0.05f
#define SPLANT_SPEED_RETRACT  0.05f
#define SPLANT_TIME_TOP_WAIT      1500   
#define SPLANT_TIME_BOTTOM_WAIT   1500

#define SPLANT_BULLET_MAX_ANGLE_RAD  0.785398f  // 45°

enum SPLANT_STATE {
    SPLANT_HIDDEN, SPLANT_EMERGING, SPLANT_WAIT_TOP,
    SPLANT_RETRACT, SPLANT_WAIT_BOTTOM
};

class CShootingPlant :
    public CGameObject
{
private:
    CShootingPlantHead* head;
    CShootingPlantBody* body;
    float detectRange;
    float distToMario = 0;

    float startY, topY;
    ULONGLONG stateTimer;
    SPLANT_STATE state;
    bool hasShot;
public:
    CShootingPlant(float x, float y,
        int bodyLength,
        float detectRange, int type = 2) :
        CGameObject(x, y)
    {
        z = 2;
        this->detectRange = detectRange;
        head = new CShootingPlantHead(x, y-4, type);
        body = new CShootingPlantBody(x, y, 16, 8, bodyLength);

        startY = y;
        topY = y - bodyLength * 8 - 20;   // vượt khỏi Pipe
        state = SPLANT_HIDDEN;
        hasShot = false;
        stateTimer = 0;
    }

    void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) override;
    void Render();
    void GetBoundingBox(float& l, float& t, float& r, float& b) {}

    virtual void WAIT_TOP();
    virtual void Detect_Mario(); //virtual hàm này để tách playscene, mario
                                 //ra khỏi Update thì mới đặt wait_top
                                 //thành virtual được

    CShootingPlantHead* GetHead() { return head; }
    CShootingPlantBody* GetBody() { return body; }
};

