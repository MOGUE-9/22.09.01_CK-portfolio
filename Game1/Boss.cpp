#include "stdafx.h"


Boss::Boss()
{
	//������ü ���� �̹���, col�ڽ���
	col = new ObRect();
	col->scale = Vector2(0.0f, 0.0f);
	col->isFilled = false;

	img->scale = Vector2(128.0f, 128.0f);
	img->SetParentRT(*col);
	img->ChangeAnim(ANIMSTATE::LOOP, 0.2f);
	img->maxFrame.x = 8;

	imgAtt->scale = Vector2(128.0f, 128.0f);
	imgAtt->SetParentRT(*col);
	imgAtt->ChangeAnim(ANIMSTATE::LOOP, 0.2f);
	imgAtt->maxFrame.x = 8;
	imgAtt->visible = false;

	imgDie->scale = Vector2(128.0f, 128.0f);
	imgDie->SetParentRT(*col);
	imgDie->ChangeAnim(ANIMSTATE::LOOP, 0.2f);
	imgDie->maxFrame.x = 8;
	imgDie->visible = false;
	
	//��������
	range[0] = new ObCircle();
	range[0]->isFilled = false;
	float scale = (float)BossState::LOOK * 2.0f;
	range[0]->scale = Vector2(scale, scale);
	range[0]->SetParentRT(*col);

	range[1] = new ObCircle();
	range[1]->isFilled = false;
	scale = (float)BossState::MOVE * 2.0f;
	range[1]->scale = Vector2(scale, scale);
	range[1]->SetParentRT(*col);

	range[2] = new ObCircle();
	range[2]->isFilled = false;
	scale = (float)BossState::ATTACK * 2.0f;
	range[2]->scale = Vector2(scale, scale);
	range[2]->SetParentRT(*col);

	bossState = BossState::IDLE;
}

Boss::~Boss()
{
	SafeDelete(col);
	SafeDelete(img);
	SafeDelete(imgAtt);
	SafeDelete(imgDie);
	SafeDelete(range[0]);
	SafeDelete(range[1]);
	SafeDelete(range[2]);
}

void Boss::Update()
{
	if (hp <= 0) //�������� ���� hp�� 0�� ���� ���
	{
		bossState = BossState::DIE;
		//cout << "���� ���" << endl;
	}
	else //ü���� 0�� �ƴ� ���
	{
		if (!isFind) //������ ����: scene01�� update���� �Լ��ؼ� target��ġ�� �ҷ����� ������
				// �������� ������ ������ ���?? ������ ���µ��� ? �ƴѰ�? �����غ�
		{
			Vector2 dis = target - GetPos();
			distance = dis.Length();

			switch (bossState)
			{
			case BossState::IDLE: //������ �ִ� ����
				Idle();
				break;
			case BossState::LOOK: // �������·� ���� . . . 
				Look();
				break;
			case BossState::MOVE: //�����̸鼭 ��ġ��(����) ����
				Move();
				break;
			case BossState::ATTACK: //�����ϸ鼭 ������ ����
				Attack();
				break;
			}
		}
	}

	img->Update();
	imgAtt->Update();
	imgDie->Update();
	for (int i = 0; i < 3; i++)
	{
		range[i]->Update();
	}
}

void Boss::Render()
{
	img->Render();
	imgAtt->Render();
	imgDie->Render();
	for (int i = 0; i < 3; i++)
	{
		range[i]->Render();
	}
}

void Boss::Idle()
{
}

void Boss::Look()
{
}

void Boss::Move()
{
}

void Boss::Attack()
{
}

void Boss::Die()
{
	img->visible = false;
	img->visible = false;

	imgAtt->visible = false;
	imgAtt->visible = false;

	imgDie->visible = true;
	imgDie->ChangeAnim(ANIMSTATE::ONCE, 0.2f);
	
	if (imgDie->frame.x == 8)
	{
		col->visible = false;
		col->colOnOff = false;

		imgDie->visible = false;
		imgDie->colOnOff = false;

		//die -> idle ���·� �ؼ� visible�� false�� ������� ����
		bossState = BossState::IDLE;
	}
}

