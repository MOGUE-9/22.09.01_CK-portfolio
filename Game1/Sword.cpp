#include "stdafx.h"

Sword::Sword()
{
	col = new ObRect();
	col->scale = Vector2(10.0f, 20.0f) *1.5f;
	col->color = Color(0.0f, 0.0f, 1.0f, 1.0f);
	col->colOnOff = false;
	col->isFilled = false;

	hitBox = new ObRect();
	hitBox->colOnOff = false;
	hitBox->pivot = OFFSET_L;
	hitBox->scale = Vector2(15.0f, 20.0f) * 1.5f;
	hitBox->color = Color(1.0f, 0.0f, 0.0f, 1.0f);
	hitBox->SetParentRT(*col);
	hitBox->isFilled = false;

	img = new ObImage(L"Sword.png");
	img->scale = Vector2(40.0f, 40.0f) * 1.5f;
	img->maxFrame = Int2(7, 1);
	img->SetParentRT(*col);

	swordState = SwordState::IDLE;
}

Sword::~Sword()
{
	SafeDelete(col);
	SafeDelete(img);
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
	hitBox->Update();
	img->Update();
}

void Sword::Render()
{
	col->Render();
	hitBox->Render();
	img->Render();
}


void Sword::Idle()
{
	col->scale = Vector2(10.0f, 20.0f) * 1.5f;
	//sword->rotationY = 0.0f;

	if (gearOnoff)
	{
		if (INPUT->KeyPress(VK_LBUTTON))
		{
			swordState = SwordState::ATTACK;
			float time = 4.0f / 70.0f;
			img->ChangeAnim(ANIMSTATE::LOOP, time);
			attackTime = 0.0f;
			hitBox->colOnOff = true;
		}
	}

}

void Sword::Attack()
{
	Vector2 dir = Vector2(0.0f, 0.0f);
	attackTime += DELTA;

	//cout << mDirState << endl;

	if (mDirState == mDir_L)
	{
		//sword->rotationY = 180.0f;
		img->reverseLR = true;
		dir.x = -8.0f;

		hitBox->rotationY = PI;
		hitBox->SetLocalPos(Vector2(0.0f, 0.0f));
		hitBox->scale.x = 15.0f * 1.5f;
	}
	else if (mDirState == mDir_B)
	{
		img->reverseLR = false;
		dir.x = -8.0f;

		hitBox->rotationY = 0.0f;
		hitBox->SetLocalPos(Vector2(-7.5f, -20.0f));
		hitBox->scale.x = 20.0f * 1.5f;
	}
	else if (mDirState == mDir_T)
	{
		img->reverseLR = true;
		dir.x = 8.0f;
		dir.y = 15.0f;

		hitBox->rotationY = PI;
		hitBox->SetLocalPos(Vector2(7.5f, 0.0f));
		hitBox->scale.x = 20.0f * 1.5f;
	}
	else if(mDirState == mDir_R)
	{
		//img->rotationY = 0.0f;
		img->reverseLR = false;
		dir.x = 8.0f;

		hitBox->rotationY = 0.0f;
		hitBox->SetLocalPos(Vector2(0.0f, 0.0f));
		hitBox->scale.x = 15.0f * 1.5f;
	}

	Vector2 pos = target + dir;
	col->SetWorldPos(pos);


	if (!hitBox->colOnOff)
	{
		// Scene01 에서 때린 뒤 colOnoff = false가 됨, 이후 false면 들어와서 0.7초 후에 true로 변경시킴
		if (TIMER->GetTick(attackTime, 0.7f))
		{
			hitBox->colOnOff = true;
		}
	}



	if (INPUT->KeyUp(VK_LBUTTON))
	{
		swordState = SwordState::IDLE;
		img->ChangeAnim(ANIMSTATE::STOP, 0.1f);
		img->frame.x = 0;

		hitBox->rotationY = 0.0f;
		hitBox->SetLocalPos(Vector2(0.0f, 0.0f));
		hitBox->scale.x = 15.0f * 1.5f;

		hitBox->colOnOff = false;

	}
}