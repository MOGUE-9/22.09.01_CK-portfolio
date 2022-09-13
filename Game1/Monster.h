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
	ObImage*		img; //�⺻ �̹���
	//ObImage*		imgAtt; //���� �̹���
	//ObImage*		imgDie; //��� �̹���

	MonsterState	monsterState;
	ObCircle*		range[3];
	float			distance;

	bool			scaleSwitching;
	
	float			moveTimer{ 0.0f }; //��ȸ��ȯ Ÿ�̸� ���µ� ������ �ȵ��̾��ٰ� ��?�ε�
	
	Vector2			freeMov{ DOWN }; //�����̵� ���Ⱚ
	bool			isFind{ false }; //�÷��̾ �ֺ��� �Դ��� üũ


	//�ٵ� �̰� ��� �ɵ� ������ ����̴ϱ�
	bool			fightMod; //������� ��������� Ȯ�� - �÷��̾ �����̿� ���� - ������ hp����, �������� �Ⱥ���

	//�̰� ���� �׳� hp�� �����ϰ� ���൵ ������ .... 
	bool			getAttack; //�̰� �¾��� �� hp���� �� bool��
	
public:
	int				hp; //�� hp
	int				att{ 5 }; //�� ���ݷ�


public:
	Monster();
	~Monster();

	void Update();
	void Render();

	void Idle();
	void Look();
	void Move();
	void Attack();

	void MonAtt(); //���� ����

};

