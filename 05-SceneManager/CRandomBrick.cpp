#include "CRandomBrick.h"

void CRandomBrick::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
		case RANDOMBRICK_STATE_TOUCHED:
		{
		spriteIdBegin = spriteIdMiddle = spriteIdEnd = ID_SPRITE_RANDOMBRICK_TOUCHED;
		isAni = 0;
		break;
		}
	}
}