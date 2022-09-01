#include "stdafx.h"

OnScreen::OnScreen()
{
	bag = new ObImage(L"Bag.png");
	bag->scale = Vector2(24.0f, 24.0f) * 2.0f;
	bag->SetWorldPos(Vector2(app.GetHalfWidth() - (24.0f * 2.0f), -app.GetHalfHeight() + (24.0f * 2.0f)));
	bag->space = SPACE::SCREEN; //화면고정 UI (카메라고정)

	hand = new ObImage(L"Interact.png");
	hand->SetWorldPos(Vector2(app.GetHalfWidth() - (24.0f * 4.5f), -app.GetHalfHeight() + (24.0f * 2.0f)));
	hand->scale = Vector2(24.0f, 24.0f) * 2.0f;
	hand->space = SPACE::SCREEN; //화면고정 UI (카메라고정)

	itemType = ItemType::NONE;
}

OnScreen::~OnScreen()
{
	SafeDelete(bag);
	SafeDelete(hand);

}

void OnScreen::Update()
{

	switch (itemType)
	{
	case ItemType::WEAPON:

		break;
	case ItemType::TOOL:

		break;
	case ItemType::FOOD:

		break;
	case ItemType::NONE:

		break;
	}

	bag->Update();
	hand->Update();
}

void OnScreen::Render()
{
	bag->Render();
	hand->Render();

}
