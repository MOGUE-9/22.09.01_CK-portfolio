#include "stdafx.h"

OnScreen::OnScreen()
{
	bag = new ObImage(L"Bag.png");
	bag->scale = Vector2(24.0f, 24.0f) * 2.0f;
	bag->SetWorldPos(Vector2(app.GetHalfWidth() - (24.0f * 2.0f), -app.GetHalfHeight() + (24.0f * 2.0f)));
	bag->space = SPACE::SCREEN; //ȭ����� UI (ī�޶����)

	hand = new ObImage(L"Interact.png");
	hand->SetWorldPos(Vector2(app.GetHalfWidth() - (24.0f * 4.0f), -app.GetHalfHeight() + (24.0f * 2.0f)));
	hand->scale = Vector2(24.0f, 24.0f) * 2.0f;
	hand->space = SPACE::SCREEN; //ȭ����� UI (ī�޶����)

	eat = new ObImage(L"Eat.png");
	eat->SetWorldPos(Vector2(app.GetHalfWidth() - (24.0f * 6.0f), -app.GetHalfHeight() + (24.0f * 2.0f)));
	eat->scale = Vector2(24.0f, 24.0f) * 2.0f;
	eat->visible = false;
	eat->space = SPACE::SCREEN; //ȭ����� UI (ī�޶����)

	stand = new ObImage(L"Stand.png");
	stand->SetWorldPos(Vector2(app.GetHalfWidth() - (24.0f * 6.0f), -app.GetHalfHeight() + (24.0f * 2.0f)));
	stand->scale = Vector2(24.0f, 24.0f) * 2.0f;
	stand->visible = false;
	stand->space = SPACE::SCREEN; //ȭ����� UI (ī�޶����)


	itemType = ItemType::NONE;
}

OnScreen::~OnScreen()
{
	SafeDelete(bag);
	SafeDelete(hand);

}

void OnScreen::Update()
{
	//������ ���� Ȯ�ο� Ŀ�ǵ�
	//if (INPUT->KeyPress('1'))
	//{
	//	itemType = ItemType::WEAPON;
	//}
	//if (INPUT->KeyPress('2'))
	//{
	//	itemType = ItemType::TOOL;
	//}
	//if (INPUT->KeyPress('3'))
	//{
	//	itemType = ItemType::FOOD;
	//}
	//if (INPUT->KeyPress('4'))
	//{
	//	itemType = ItemType::NONE;
	//}

	switch (itemType)
	{
	case ItemType::WEAPON:
		Weapon();
		break;
	case ItemType::TOOL:
		Tool();
		break;
	case ItemType::FOOD:
		Food();
		break;
	case ItemType::NONE:
		None();
		break;
	}

	bag->Update();
	hand->Update();
	eat->Update();
	stand->Update();
}

void OnScreen::Render()
{
	bag->Render();
	hand->Render();
	eat->Render();
	stand->Render();
}

void OnScreen::Weapon()
{
	hand->color.A(0.2f);
}

void OnScreen::Food()
{
	hand->color.A(0.2f);
	stand->visible = false;
	eat->visible = true;
}

void OnScreen::Tool()
{
	hand->color.A(0.2f);
	eat->visible = false;
	stand->visible = true;
}

void OnScreen::None()
{
	eat->visible = false;
	stand->visible = false;
	hand->color.A(0.5f);
}
