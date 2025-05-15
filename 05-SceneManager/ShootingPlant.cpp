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
        if (!hasShot)
        {
            int sprId = -1;
            switch (head->GetOrient())
            {
            case 0: sprId = ID_SPRITE_SHOOTINGPLANT_RED_BOTTOMLEFT;      break;
            case 1: sprId = ID_SPRITE_SHOOTINGPLANT_RED_TOPRIGHT;     break;
            case 2: sprId = ID_SPRITE_SHOOTINGPLANT_RED_TOPLEFT;   break;
            case 3: sprId = ID_SPRITE_SHOOTINGPLANT_RED_BOTTOMRIGHT;  break;
            }
            head->UseStatic(sprId);  // <-- Gọi duy nhất khi vừa lên tới đỉnh
        }

        if (!hasShot && GetTickCount64() - stateTimer >= SPLANT_TIME_TOP_WAIT)
        {
            float bx = head->GetX(), by = head->GetY();

            /* Đầu cây tới Mario */
            float tx = mx - bx;
            float ty = my - by;

            /* xác định phía trái/ phải và chiều lên/ xuống */
            float side = (tx < 0) ? -1.0f : 1.0f;
            float signY = (ty < 0) ? -1.0f : 1.0f;

            float abs_dx = fabsf(tx);
            float abs_dy = fabsf(ty);

            /* góc chết so với trục ngang, giới hạn ±45° (điều chỉnh theo rad) */
            float angle = atan2f(abs_dy, abs_dx);
            if (angle > SPLANT_BULLET_MAX_ANGLE_RAD) angle = SPLANT_BULLET_MAX_ANGLE_RAD;

            /* vận tốc đạn */
            float vxb = SHOOTINGPLANT_BULLET_SPEED * cosf(angle) * side;
            float vyb = SHOOTINGPLANT_BULLET_SPEED * sinf(angle) * signY;

            CShootingPlantBullet* b = new CShootingPlantBullet(bx, by, vxb, vyb);
            scene->AddObject(b);
            hasShot = true;
            head->ClearStatic();

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