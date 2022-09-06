#pragma once
#define bagX 10
#define bagY 3

struct InBagItem
{
	ObImage* img;
	ObRect* col;
	string name;
	ItemType type;
	float damage;
};

class Bag : public OnScreen
{
	InBagItem*	hotbar[bagX];

	InBagItem*	bagitem[bagX][bagY];
	ObImage*	bagBG;

public:
	Bag();
	~Bag();

	void Update();
	void Render();

	Vector2 GetHotbarPos(int x);

	Vector2 GetBagitemPos(int x, int y);

	void AddItem();
	void CheckItem();

};

