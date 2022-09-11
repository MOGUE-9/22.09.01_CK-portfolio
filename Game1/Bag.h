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
	InBagItem*	selectBox;
	int			boxNum{ 0 }; //선택박스 위치 정해줄 X값!!

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
	ItemType GetBagitemType(int x, int y);

	void SetBagitemType(int x, int y, ItemType itType);

	//가방선택 블럭이랑 icon블럭 충돌확인위한 obrect 반환 함수 -- 어차피 hotbar에서만 움직이니까
	// bagitem 말고 hotbar랑 충돌
	ObRect* ReturnHotbarCol(int x)
	{
		return hotbar[x]->col;
	}

	ObRect* ReturnCol()
	{
		return selectBox->col;
	}

	void AddItem(ItemType itType); //selectItem쪽에 타입 넘겨주는 함수

	ItemType GetItemType(); //selectItem의 타입이 필요해! -> OnScreen 쪽에서 사용될 함수


	void CheckItem();

};

