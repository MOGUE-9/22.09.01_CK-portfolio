#pragma once
enum class ItemType
{
	WEAPON,
	TOOL,
	FOOD,
	NONE
};

class OnScreen
{
	ObImage* bag;
	ObImage* hand;

	ItemType itemType;

public:
	OnScreen();
	~OnScreen();

	void Update();
	void Render();
};

