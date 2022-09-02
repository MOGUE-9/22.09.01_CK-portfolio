#include "stdafx.h"

Torch::Torch()
{
	col = new ObRect();
	col->scale = Vector2(32.0f, 32.0f) * 2.0f;
	col->SetWorldPos(Vector2(100.0f, 100.0f));
	col->isFilled = false;

	torch = new ObImage(L"Torch.png");
	torch->maxFrame = Int2(6, 1);
	torch->ChangeAnim(ANIMSTATE::LOOP, 0.1f);
	torch->scale = Vector2(32.0f, 32.0f) * 2.0f;
	torch->SetParentRT(*col);
}

Torch::~Torch()
{
	SafeDelete(col);
	SafeDelete(torch);
}

void Torch::Update()
{


	col->Update();
	torch->Update();
}

void Torch::Render()
{

	col->Render();
	torch->Render();
}
