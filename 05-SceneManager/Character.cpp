#include "Character.h"
#include "debug.h"

void Character::OnNoCollision(DWORD dt)
{
	y -= vy * dt;
}

void Character::Update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects)
{
	if (score == C_COURSECLEAR || score == C_YOUGOTACARD || score == C_MUSHROOM || score == C_FLOWER || score == C_STAR)
	{
		return;
	}

	if (score != C_ANI_HIT)
	{
		vy *= C_SLOWING;
		if (vy <= C_MIN_VY)
			this->Delete();
		OnNoCollision(dt);
		CCollision::GetInstance()->Process(this, dt, coObjects);
	}
	else
	{
		ULONGLONG now = GetTickCount64();
		if (now - timer >= 200) this->Delete();
	}
}

void Character::Render()
{
	if (score == C_ANI_HIT)
	{
		CAnimations::GetInstance()->Get(score)->Render(x, y - 3);
		return;
	}

	CSprites* sprites = CSprites::GetInstance();
	sprites->Get(score)->Draw(x, y);
}