#include "stdafx.h"

Monster::Monster()
{
	col = new ObRect();
	col->isFilled = false;
	col->SetWorldPos(Vector2(100.0f, -160.0f));
	col->scale = Vector2(28.0f, 28.0f);
	col->color = Color(1.0f, 0.0f, 0.0f, 1.0f);

	img = new ObImage(L"Mini.png");
	img->SetParentRT(*col);
	img->scale = Vector2(42.0f, 42.0f);
	img->ChangeAnim(ANIMSTATE::LOOP, 0.2f);
	img->maxFrame.x = 6;

	//frameY[Dir_R] = 0;
	//frameY[Dir_L] = 1;
	//frameY[Dir_RB] = 2;
	//frameY[Dir_LT] = 3;
	//frameY[Dir_T] = 4;
	//frameY[Dir_B] = 5;
	//frameY[Dir_LB] = 6;
	//frameY[Dir_RT] = 7;

	range[0] = new ObCircle();
	range[0]->isFilled = false;
	float scale = (float)MonsterState::LOOK * 2.0f;
	range[0]->scale = Vector2(scale, scale);
	range[0]->SetParentRT(*col);

	range[1] = new ObCircle();
	range[1]->isFilled = false;
	scale = (float)MonsterState::MOVE * 2.0f;
	range[1]->scale = Vector2(scale, scale);
	range[1]->SetParentRT(*col);

	range[2] = new ObCircle();
	range[2]->isFilled = false;
	scale = (float)MonsterState::ATTACK * 2.0f;
	range[2]->scale = Vector2(scale, scale);
	range[2]->SetParentRT(*col);

	monsterState = MonsterState::IDLE;
}

Monster::~Monster()
{
	SafeDelete(col);
	SafeDelete(img);
	SafeDelete(range[0]);
	SafeDelete(range[1]);
	SafeDelete(range[2]);
}

void Monster::Update()
{

	//col->MoveWorldPos(freeMov * 100.0f * DELTA);

	if (TIMER->GetTick(moveTimer, 2.0f))
	{
		
	}


	if (!isFind)
	{
		Vector2 dis = target - GetPos();
		distance = dis.Length();
	
		switch (monsterState)
		{
		case MonsterState::IDLE:
			Idle();
			break;
		case  MonsterState::LOOK:
			Look();
			break;
		case  MonsterState::MOVE:
			Move();
			break;
		case  MonsterState::ATTACK:
			Attack();
			break;
		}
	}
	col->Update();
	img->Update();
	range[0]->Update();
	range[1]->Update();
	range[2]->Update();
}

void Monster::Render()
{
	col->Render();
	img->Render();
	range[0]->Render();
	range[1]->Render();
	range[2]->Render();
}

void Monster::Idle()
{
	//idle -> look
	if (distance < (float)MonsterState::LOOK)
	{
		monsterState = MonsterState::LOOK;
	}
}

void Monster::Look()
{
	LookTarget(target, img);

	//look -> idle
	if (distance > (float)MonsterState::LOOK)
	{
		monsterState = MonsterState::IDLE;
	}

	//look -> move
	if (distance < (float)MonsterState::MOVE)
	{
		monsterState = MonsterState::MOVE;
	}
}

void Monster::Move()
{
	LookTarget(target, img);

	moveDir = target - GetPos();
	moveDir.Normalize();

	col->MoveWorldPos(moveDir * 100.0f * DELTA);
	
	//move -> look
	if (distance > (float)MonsterState::MOVE)
	{
		monsterState = MonsterState::LOOK;
	}

	////move -> attack
	//if (distance < (float)MonsterState::ATTACK)
	//{
	//	monsterState = MonsterState::ATTACK;
	//	scaleSwitching = true;
	//}
}

void Monster::Attack()
{
	LookTarget(target, img);

	float plus;
	if (scaleSwitching) plus = 1.0f;
	else plus = -1.0f;

	img->scale.x += plus * 200.0f * DELTA;
	img->scale.y -= plus * 200.0f * DELTA;

	if (img->scale.x < 50.0f || img->scale.y < 50.0f)
	{
		scaleSwitching = !scaleSwitching;
	}

	//attack -> move
	if (distance > (float)MonsterState::ATTACK)
	{
		monsterState = MonsterState::MOVE;
		img->scale.x = 128.0f;
		img->scale.y = 127.0f;
	}
}
