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

	bool		isIn{ false }; //����ĭ�� ä������? �� ��.

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

	//Ÿ�� �����ϴ� �Լ� :: !isIn, �ȿ� �ƹ��͵� ���� ���� ����ǵ���!!
	void AddItem(ItemType type);

	void SetIconPos(Vector2 pos);
};

