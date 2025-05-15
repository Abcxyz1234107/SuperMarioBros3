#include "Goomba.h"
#include "VoidSpike.h"

CGoomba::CGoomba(float x, float y):CGameObject(x, y)
{
	this->ax = 0;
	this->ay = GOOMBA_GRAVITY;
	die_start = -1;
	SetState(GOOMBA_STATE_WALKING);
	character = nullptr;

	spawned = false;
	SetState(GOOMBA_STATE_SLEEPING);
}

void CGoomba::AddCharacter(int c) { LPPLAYSCENE currentScene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene(); character = new Character(x, y, c); currentScene->AddObject(character); }
void CGoomba::RenderCharacter() { if (!character) return; if (character->IsDeleted()) {character = nullptr;  return; } character->Render(); }

void CGoomba::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	if (state == GOOMBA_STATE_DIE)
	{
		/*left = x - GOOMBA_BBOX_WIDTH/2;
		top = y - GOOMBA_BBOX_HEIGHT_DIE/2;
		right = left + GOOMBA_BBOX_WIDTH;
		bottom = top + GOOMBA_BBOX_HEIGHT_DIE;*/
	}
	else
	{ 
		left = x - GOOMBA_BBOX_WIDTH/2;
		top = y - GOOMBA_BBOX_HEIGHT/2;
		right = left + GOOMBA_BBOX_WIDTH;
		bottom = top + GOOMBA_BBOX_HEIGHT;
	}
}

void CGoomba::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CGoomba::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<CVoidSpike*>(e->obj))
	{
		this->SetState(GOOMBA_STATE_DIE);
		return;
	}
	if (!e->obj->IsBlocking()) return; 
	if (dynamic_cast<CGoomba*>(e->obj)) return; 

	// Va chạm cơ bản với vật cản
	if (e->ny != 0 )
	{
		vy = 0; // hit ceiling, floor
	}
	else if (e->nx != 0)
	{
		vx = -vx; // đổi hướng khi chạm tường
	}
}

void CGoomba::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	if (!spawned)
	{
		LPPLAYSCENE sc = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
		CMario* mario = (CMario*)sc->GetPlayer();

		float mx, my;  mario->GetPosition(mx, my);
		float range = CGame::GetInstance()->GetBackBufferWidth() * 0.6f;

		if (fabs(mx - x) <= range)  // Mario trong nửa màn hình
		{
			spawned = true;
			SetState(GOOMBA_STATE_WALKING);
		}
		else
			return;
	}

	vy += ay * dt;
	vx += ax * dt;

	if ( (state==GOOMBA_STATE_DIE) && (GetTickCount64() - die_start > GOOMBA_DIE_TIMEOUT) )
	{
		isDeleted = true;
		return;
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CGoomba::Render()
{
	if (!spawned) return;

	int aniId = ID_ANI_GOOMBA_WALKING;
	if (state == GOOMBA_STATE_DIE) 
	{
		aniId = ID_ANI_GOOMBA_DIE;
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x,y);

	RenderCharacter();
	//RenderBoundingBox();
}

void CGoomba::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
		case GOOMBA_STATE_DIE:
			die_start = GetTickCount64();
			y += (GOOMBA_BBOX_HEIGHT - GOOMBA_BBOX_HEIGHT_DIE)/2;
			vx = 0;
			vy = 0;
			ay = 0; 
			break;
		case GOOMBA_STATE_WALKING: 
			vx = -GOOMBA_WALKING_SPEED;
			break;
		case GOOMBA_STATE_SLEEPING:
			vx = vy = 0;
			break;
	}
}
