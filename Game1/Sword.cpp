#include "stdafx.h"

Sword::Sword()
{
	col = new ObRect();
	col->scale = Vector2(10.0f, 20.0f) *1.5f;
	col->color = Color(1.0f, 0.0f, 0.0f, 1.0f);
	col->isFilled = false;

	sword = new ObImage(L"Sword.png");
	sword->scale = Vector2(40.0f, 40.0f) * 1.5f;
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
	Vector2 pos = target - Vector2(8.0f, 5.0f);
	col->SetWorldPos(pos);

	SetWeaponPos(INPUT->GetMouseWorldPos());

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
	col->scale = Vector2(10.0f, 20.0f) * 1.5f;

	if (INPUT->KeyPress(VK_LBUTTON))
	{
		swordState = SwordState::ATTACK;
		float time = 4.0f / 70.0f;
		sword->ChangeAnim(ANIMSTATE::LOOP, time);
	}
}

void Sword::Attack()
{
	Vector2 dir = Vector2(0.0f, 0.0f);

	cout << mDirState << endl;

	if (mDirState == mDir_L)
	{
		sword->reverseLR = true;
		dir.x = -8.0f;
	}
	else if (mDirState == mDir_B)
	{
		sword->reverseLR = false;
		dir.x = -8.0f;
	}
	else if (mDirState == mDir_T)
	{
		sword->reverseLR = true;
		dir.x = 8.0f;
		dir.y = 10.0f;
	}
	else
	{
		sword->reverseLR = false;
		dir.x = 8.0f;
	}

	Vector2 pos = target + dir;
	col->SetWorldPos(pos);

	if (INPUT->KeyUp(VK_LBUTTON))
	{
		swordState = SwordState::IDLE;
		sword->ChangeAnim(ANIMSTATE::STOP, 0.1f);
		sword->frame.x = 0;
	}
}