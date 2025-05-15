#include "ShootingPlantBullet.h"
#include "Mario.h"
#include "Game.h"

void CShootingPlantBullet::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_SHOOTINGPLANT_BULLET)->Render(x, y);
	//RenderBoundingBox();
}

void CShootingPlantBullet::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - SHOOTINGPLANTBULLET_W / 2;
	t = y - SHOOTINGPLANTBULLET_H / 2;
	r = l + SHOOTINGPLANTBULLET_W;
	b = t + SHOOTINGPLANTBULLET_H;
}

void CShootingPlantBullet::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CShootingPlantBullet::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<CMario*>(e->obj))
		OnCollisionWithMario(e);
};

void CShootingPlantBullet::OnCollisionWithMario(LPCOLLISIONEVENT e)
{
	this->Delete();
	CMario* mario = dynamic_cast<CMario*>(e->obj);

	if (!mario->IsUntouchable())
	{
		if (mario->GetLevel() > MARIO_LEVEL_SMALL)
		{
			mario->SetLevel(mario->GetLevel() - 1);
		}
		else
		{
			DebugOut(L">>> Mario DIE >>> \n");
			mario->SetState(MARIO_STATE_DIE);
		}
	}
};

void CShootingPlantBullet::Update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects)
{
	// xoá viên đạn khi ra khỏi màn hình
	float camX, camY;
	CGame::GetInstance()->GetCamPos(camX, camY);
	if (x < camX - 32 || x > camX + CGame::GetInstance()->GetBackBufferWidth() + 32)
		this->Delete();

	CCollision::GetInstance()->Process(this, dt, coObjects);
}