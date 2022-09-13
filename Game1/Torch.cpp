#include "stdafx.h"

Torch::Torch()
{
	col = new ObRect();
	col->scale = Vector2(10.0f, 32.0f) * 2.0f;
	col->SetWorldPos(Vector2(100.0f, 100.0f));
	col->isFilled = false;

	img = new ObImage(L"Torch.png");
	img->maxFrame = Int2(6, 1);
	img->ChangeAnim(ANIMSTATE::LOOP, 0.1f);
	img->scale = Vector2(32.0f, 32.0f) * 2.0f;
	img->SetParentRT(*col);
	img->visible = true;

	torchIcon = new ObImage(L"iconTorchS.png");
	torchIcon->scale = Vector2(16.0f, 16.0f) * 2.0f;
	torchIcon->SetParentRT(*col);           
	torchIcon->visible = false;

	range = new ObCircle();
	range->scale = Vector2(16.0f, 16.0f)*2.0f;
	range->isFilled = false;
	range->SetParentRT(*col);

	torchState = TorchState::STAND;
}

Torch::~Torch()
{
	SafeDelete(col);
	SafeDelete(img);
	SafeDelete(torchIcon);
	SafeDelete(range);

}	

void Torch::Update()
{
	//if (col->Intersect(INPUT->GetMouseWorldPos()))
	//{
	//	if (INPUT->KeyPress(VK_LBUTTON))
	//	{
	//		col->SetWorldPos(INPUT->GetMouseWorldPos());
	//	}
	//}

	switch (torchState)
	{
	case TorchState::STAND:
		Stand();
		break;
	case TorchState::MINI:
		Mini();
		break;
	case TorchState::NONE:
		None();
		break;
	}


	col->Update();
	img->Update();
	torchIcon->Update();
	range->Update();

}

void Torch::Render()
{

	col->Render();
	img->Render();
	torchIcon->Render();
	range->Render();
}

void Torch::Stand()
{
	//a = 0;

	col->scale = Vector2(10.0f, 15.0f) * 2.0f;

	img->visible = true;
	col->visible = true;
	range->visible = false;
	torchIcon->visible = false;

	if (count == 0)
	{
		torchState = TorchState::MINI;

		col->visible = false;
		img->visible = false;
		torchIcon->visible = true;
		range->visible = true;

	}
}

void Torch::Mini()
{
	//a = 1;

	
	if (TIMER->GetTick(udTimer, 1.0f))
	{
		ud.y *= -1.0f;
	}

	col->MoveWorldPos(ud * 5.0f * DELTA);



	Vector2 moveDir = playerPivot - col->GetWorldPos();

	if (range->Intersect(getBox))
	{
		col->MoveWorldPos(moveDir * 5.0f * DELTA);
	}
	
	if (col->Intersect(getBox))
	{
		torchState = TorchState::NONE;
	}

}

void Torch::None()
{
	//a = 2;

	col->visible = false;
	range->visible = false;
	torchIcon->visible = false;
}

bool Torch::isInterSect(ObRect* col)
{
	if (this->col->Intersect(col))
	{
		return true;
	}
	else false;

	//isInterSec = true;
}

void Torch::GetPlayer(Vector2 pos)
{
	playerPivot = pos;
}
