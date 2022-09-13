#pragma once

enum class MonsterState
{
	IDLE,
	LOOK = 160,
	MOVE = 150,
	ATTACK = 15
};

class Monster : public Character
{
private:
	ObImage*		img;
	MonsterState	monsterState;
	ObCircle*		range[3];
	float			distance;

	bool			scaleSwitching;
	
	float			moveTimer; //배회전환 타이머 였는데 구동이 안됨
	
	Vector2			freeMov{ DOWN }; //자율이동 방향값
	bool			isFind{ false }; //플레이어가 주변에 왔는지 체크

	float			hp{ 20.0f }; //몹 hp
	float			att{ 5.0f }; //몹 공격력

	//근데 이거 없어도 될듯 어차피 잡몹이니까
	//bool			fightMod; //전투모드 비전투모드 확인 - 전투면 hp보임, 비전투면 안보임

public:
	Monster();
	~Monster();

	void Update();
	void Render();

	void Idle();
	void Look();
	void Move();
	void Attack();
};

