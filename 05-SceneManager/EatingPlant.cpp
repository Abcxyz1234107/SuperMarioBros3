#include "EatingPlant.h"
#include "PlayScene.h"

void CEatingPlant::WAIT_TOP()
{
    LPPLAYSCENE scene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
    CMario* mario = (CMario*)scene->GetPlayer();

    if (GetTickCount64() - stateTimer >= SPLANT_TIME_TOP_WAIT)
    {
        state = SPLANT_RETRACT;
        vy = SPLANT_SPEED_RETRACT;
    }
}
void CEatingPlant::Detect_Mario()
{
    LPPLAYSCENE scene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
    CMario* mario = (CMario*)scene->GetPlayer();

    float mx, my;
    mario->GetPosition(mx, my);

    float dx = mx - x;
    float dy = my - y;
    distToMario = dx * dx + dy * dy;

    // Nếu Mario ở trong phạm vi phát hiện 
    if (distToMario <= detectRange * detectRange)
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
}