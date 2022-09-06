#include "stdafx.h"

Torch::Torch()
{
	col = new ObRect();
	col->scale = Vector2(10.0f, 32.0f) * 2.0f;
	col->SetWorldPos(Vector2(100.0f, 100.0f));
	col->isFilled = false;

	torch = new ObImage(L"Torch.png");
	torch->maxFrame = Int2(6, 1);
	torch->ChangeAnim(ANIMSTATE::LOOP, 0.1f);
	torch->scale = Vector2(32.0f, 32.0f) * 2.0f;
	torch->SetParentRT(*col);
	torch->visible = true;

	torchIcon = new ObImage(L"iconTorchS.png");
	torchIcon->scale = Vector2(16.0f, 16.0f) * 2.0f;
	torchIcon->SetParentRT(*col);           
	torchIcon->visible = false;


	torchState = TorchState::STAND;
}

Torch::~Torch()
{
	SafeDelete(col);
	SafeDelete(torch);
}	

void Torch::Update()
{
	if (col->Intersect(INPUT->GetMouseWorldPos()))
	{
		if (INPUT->KeyPress(VK_LBUTTON))
		{
			col->SetWorldPos(INPUT->GetMouseWorldPos());
		}
	}

	cout << a << endl;

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
	torch->Update();
	torchIcon->Update();

}

void Torch::Render()
{

	col->Render();
	torch->Render();
	torchIcon->Render();
}

void Torch::Stand()
{
	a = 0;
	if (count == 0)
	{
		torchState = TorchState::MINI;
		torch->visible = false;
		torchIcon->visible = true;
	}
}

void Torch::Mini()
{
	a = 1;

	Vector2 moveDir = playerPivot - col->GetWorldPos();

	col->MoveWorldPos(moveDir * 10.0f * DELTA);

	if (col->GetWorldPos() == playerPivot)
	{
		torchState = TorchState::NONE;
	}
}

void Torch::None()
{
	a = 2;

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
