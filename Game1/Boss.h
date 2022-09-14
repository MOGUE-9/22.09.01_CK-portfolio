#pragma once

enum class BossState
{
	IDLE,
	LOOK = 1500,
	MOVE = 1000,
	ATTACK = 100,
	DIE
};

class Boss : public Character
{
private:
	ObImage*	img = new ObImage(L"Boss.png"); //�⺻ �̹���
	ObImage*	imgAtt = new ObImage(L"BossAtt.png"); //���� �̹���
	ObImage*	imgDie = new ObImage(L"MiniDie.png"); //��� �̹���

	BossState	bossState; //�������
	ObCircle*	range[3];
	float		distance;

	float		moveTimer{ 0.0f }; //����Ÿ�� ���� Ÿ�̸ӷ� ����ϱ�

	// vvv�̰� ���߿� ��� ������� ���ս��ѵ� �ɵ���??
	bool		isFind{ false }; //�÷��̾ �����ȿ� ���Դ��� üũ
	bool		fightMod; //������� ��������� Ȯ�� - �÷��̾ �����̿� ���� - ������ hp����, �������� �Ⱥ���
	bool		getAttack; //�̰� �¾��� �� hp���� �� bool��

public:
	int			hp{ 100 }; //���� hp
	int			att{ 15 }; //���� ���ݷ�

public:
	Boss();
	~Boss();

	void Update();
	void Render();

	void Idle();
	void Look();
	void Move();
	void Attack();
	void Die();
};