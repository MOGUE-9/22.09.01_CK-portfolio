#pragma once

class Scene01 : public Scene
{
private:
	Player* pl;
	//Monster* mon;
	
	Weapon*		weapon;
	PickAxe*	pickAxe;
	Sword*		sword;
	Torch*		torch;

	Bag*		bags;
	OnScreen*	screenUI;
	Icon*		icons[bagX][bagY];

	//���濭�ȳ�? - �������� ���� icons ��ġ �缳��!
	bool		isOpenBag{ false };

	ItemType	saveType; //���Ÿ�� �����?

	ObTileMap* map;

	//��ã��� ����
	vector<Tile*> PlWay;

	//�̵���ų ��ġ
	Vector2 PlDest;
	Vector2 PlSour;

	//����
	float   g;

public:
	Scene01();
	~Scene01();

	virtual void Init() override;
	virtual void Release() override; //����
	virtual void Update() override;
	virtual void LateUpdate() override;//����
	virtual void Render() override;
	virtual void ResizeScreen() override;
};

