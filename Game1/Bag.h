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
	int			boxNum{ 0 }; //���ùڽ� ��ġ ������ X��!!

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

	//���漱�� ���̶� icon�� �浹Ȯ������ obrect ��ȯ �Լ� -- ������ hotbar������ �����̴ϱ�
	// bagitem ���� hotbar�� �浹
	ObRect* ReturnHotbarCol(int x)
	{
		return hotbar[x]->col;
	}

	ObRect* ReturnCol()
	{
		return selectBox->col;
	}

	void AddItem(ItemType itType); //selectItem�ʿ� Ÿ�� �Ѱ��ִ� �Լ�

	ItemType GetItemType(); //selectItem�� Ÿ���� �ʿ���! -> OnScreen �ʿ��� ���� �Լ�


	void CheckItem();

};

