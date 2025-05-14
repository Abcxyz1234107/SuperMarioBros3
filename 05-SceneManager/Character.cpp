#include "Character.h"
#include "debug.h"

void Character::OnNoCollision(DWORD dt)
{
	y -= vy * dt;
}

void Character::Update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects)
{
	OnNoCollision(dt);
	CCollision::GetInstance()->Process(this, dt, coObjects);

	vy *= C_SLOWING;

	if (vy <= C_MIN_VY)
		this->Delete();
}

void Character::Render()
{
	CSprites* sprites = CSprites::GetInstance();
	sprites->Get(score)->Draw(x, y);
}