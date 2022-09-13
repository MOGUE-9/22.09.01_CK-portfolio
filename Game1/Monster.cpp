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
	hp = 20;
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
	if (hp <= 0) //공격으로 인해 hp가 0이 됐을 경우
	{
		col->visible = false;
		col->colOnOff = false;

		img->visible = false;
		img->colOnOff = false;

		monsterState = MonsterState::IDLE;
		//cout << "몹 사망" << endl;
	}
	else
	{
		if (!isFind) //설정한 이유: scene01의 update에서 게속해서 target위치를 불러오기 때문에
						// 설정하지 않으면 범위에 없어도?? 나한테 오는듯함 ? 아닌가? 해제해봄
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

	col->MoveWorldPos(freeMov * 30.0f * DELTA);

	if (TIMER->GetTick(moveTimer, 2.0f))
	{
		int dirX =	RANDOM->Int(0, 3);
		switch (dirX)
		{
		case 0:
			freeMov.x = 1.0f;
			break;
		case 1:
			freeMov.x = -1.0f;
			break;
		case 2:
			freeMov.x = 0.0f;
			break;
		}

		int dirY = RANDOM->Int(0, 3);
		switch (dirY)
		{
		case 0:
			freeMov.y = 1.0f;
			break;
		case 1:
			freeMov.y = -1.0f;
			break;
		case 2:
			freeMov.y = 0.0f;
			break;
		}
	}

	//idle -> look
	//if (distance < (float)MonsterState::LOOK)
	//{
	//	monsterState = MonsterState::LOOK;
	//}

	//idle -> move
	if (distance < (float)MonsterState::MOVE)
	{
		monsterState = MonsterState::MOVE;
	}
}

//굳이 필요하지 않을 것 같은 상태라 일단 제외
void Monster::Look()
{
	////LookTarget(target, img);
	//col->MoveWorldPos(freeMov * 30.0f * DELTA);

	////look -> idle
	//if (distance > (float)MonsterState::LOOK)
	//{
	//	monsterState = MonsterState::IDLE;
	//}

	////look -> move
	//if (distance < (float)MonsterState::MOVE)
	//{
	//	monsterState = MonsterState::MOVE;
	//}
}

void Monster::Move()
{
	LookTarget(target, img);

	moveDir = target - GetPos();
	moveDir.Normalize();

	col->MoveWorldPos(moveDir * 60.0f * DELTA);
	
	//move -> idle
	if (distance > (float)MonsterState::MOVE)
	{
		monsterState = MonsterState::IDLE;
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
