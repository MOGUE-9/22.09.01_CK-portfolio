#include "stdafx.h"

Sword::Sword()
{
	col = new ObRect();
	col->scale = Vector2(40.0f, 40.0f) * 5.0f;
	col->isFilled = false;

	sword = new ObImage(L"Sword.png");
	sword->scale = Vector2(40.0f, 40.0f) * 5.0f;
	sword->maxFrame = Int2(7, 1);
	sword->SetParentRT(*col);

	swordState = SwordState::IDLE;
}

Sword::~Sword()
{
	SafeDelete(col);
	SafeDelete(sword);
}

void Sword::Update()
{
	col->SetWorldPos(target);

	switch (swordState)
	{
	case SwordState::IDLE:
		Idle();
		break;
	case SwordState::ATTACK:
		Attack();
		break;
	}
	col->Update();
	sword->Update();
}

void Sword::Render()
{
	col->Render();
	sword->Render();
}

void Sword::Idle()
{
	if (INPUT->KeyPress(VK_LBUTTON))
	{
		swordState = SwordState::ATTACK;
		float time = 4.0f / 70.0f;
		sword->ChangeAnim(ANIMSTATE::LOOP, time);
	}
}

void Sword::Attack()
{
	if (INPUT->KeyUp(VK_LBUTTON))
	{
		swordState = SwordState::IDLE;
		sword->ChangeAnim(ANIMSTATE::STOP, 0.1f);
		sword->frame.x = 0;
	}
}