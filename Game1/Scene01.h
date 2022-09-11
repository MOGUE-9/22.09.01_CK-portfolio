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

	//가방열렸냐? - 여닫힘에 따라 icons 위치 재설정!
	bool		isOpenBag{ false };

	ItemType	saveType; //장비타입 저장용?

	ObTileMap* map;

	//길찾기용 변수
	vector<Tile*> PlWay;

	//이동시킬 위치
	Vector2 PlDest;
	Vector2 PlSour;

	//비율
	float   g;

public:
	Scene01();
	~Scene01();

	virtual void Init() override;
	virtual void Release() override; //해제
	virtual void Update() override;
	virtual void LateUpdate() override;//갱신
	virtual void Render() override;
	virtual void ResizeScreen() override;
};