//
//Monster::Monster()
//{
//	col = new ObRect();
//	col->isFilled = false;
//	col->scale = Vector2(128.0f, 127.0f);
//
//	img = new ObImage(L"boss.bmp");
//	img->SetParentRT(*col);
//	img->scale = Vector2(128.0f, 127.0f);
//	img->maxFrame.y = 8;
//
//	//frameY[Dir_R] = 0;
//	//frameY[Dir_L] = 1;
//	//frameY[Dir_RB] = 2;
//	//frameY[Dir_LT] = 3;
//	//frameY[Dir_T] = 4;
//	//frameY[Dir_B] = 5;
//	//frameY[Dir_LB] = 6;
//	//frameY[Dir_RT] = 7;
//
//	range[0] = new ObCircle();
//	range[0]->isFilled = false;
//	float scale = (float)MonsterState::LOOK * 2.0f;
//	range[0]->scale = Vector2(scale, scale);
//	range[0]->SetParentRT(*col);
//
//	range[1] = new ObCircle();
//	range[1]->isFilled = false;
//	scale = (float)MonsterState::MOVE * 2.0f;
//	range[1]->scale = Vector2(scale, scale);
//	range[1]->SetParentRT(*col);
//
//	range[2] = new ObCircle();
//	range[2]->isFilled = false;
//	scale = (float)MonsterState::ATTACK * 2.0f;
//	range[2]->scale = Vector2(scale, scale);
//	range[2]->SetParentRT(*col);
//
//	monsterState = MonsterState::IDLE;
//}
//
//Monster::~Monster()
//{
//	SafeDelete(col);
//	SafeDelete(img);
//	SafeDelete(range[0]);
//	SafeDelete(range[1]);
//	SafeDelete(range[2]);
//}
//
//void Monster::Update()
//{
//	Vector2 dis = target - GetPos();
//	distance = dis.Length();
//
//	switch (monsterState)
//	{
//	case MonsterState::IDLE:
//		Idle();
//		break;
//	case  MonsterState::LOOK:
//		Look();
//		break;
//	case  MonsterState::MOVE:
//		Move();
//		break;
//	case  MonsterState::ATTACK:
//		Attack();
//		break;
//	}
//
//	col->Update();
//	img->Update();
//	range[0]->Update();
//	range[1]->Update();
//	range[2]->Update();
//}
//
//void Monster::Render()
//{
//	col->Render();
//	img->Render();
//	range[0]->Render();
//	range[1]->Render();
//	range[2]->Render();
//}
//
//void Monster::Idle()
//{
//	//idle -> look
//	if (distance < (float)MonsterState::LOOK)
//	{
//		monsterState = MonsterState::LOOK;
//	}
//}
//
//void Monster::Look()
//{
//	LookTarget(target, img);
//
//	//look -> idle
//	if (distance > (float)MonsterState::LOOK)
//	{
//		monsterState = MonsterState::IDLE;
//	}
//
//	//look -> move
//	if (distance < (float)MonsterState::MOVE)
//	{
//		monsterState = MonsterState::MOVE;
//	}
//}
//
//void Monster::Move()
//{
//	LookTarget(target, img);
//
//	moveDir = target - GetPos();
//	moveDir.Normalize();
//
//	col->MoveWorldPos(moveDir * 100.0f * DELTA);
//
//	//move -> look
//	if (distance > (float)MonsterState::MOVE)
//	{
//		monsterState = MonsterState::LOOK;
//	}
//
//	//move -> attack
//	if (distance < (float)MonsterState::ATTACK)
//	{
//		monsterState = MonsterState::ATTACK;
//		scaleSwitching = true;
//	}
//}
//
//void Monster::Attack()
//{
//	LookTarget(target, img);
//
//	float plus;
//	if (scaleSwitching) plus = 1.0f;
//	else plus = -1.0f;
//
//	img->scale.x += plus * 200.0f * DELTA;
//	img->scale.y -= plus * 200.0f * DELTA;
//
//	if (img->scale.x < 50.0f || img->scale.y < 50.0f)
//	{
//		scaleSwitching = !scaleSwitching;
//	}
//
//	//attack -> move
//	if (distance > (float)MonsterState::ATTACK)
//	{
//		monsterState = MonsterState::MOVE;
//		img->scale.x = 128.0f;
//		img->scale.y = 127.0f;
//	}
//}