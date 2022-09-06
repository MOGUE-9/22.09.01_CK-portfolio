#pragma once
struct IconType
{
	ObImage* weapon;
	ObImage* tool;
	ObImage* torch;
	ObImage* wood;
};

class Icon : public OnScreen
{
	IconType	iconType;
	ItemType	itemType;

	bool		isIn{ false }; //가방칸이 채워졌냐? 는 뜻.

	void Weapon();
	void Tool();
	void Torch();
	void Wood();
	void None();

public:

	Icon();
	~Icon();

	void Update();
	void Render();

	//타입 저장하는 함수 :: !isIn, 안에 아무것도 없을 때만 저장되도록!!
	void AddItem(ItemType type);

	void SetIconPos(Vector2 pos);
};

