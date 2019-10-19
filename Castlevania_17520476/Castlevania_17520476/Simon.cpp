#include <algorithm>
#include "debug.h"

#include "Simon.h"
#include "Game.h"


void CSIMON::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	// Calculate dx, dy 
	CGameObject::Update(dt);

	// Simple fall down
	vy += SIMON_GRAVITY * dt;

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	// No collision occured, proceed normally
	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		// block 
		x += min_tx * dx + nx * 0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
		y += min_ty * dy + ny * 0.4f;

		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;

	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void CSIMON::Render()
{
	int ani;

			if (vx == 0)
			{
				if (nx > 0) ani = SIMON_ANI_BIG_IDLE_RIGHT;
				else ani = SIMON_ANI_BIG_IDLE_LEFT;
			}
			else if (vx > 0)
				ani = SIMON_ANI_BIG_WALKING_RIGHT;
			else ani = SIMON_ANI_BIG_WALKING_LEFT;
		
	animations[ani]->Render(x, y, 255);

	RenderBoundingBox();
}

void CSIMON::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
	case SIMON_STATE_WALKING_RIGHT:
		vx = SIMON_WALKING_SPEED;
		nx = 1;
		break;
	case SIMON_STATE_WALKING_LEFT:
		vx = -SIMON_WALKING_SPEED;
		nx = -1;
		break;
	case SIMON_STATE_JUMP:
		vy = -SIMON_JUMP_SPEED_Y;
	case SIMON_STATE_IDLE:
		vx = 0;
		break;
	}
}

void CSIMON::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;

	if (level == SIMON_LEVEL_BIG)
	{
		right = x + SIMON_BIG_BBOX_WIDTH;
		bottom = y + SIMON_BIG_BBOX_HEIGHT;
	}
}

