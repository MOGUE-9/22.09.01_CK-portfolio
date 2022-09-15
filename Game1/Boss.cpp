#include "stdafx.h"

Boss::Boss()
{
	//보스 소환진 (기본 위치)
	colRune->scale = Vector2(46.0f, 46.0f);
	colRune->isFilled = false;
	colRune->SetWorldPos(Vector2(0.0f, -1000.0f));

	imgRune->scale = Vector2(46.0f, 46.0f) * 1.5f;
	imgRune->SetParentRT(*colRune);

	//보스본체 관련 이미지, col박스들
	col = new ObRect();
	col->scale = Vector2(100.0f, 100.0f);
	col->SetWorldPos(Vector2(0.0f, -1000.0f));
	col->isFilled = false;

	img->scale = Vector2(128.0f, 128.0f) * 1.5f;
	img->SetParentRT(*col);
	img->ChangeAnim(ANIMSTATE::LOOP, 0.15f);
	img->maxFrame.x = 8;

	imgAtt->scale = Vector2(128.0f, 128.0f) * 1.5f;
	imgAtt->SetParentRT(*col);
	imgAtt->ChangeAnim(ANIMSTATE::LOOP, 0.15f);
	imgAtt->maxFrame.x = 6;
	imgAtt->visible = false;

	imgDie->scale = Vector2(128.0f, 128.0f) * 0.8f;
	imgDie->SetParentRT(*col);
	imgDie->ChangeAnim(ANIMSTATE::LOOP, 0.15f);
	imgDie->maxFrame.x = 8;
	imgDie->visible = false;
	
	//감지범위
	range[0] = new ObCircle();
	range[0]->isFilled = false;
	float scale = (float)BossState::BACK * 2.0f;
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

	SOUND->AddSound("slimeBossDeath.mp3", "bossDeath", false);
	SOUND->AddSound("slimeBossHurt.mp3", "bossHurt", false);

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
	Vector2 dis = target - GetPos();
	distance = dis.Length();
	//cout << distance << endl;

	if (hp > 0) //공격으로 인해 hp가 0이 됐을 경우
	{
		/*if (!isFind) *///설정한 이유: scene01의 update에서 게속해서 target위치를 불러오기 때문에
		// 설정하지 않으면 범위에 없어도?? 나한테 오는듯함 ? 아닌가? 해제해봄

		switch (bossState)
		{
		case BossState::IDLE: //가만히 있는 상태
			Idle();
			break;
		case BossState::BACK: // 무슨상태로 하지 . . . 
			Back();
			break;
		case BossState::MOVE: //움직이면서 박치기(공격) 상태
			Move();
			break;
		case BossState::ATTACK: //점프하면서 때리는 상태
			Attack();
			break;
		}

	}
	else //체력이 0이 아닌 경우
	{
		bossState = BossState::DIE;
		Die();
		//cout << "보스 사망" << endl;
		
	}

	if (getHited)
	{
		SOUND->Stop("bossHurt");
		SOUND->Play("bossHurt");
		getHited = false;
	}
	
	if (bossState == BossState::DIE && !isDie)
	{
		SOUND->Play("bossDeath");
		isDie = true;
	}

	colRune->Update();
	imgRune->Update();
	col->Update();
	img->Update();
	imgAtt->Update();
	imgDie->Update();

	range[0]->Update();
	range[1]->Update();
	range[2]->Update();
}

void Boss::Render()
{
	colRune->Render();
	imgRune->Render();
	col->Render();
	img->Render();
	imgAtt->Render();
	imgDie->Render();
	range[0]->Render();
	range[1]->Render();
	range[2]->Render();
}

void Boss::Idle() //진짜 그냥 가만히 아무것도 X상태
{
	//cout << "idle" << endl;
	//cout << distance << endl;

	img->visible = true;
	imgAtt->visible = false;

	//// idle -> move
	//if (distance < (float)BossState::MOVE)
	//{
	//	bossState = BossState::MOVE;
	//}
	
	//idle -> back :: 복귀상태
	if (distance < (float)BossState::BACK)
	{
		bossState = BossState::BACK;
	}
}

void Boss::Back()
{
	//cout << "back" << endl;

	// look 범위를 벗어나면 제자리로 돌아가도록 ??
	// 원래 소환진 위로 이동하는 함수?로??
	moveDir = firstPlace - GetPos();
	moveDir.Normalize();
	col->MoveWorldPos(moveDir * 60.0f * DELTA);
	//cout << col->GetWorldPos().x << endl;

	//if (colRune->Intersect(col)))
	//{
	//	col->SetWorldPos(firstPlace);
	//	//isOnRune = true;
	//}

	//back -> idle
	if (distance > (float)BossState::BACK)
	{
		bossState = BossState::IDLE;
	}
	
	//back -> move
	if (distance < (float)BossState::MOVE)
	{
		bossState = BossState::MOVE;
	}
}

void Boss::Move() //이동하며 부딪혀서 공격
{
	//cout << "move" << endl;

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


	//move -> back
	if (distance > (float)BossState::MOVE)
	{
		bossState = BossState::BACK;
	}

	//씬01에서 fightmod 를 true로 변경하면 attack 모드로 바뀜
	//move -> attack
	if (fightMod)
	{
		bossState = BossState::ATTACK;
	}
}

void Boss::Attack() //점프뛰며 공격
{
	//cout << "attack" << endl;

	img->visible = false;
	imgAtt->visible = true;

	//애니메이션 재생 끝나면 대미지 들어가며 move로 돌아가기
	if (imgAtt->frame.x == 5)
	{
		getAttack = true; // 이걸로 씬01에서 대미지 받도록 시간조절
		bossState = BossState::MOVE;
		imgAtt->frame.x = 0;
	}

	//attack -> move
	if (distance > (float)BossState::ATTACK)
	{
		bossState = BossState::MOVE;
	}
}

void Boss::Die()
{
	//cout << "die" << endl;

	img->visible = false;
	img->colOnOff = false;

	imgAtt->visible = false;
	imgAtt->colOnOff = false;

	imgDie->visible = true;
	imgDie->ChangeAnim(ANIMSTATE::LOOP, 0.15f);
	
	if (imgDie->frame.x == 7)
	{
		col->visible = false;
		col->colOnOff = false;

		imgDie->visible = false;
		imgDie->colOnOff = false;
	}
}
