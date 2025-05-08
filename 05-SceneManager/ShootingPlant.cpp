#include "ShootingPlant.h"
#include "Mario.h"
#include "PlayScene.h"

void CShootingPlant::Render() 
{
	head->Render();
	body->Render();
}

void CShootingPlant::Update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects)
{
    
    LPPLAYSCENE scene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
    CMario* mario = (CMario*)scene->GetPlayer();

    float mx, my;
    mario->GetPosition(mx, my);

    float dx = mx - x;
    float dy = my - y;
    float dist2 = dx * dx + dy * dy;

    // Nếu Mario ở trong phạm vi phát hiện 
    if (dist2 <= detectRange * detectRange)
    {
        int o = -1;

        if (dx < 0)                        // Mario bên trái
        {
            o = (dy < 0 ? 2 : 0);
        }
        else                               // Mario bên phải
        {
            o = (dy > 0 ? 3 : 1);
        }

        head->SetOrient(o);
    }

    switch (state)
    {
    case SPLANT_HIDDEN:
        if (dist2 <= detectRange * detectRange)
        {
            state = SPLANT_EMERGING;
            vy = -SPLANT_SPEED_EMERGE;
        }
        break;

    case SPLANT_EMERGING:
        y += vy * dt;
        head->SetPosition(head->GetX(), head->GetY() + vy * dt);
        body->SetPosition(body->GetX(), body->GetY() + vy * dt);
        if (y <= topY)
        {
            y = topY; head->SetPosition(head->GetX(), head->GetY() - (y - topY));
            vy = 0;
            state = SPLANT_WAIT_TOP;
            stateTimer = GetTickCount64();
            hasShot = false;
        }
        break;

    case SPLANT_WAIT_TOP:
        if (!hasShot && GetTickCount64() - stateTimer >= SPLANT_TIME_TOP_WAIT)
        {
            /* bắn đạn theo orient hiện tại */
            float bx = head->GetX(), by = head->GetY();
            float vx = 0, vyb = 0;
            switch (head->GetOrient())       
            {
            case 0:  vx = -SHOOTINGPLANT_BULLET_SPEED; vyb = SHOOTINGPLANT_BULLET_SPEED;  break; // BL
            case 1:  vx = SHOOTINGPLANT_BULLET_SPEED; vyb = -SHOOTINGPLANT_BULLET_SPEED;  break; // TR
            case 2:  vx = -SHOOTINGPLANT_BULLET_SPEED; vyb = -SHOOTINGPLANT_BULLET_SPEED;  break; // BR
            case 3:  vx = SHOOTINGPLANT_BULLET_SPEED; vyb = SHOOTINGPLANT_BULLET_SPEED;  break; // TL
            }
            CShootingPlantBullet* b = new CShootingPlantBullet(bx, by, vx, vyb);
            scene->AddObject(b);               
            hasShot = true;

            state = SPLANT_RETRACT;
            vy = SPLANT_SPEED_RETRACT;
        }
        break;

    case SPLANT_RETRACT:
        y += vy * dt;
        head->SetPosition(head->GetX(), head->GetY() + vy * dt);
        body->SetPosition(body->GetX(), body->GetY() + vy * dt);
        if (y >= startY)
        {
            y = startY;
            vy = 0;
            state = SPLANT_WAIT_BOTTOM;
            stateTimer = GetTickCount64();
        }
        break;

    case SPLANT_WAIT_BOTTOM:
        if (GetTickCount64() - stateTimer >= SPLANT_TIME_BOTTOM_WAIT)
            state = SPLANT_HIDDEN;
        break;
    }
}