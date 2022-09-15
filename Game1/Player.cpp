#include "stdafx.h"

Player::Player()
{
	col = new ObRect();
	//col->SetWorldPos(Vector2(-500.0f, -200.0f));
	col->SetWorldPos(Vector2());
	col->scale = Vector2(26.0f, 36.0f);
	col->color = Color(0.0f, 0.0f, 0.0f, 0.0f);
	col->isFilled = false;
	
	hpBox->SetParentRT(*col);
	hpBox->scale = Vector2(30.0f ,3.0f);
	hpBox->SetWorldPos(Vector2(-15.0f, 23.0f));
	hpBox->isFilled = false;
	hpBox->pivot = OFFSET_L;

	hpBar->SetParentRT(*col);
	hpBar->scale = Vector2(30.0f, 3.0f);
	hpBar->SetWorldPos(Vector2(-15.0f, 23.0f));
	hpBar->pivot = OFFSET_L;


	walk = new ObImage(L"IdleWalk.png");
	walk->scale = Vector2(46.0f, 46.0f);
	walk->maxFrame = Int2(7, 6);
	walk->SetParentRT(*col);

	action = new ObImage(L"Action.png");
	action->scale = Vector2(46.0f, 46.0f);
	action->maxFrame = Int2(4, 6);
	action->SetParentRT(*col);
	action->visible = false;

	frameY[Dir_RB] = 0;
	frameY[Dir_R] = 1;
	frameY[Dir_RT] = 2;

	frameY[Dir_LB] = 0;
	frameY[Dir_L] = 4;
	frameY[Dir_LT] = 2;

	plState = PlayerState::IDLE;
}

Player::~Player()
{
	SafeDelete(col);
	SafeDelete(walk);
	SafeDelete(action);
} 

void Player::Update()
{
	LIGHT->light.select = 1.0f;
	LIGHT->SetLightPos(col->GetWorldPos());

	lastPos = col->GetWorldPos();

	hpBar->scale.x = hp;
	hpBar->scale.x = Utility::Saturate(hpBar->scale.x, 0.0f, 30.0f);

	switch (plState)
	{
	case PlayerState::IDLE:
		Idle();
		break;
	case PlayerState::WALK:
		Walk();
		break;
	case PlayerState::ACTION:
		Action();
		break;
	}

	col->Update();
	walk->Update();
	action->Update();
	hpBox->Update();
	hpBar->Update();
}

void Player::Render()
{
	col->Render();
	walk->Render();
	action->Render();

	hpBox->Render();
	hpBar->Render();
}

void Player::StepBack()
{
	col->SetWorldPos(lastPos);

	col->Update();
	walk->Update();
	action->Update();
}

void Player::Idle()
{	
	Input();
	LookTarget(INPUT->GetMouseWorldPos(), walk);
	
	//Idle->Walk
	if (moveDir != Vector2(0.0f, 0.0f))
	{
		plState = PlayerState::WALK;
		walk->ChangeAnim(ANIMSTATE::LOOP, 0.1f);
	}

	//Idle -> Action
	if (INPUT->KeyPress(VK_LBUTTON))
	{
		plState = PlayerState::ACTION;
		action->ChangeAnim(ANIMSTATE::LOOP, 0.1f);
		walk->visible = false;
		action->visible = true;
		rollTime = 0.0f;
	}
}

void Player::Walk()
{
	Input();
	LookTarget(INPUT->GetMouseWorldPos(), walk);

	col->MoveWorldPos(moveDir * 200.0f * DELTA);

	//Walk -> Idle
	if (moveDir == Vector2(0.0f, 0.0f))
	{
		plState = PlayerState::IDLE;
		walk->ChangeAnim(ANIMSTATE::STOP, 0.1f);
		walk->frame.x = 0;
	}

	//Walk -> Action
	if (INPUT->KeyPress(VK_LBUTTON))
	{
		plState = PlayerState::ACTION;
		action->ChangeAnim(ANIMSTATE::LOOP, 0.1f);
		walk->visible = false;
		action->visible = true;
		rollTime = 0.0f;
	}
}

void Player::Action()
{
	Input();
	LookTarget(INPUT->GetMouseWorldPos(), action);

	if (INPUT->KeyUp(VK_LBUTTON))
	{
		plState = PlayerState::IDLE;
		walk->ChangeAnim(ANIMSTATE::STOP, 0.1f);
		walk->frame.x = 0;
		action->visible = false;
		walk->visible = true;
		rollTime = 0.0f;
	}
}

void Player::Input()
{
	moveDir = Vector2(0.0f, 0.0f);

	if (INPUT->KeyPress('S'))
	{
		moveDir.y = -1.0f;
	}
	else if (INPUT->KeyPress('W'))
	{
		moveDir.y = 1.0f;
	}

	if (INPUT->KeyPress('A'))
	{
		moveDir.x = -1.0f;
	}
	else if (INPUT->KeyPress('D'))
	{
		moveDir.x = 1.0f;
	}
	
	moveDir.Normalize();
}


