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

			bagitem[x][y]->type = ItemType::NONE;

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

		hotbar[x]->type = ItemType::NONE;
	}


	selectBox = new InBagItem();

	selectBox->col = new ObRect();
	selectBox->col->SetWorldPos(Vector2(-240.0f, -app.GetHalfHeight() + (24.0f * 2.0f)));
	selectBox->col->scale = Vector2(24.0f, 24.0f) * 2.0f;
	selectBox->col->isFilled = false;
	selectBox->col->space = SPACE::SCREEN; //화면고정 UI (카메라고정)

	selectBox->img = new ObImage(L"bagSelect.png");
	selectBox->img->SetParentRT(*selectBox->col);
	selectBox->img->scale = Vector2(24.0f, 24.0f) * 2.0f;
	selectBox->img->space = SPACE::SCREEN; //화면고정 UI (카메라고정)

	selectBox->type = ItemType::NONE;

}

Bag::~Bag()
{
}

void Bag::Update()
{
	if (INPUT->KeyDown(WM_MOUSEWHEEL))
	{
		if (WM_MOUSEWHEEL < 120 && WM_MOUSEWHEEL > 0)
		{
			cout << "위로" << endl;
		}
		else if (WM_MOUSEWHEEL > -120 && WM_MOUSEWHEEL < 0)
		{
			cout << "아래로" << endl;

		}
	}

	//아이콘 변경 확인용 커맨드
	if (INPUT->KeyPress('1'))
	{
		selectBox->col->SetWorldPos(hotbar[0]->col->GetWorldPos());
	}
	if (INPUT->KeyPress('2'))
	{
		selectBox->col->SetWorldPos(hotbar[1]->col->GetWorldPos());
	}
	if (INPUT->KeyPress('3'))
	{
		selectBox->col->SetWorldPos(hotbar[2]->col->GetWorldPos());
	}
	if (INPUT->KeyPress('4'))
	{
		selectBox->col->SetWorldPos(hotbar[3]->col->GetWorldPos());
	}
	if (INPUT->KeyPress('5'))
	{
		selectBox->col->SetWorldPos(hotbar[4]->col->GetWorldPos());
	}
	if (INPUT->KeyPress('6'))
	{
		selectBox->col->SetWorldPos(hotbar[5]->col->GetWorldPos());
	}
	if (INPUT->KeyPress('7'))
	{
		selectBox->col->SetWorldPos(hotbar[6]->col->GetWorldPos());
	}
	if (INPUT->KeyPress('8'))
	{
		selectBox->col->SetWorldPos(hotbar[7]->col->GetWorldPos());
	}
	if (INPUT->KeyPress('9'))
	{
		selectBox->col->SetWorldPos(hotbar[8]->col->GetWorldPos());
	}
	if (INPUT->KeyPress('0'))
	{
		selectBox->col->SetWorldPos(hotbar[9]->col->GetWorldPos());
	}



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

	selectBox->col->Update();
	selectBox->img->Update();
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

	selectBox->col->Render();
	selectBox->img->Render();
}

Vector2 Bag::GetHotbarPos(int x)
{
	return hotbar[x]->col->GetWorldPos();
}

Vector2 Bag::GetBagitemPos(int x, int y)
{
	return bagitem[x][y]->col->GetWorldPos();
}

ItemType Bag::GetBagitemType(int x, int y)
{
	return bagitem[x][y]->type;
}

void Bag::SetBagitemType(int x, int y, ItemType itType)
{
	bagitem[x][y]->type = itType;
}


void Bag::AddItem(ItemType itType)
{
	selectBox->type = itType;
}

ItemType Bag::GetItemType()
{
	return selectBox->type;
}

void Bag::CheckItem()
{
	for (int x = 0; x < 10; x++)
	{
		//선택상자랑 단축바 위치 중 한 곳과 같을때
		if (selectBox->col->GetWorldPos() == hotbar[x]->col->GetWorldPos())
		{
			//아이템타입 검사

		}
	}

}
