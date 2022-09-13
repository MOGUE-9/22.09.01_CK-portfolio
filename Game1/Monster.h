#pragma once

enum class MonsterState
{
	IDLE,
	LOOK = 200,
	MOVE = 150,
	ATTACK = 15
};

class Monster : public Character
{
private:
	ObImage*		img; //기본 이미지
	//ObImage*		imgAtt; //공격 이미지
	//ObImage*		imgDie; //사망 이미지

	MonsterState	monsterState;
	ObCircle*		range[3];
	float			distance;

	bool			scaleSwitching;
	
	float			moveTimer{ 0.0f }; //배회전환 타이머 였는데 구동이 안됨이었다가 됨?인듯
	
	Vector2			freeMov{ DOWN }; //자율이동 방향값
	bool			isFind{ false }; //플레이어가 주변에 왔는지 체크


	//근데 이거 없어도 될듯 어차피 잡몹이니까
	bool			fightMod; //전투모드 비전투모드 확인 - 플레이어가 가까이에 들어옴 - 전투면 hp보임, 비전투면 안보임

	//이거 없이 그냥 hp에 접근하게 해줘도 될지도 .... 
	bool			getAttack; //이건 맞았을 때 hp관리 용 bool값
	
public:
	int				hp; //몹 hp
	int				att{ 5 }; //몹 공격력


public:
	Monster();
	~Monster();

	void Update();
	void Render();

	void Idle();
	void Look();
	void Move();
	void Attack();

	void MonAtt(); //내가 공격

};

