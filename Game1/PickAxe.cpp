#include "stdafx.h"


PickAxe::PickAxe()
{
	col = new ObRect();
	col->scale = Vector2(40.0f, 40.0f) * 5.0f;
	col->isFilled = false;

	axe = new ObImage(L"PickAxe.png");
	axe->scale = Vector2(40.0f, 40.0f) * 5.0f;
	axe->maxFrame = Int2(7, 1);
	axe->SetParentRT(*col);

	axeState = AxeState::IDLE;
}

PickAxe::~PickAxe()
{
	SafeDelete(col);
	SafeDelete(axe);
}

void PickAxe::Update()
{
	col->SetWorldPos(target);

	switch (axeState)
	{
	case AxeState::IDLE:
		Idle();
		break;
	case AxeState::ATTACK:
		Attack();
		break;
	}
	col->Update();
	axe->Update();
}

void PickAxe::Render()
{
	col->Render();
	axe->Render();
}

void PickAxe::Idle()
{
	if (INPUT->KeyPress(VK_LBUTTON))
	{
		axeState = AxeState::ATTACK;
		float time = 4.0f / 70.0f;
		axe->ChangeAnim(ANIMSTATE::LOOP, time);
	}
}

void PickAxe::Attack()
{
	if (INPUT->KeyUp(VK_LBUTTON))
	{
		axeState = AxeState::IDLE;
		axe->ChangeAnim(ANIMSTATE::STOP, 0.1f);
		axe->frame.x = 0;
	}
}
