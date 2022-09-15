#include "stdafx.h"

Monster::Monster()
{
	col = new ObRect();
	col->isFilled = false;
	col->SetWorldPos(Vector2(200.0f, -360.0f));
	col->scale = Vector2(28.0f, 28.0f);
	col->color = Color(1.0f, 0.0f, 0.0f, 1.0f);

	img->SetParentRT(*col);
	img->scale = Vector2(42.0f, 42.0f);
	img->ChangeAnim(ANIMSTATE::LOOP, 0.15f);
	img->maxFrame.x = 10;

	imgAtt->SetParentRT(*col);
	imgAtt->visible = false;
	imgAtt->scale = Vector2(42.0f, 42.0f);
	imgAtt->ChangeAnim(ANIMSTATE::LOOP, 0.15f);
	imgAtt->maxFrame.x = 10;

	imgDie->SetParentRT(*col);
	imgDie->visible = false;
	imgDie->scale = Vector2(42.0f, 42.0f);
	imgDie->maxFrame.x = 8;

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

	SOUND->AddSound("slimeDeath.mp3", "slimeDeath", false);
	SOUND->AddSound("slimeHurt.mp3", "slimeHurt", false);

	monsterState = MonsterState::IDLE;
	hp = 20;
}

Monster::~Monster()
{
	SafeDelete(col);
	SafeDelete(img);
	SafeDelete(imgAtt);
	SafeDelete(imgDie);

	SafeDelete(range[0]);
	SafeDelete(range[1]);
	SafeDelete(range[2]);
}

void Monster::Update()
{
	if (hp <= 0) //공격으로 인해 hp가 0이 됐을 경우
	{
		getHit = false;
		monsterState = MonsterState::DIE;
		Die();
		//cout << "몹 사망" << endl;
	}
	else
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
	
	if (getHited)
	{
		SOUND->Stop("slimeHurt");
		SOUND->Play("slimeHurt");
		getHited = false;
	}


	col->Update();
	img->Update();
	imgAtt->Update();
	imgDie->Update();
	range[0]->Update();
	range[1]->Update();
	range[2]->Update();
}

void Monster::Render()
{
	col->Render();
	img->Render();
	imgAtt->Render();
	imgDie->Render();
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

	if (true)
	{

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
	img->visible = true;
	imgAtt->visible = false;


	if (dirState == 0 || dirState == 1 || dirState == 2)
	{
		target += Vector2(25.0f, 0.0f);
	}
	else if (dirState == 3 || dirState == 4 || dirState == 5)
	{
		target += Vector2(-10.0f, 0.0f);
	}

	moveDir = target - GetPos();
	moveDir.Normalize();

	col->MoveWorldPos(moveDir * 60.0f * DELTA);


	//move -> idle
	if (distance > (float)MonsterState::MOVE)
	{
		monsterState = MonsterState::IDLE;
	}

	////move -> attack
	if (fightMod)
	{
		monsterState = MonsterState::ATTACK;
	}
	//if (TIMER->GetTick(moveTimer, 2.0f))
	//{
	//	monsterState = MonsterState::ATTACK;
	//	getHit = true;
	//}

	//if (distance < (float)MonsterState::ATTACK)
	//{
	//	monsterState = MonsterState::ATTACK;
	//	scaleSwitching = true;
	//}
}

void Monster::Attack()
{
	img->visible = false;
	imgAtt->visible = true;

	//마지막 프레임에 도달하면 상태변경
	if (imgAtt->frame.x == 7)
	{
		//playerHP -= att;
		getAttack = true;
		monsterState = MonsterState::MOVE;
		imgAtt->frame.x = 0;
	}

	//if (fightMod)
	//{
	//	monsterState = MonsterState::ATTACK;
	//}
	//float plus;
	//if (scaleSwitching) plus = 1.0f;
	//else plus = -1.0f;

	//img->scale.x += plus * 200.0f * DELTA;
	//img->scale.y -= plus * 200.0f * DELTA;

	//if (img->scale.x < 50.0f || img->scale.y < 50.0f)
	//{
	//	scaleSwitching = !scaleSwitching;
	//}


	//attack -> move
	if (distance > (float)MonsterState::ATTACK)
	{
		monsterState = MonsterState::MOVE;
	}
}


void Monster::MonAtt(int& plHp)
{
	if (TIMER->GetTick(moveTimer, 1.2f))
	{
		if (!getHit)
		{
			plHp -= att;

			//몸박으로 한대치고나면, 점프공격 상태로 변경
			getHit != getHit;
			getJump = !getJump;
		}

		//if (getJump)
		//{
		//	monsterState = MonsterState::ATTACK;
		//	if (TIMER->GetTick(moveTimer, 2.0f))
		//	{
		//		plHp -= att;

		//		getHit != getHit;
		//		getJump = !getJump;
		//	}
		//}
	}
}

void Monster::GetHp(int plHp)
{
	playerHP = plHp;
}

int Monster::SetHp()
{
	return playerHP;
}

void Monster::Die()
{
	col->visible = false;
	col->colOnOff = false;

	img->visible = false;
	img->colOnOff = false;

	imgAtt->visible = false;
	imgAtt->colOnOff = false;

	imgDie->visible = true;
	imgDie->ChangeAnim(ANIMSTATE::LOOP, 0.15f);

	if (imgDie->frame.x == 0) SOUND->Play("slimeDeath");
	if (imgDie->frame.x > 2) SOUND->Stop("slimeDeath");

	//마지막 프레임에 도달하면 소멸되도록
	if (imgDie->frame.x == 7)
	{

		col->visible = false;
		col->colOnOff = false;

		imgDie->visible = false;
		imgDie->colOnOff = false;

	}
}


