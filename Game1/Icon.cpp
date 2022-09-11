#include "stdafx.h"

Icon::Icon()
{
	iconType.weapon = new ObImage(L"iconSword.png");
	iconType.weapon->scale = Vector2(20.0f, 20.0f);
	iconType.weapon->space = SPACE::SCREEN; //화면고정 UI (카메라고정)

	iconType.tool = new ObImage(L"iconPickaxe.png");
	iconType.tool->scale = Vector2(20.0f, 20.0f);
	iconType.tool->space = SPACE::SCREEN; //화면고정 UI (카메라고정)

	iconType.torch = new ObImage(L"iconTorch.png");
	iconType.torch->scale = Vector2(20.0f, 20.0f);
	iconType.torch->space = SPACE::SCREEN; //화면고정 UI (카메라고정)

	iconType.wood = new ObImage(L"iconWood.png");
	iconType.wood->scale = Vector2(20.0f, 20.0f);
	iconType.wood->space = SPACE::SCREEN; //화면고정 UI (카메라고정)


	itemType = ItemType::NONE;
}

Icon::~Icon()
{
	SafeDelete(iconType.weapon);
	SafeDelete(iconType.tool);
	SafeDelete(iconType.torch);
	SafeDelete(iconType.wood);


}

void Icon::Update()
{

	////아이콘 변경 확인용 커맨드
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
	//	itemType = ItemType::TORCH;
	//}
	//if (INPUT->KeyPress('4'))
	//{
	//	itemType = ItemType::WOOD;
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
	case ItemType::TORCH:
		Torch();
		break;
	case ItemType::WOOD:
		Wood();
		break;
	case ItemType::NONE:
		None();
		break;
	}

	iconType.weapon->Update();
	iconType.tool->Update();
	iconType.torch->Update();
	iconType.wood->Update();
}

void Icon::Render()
{

	iconType.weapon->Render();
	iconType.tool->Render();
	iconType.torch->Render();
	iconType.wood->Render();	
}

void Icon::AddItem(ItemType type)
{
	if (!isIn)
	{
		itemType = type;
		isIn = true;
	}
}

ItemType Icon::GetItem()
{
	return itemType;
}

void Icon::Weapon()
{
	iconType.weapon->visible = true;
	iconType.tool->visible = false;
	iconType.torch->visible = false;
	iconType.wood->visible = false;
}

void Icon::Tool()
{
	iconType.weapon->visible = false;
	iconType.tool->visible = true;
	iconType.torch->visible = false;
	iconType.wood->visible = false;
}

void Icon::Torch()
{
	iconType.weapon->visible = false;
	iconType.tool->visible = false;
	iconType.torch->visible = true;
	iconType.wood->visible = false;
}

void Icon::Wood()
{
	iconType.weapon->visible = false;
	iconType.tool->visible = false;
	iconType.torch->visible = false;
	iconType.wood->visible = true;
}

void Icon::None()
{
	iconType.weapon->visible = false;
	iconType.tool->visible = false;
	iconType.torch->visible = false;
	iconType.wood->visible = false;
}

void Icon::SetIconPos(Vector2 pos)
{
	iconType.weapon->SetWorldPos(pos);
	iconType.tool->SetWorldPos(pos);
	iconType.torch->SetWorldPos(pos);
	iconType.wood->SetWorldPos(pos);
}
