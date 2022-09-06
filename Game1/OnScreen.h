#pragma once
enum class ItemType
{
	WEAPON,
	TOOL,
	TORCH,
	WOOD,
	FOOD,
	NONE
};

class OnScreen
{
protected:
	ItemType itemType;

private:
	ObImage* bag;
	ObImage* hand;

	ObImage* eat;
	ObImage* stand;



	void Weapon();
	void Food();
	void Tool();
	void None();


public:
	OnScreen();
	~OnScreen();

	void Update();
	void Render();
};

