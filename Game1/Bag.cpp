#include "stdafx.h"

Bag::Bag()
{
	bagBG = new ObImage(L"Hotbar1.png");
	bagBG->scale = Vector2(272.0f, 32.0f) * 2.0f;
	bagBG->SetWorldPos(Vector2(-3.0f, -80.0f));
	bagBG->space = SPACE::SCREEN; //화면고정 UI (카메라고정)
	bagBG->visible = false;

	for (int y = 0; y < bagY; y++)
	{
		for (int x = 0; x < bagX; x++)
		{
			bagitem[x][y] = new InBagItem();

			bagitem[x][y]->col = new ObRect();
			bagitem[x][y]->col->isFilled = false;
			bagitem[x][y]->col->space = SPACE::SCREEN; //화면고정 UI (카메라고정)
			bagitem[x][y]->col->scale = Vector2(24.0f, 24.0f) * 2.0f;
			float pY = 0;
			if (y > 0)
			{
				pY = - 20.0f - (24.0f * 2.0f + 5.0f) * y;
			}
			bagitem[x][y]->col->SetWorldPos(Vector2(-240.0f + (24.0f * 2.0f + 5.0f) * x,
				-80.0f + pY));
			bagitem[x][y]->col->visible = false;


			bagitem[x][y]->img = new ObImage(L"BagBG2.png");
			bagitem[x][y]->img->space = SPACE::SCREEN; //화면고정 UI (카메라고정)
			bagitem[x][y]->img->scale = Vector2(24.0f, 24.0f) * 2.0f;
			bagitem[x][y]->img->SetParentRT(*bagitem[x][y]->col);
			//bagitem[x][y]->img->SetWorldPos(Vector2(-240.0f + (24.0f * 2.0f + 5.0f) * x,
			//	-20.0f + (24.0f * 2.0f + 10.0f) * y + 5.0f * y));
			bagitem[x][y]->img->visible = false;

		}
	}

	for (int x = 0; x < bagX; x++)
	{
		hotbar[x] = new InBagItem();
		
		hotbar[x]->col = new ObRect();
		hotbar[x]->col->isFilled = false;
		hotbar[x]->col->scale = Vector2(24.0f, 24.0f) * 2.0f;
		
		hotbar[x]->col->SetWorldPos(Vector2(-240.0f + (24.0f * 2.0f + 5.0f) * x, 
			-app.GetHalfHeight() + (24.0f * 2.0f)));
		hotbar[x]->col->space = SPACE::SCREEN; //화면고정 UI (카메라고정)

		hotbar[x]->img = new ObImage(L"BagBG2.png");
		hotbar[x]->img->SetParentRT(*hotbar[x]->col);
		//hotbar[x]->img->SetWorldPos(Vector2(-(24.0f * (2.0f + 2.0f * x), -app.GetHalfHeight() + (24.0f * 2.0f))));
		hotbar[x]->img->scale = Vector2(24.0f, 24.0f) * 2.0f;
		hotbar[x]->img->space = SPACE::SCREEN; //화면고정 UI (카메라고정)

	}



}

Bag::~Bag()
{
}

void Bag::Update()
{
	//탭누르면 가방열기 <-> 닫기
	if (INPUT->KeyDown(VK_TAB))
	{
		for (int x = 0; x < bagX; x++)
		{
			hotbar[x]->col->visible = !hotbar[x]->col->visible;
			hotbar[x]->img->visible = !hotbar[x]->img->visible;
		}

		bagBG->visible = !bagBG->visible;

		for (int y = 0; y < bagY; y++)
		{
			for (int x = 0; x < bagX; x++)
			{
				bagitem[x][y]->col->visible = !bagitem[x][y]->col->visible;
				bagitem[x][y]->img->visible = !bagitem[x][y]->img->visible;
			}
		}
	}



	bagBG->Update();

	for (int y = 0; y < bagY; y++)
	{
		for (int x = 0; x < bagX; x++)
		{
			bagitem[x][y]->col->Update();
			bagitem[x][y]->img->Update();
		}
	}

	for (int x = 0; x < bagX; x++)
	{
		hotbar[x]->col->Update();
		hotbar[x]->img->Update();
	}
}

void Bag::Render()
{
	bagBG->Render();
	for (int y = 0; y < bagY; y++)
	{
		for (int x = 0; x < bagX; x++)
		{
			bagitem[x][y]->col->Render();
			bagitem[x][y]->img->Render();
		}
	}

	for (int x = 0; x < bagX; x++)
	{
		hotbar[x]->col->Render();
		hotbar[x]->img->Render();
	}
}

Vector2 Bag::GetHotbarPos(int x)
{
	return hotbar[x]->col->GetWorldPos();
}

Vector2 Bag::GetBagitemPos(int x, int y)
{
	return bagitem[x][y]->col->GetWorldPos();
}


void Bag::AddItem()
{
}

void Bag::CheckItem()
{
}
