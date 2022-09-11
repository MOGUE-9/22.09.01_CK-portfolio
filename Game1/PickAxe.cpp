#include "stdafx.h"


PickAxe::PickAxe()
{
	col = new ObRect();
	col->scale = Vector2(40.0f, 40.0f) * 5.0f;
	col->isFilled = false;

	img = new ObImage(L"PickAxe.png");
	img->scale = Vector2(40.0f, 40.0f) * 5.0f;
	img->maxFrame = Int2(7, 1);
	img->SetParentRT(*col);

	axeState = AxeState::IDLE;
}

PickAxe::~PickAxe()
{
	SafeDelete(col);
	SafeDelete(img);
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
	img->Update();
}

void PickAxe::Render()
{
	col->Render();
	img->Render();
}

void PickAxe::Idle()
{
	if (INPUT->KeyPress(VK_LBUTTON))
	{
		axeState = AxeState::ATTACK;
		float time = 4.0f / 70.0f;
		img->ChangeAnim(ANIMSTATE::LOOP, time);
	}
}

void PickAxe::Attack()
{
	if (INPUT->KeyUp(VK_LBUTTON))
	{
		axeState = AxeState::IDLE;
		img->ChangeAnim(ANIMSTATE::STOP, 0.1f);
		img->frame.x = 0;
	}
}
