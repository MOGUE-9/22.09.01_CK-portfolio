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
	
	float			moveTimer; //��ȸ��ȯ Ÿ�̸� ���µ� ������ �ȵ�
	
	Vector2			freeMov{ DOWN }; //�����̵� ���Ⱚ
	bool			isFind{ false }; //�÷��̾ �ֺ��� �Դ��� üũ

	float			hp{ 20.0f }; //�� hp
	float			att{ 5.0f }; //�� ���ݷ�

	//�ٵ� �̰� ��� �ɵ� ������ ����̴ϱ�
	//bool			fightMod; //������� ��������� Ȯ�� - ������ hp����, �������� �Ⱥ���

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

