#pragma once

enum class BossState
{
	IDLE,
	BACK = 800,
	MOVE = 500,
	ATTACK = 150,
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

	float		moveSpeed; //���� �̵��ӵ�

	float		moveTimer{ 0.0f }; //����Ÿ�� ���� Ÿ�̸ӷ� ����ϱ�

	// vvv�̰� ���߿� ��� ������� ���ս��ѵ� �ɵ���??
	bool		isFind{ false }; //�÷��̾ �����ȿ� ���Դ��� üũ

public:
	bool		getAttack{ false }; //�̰� �¾��� �� hp���� �� bool��
	bool		fightMod; //������� ��������� Ȯ�� - �÷��̾ �����̿� ���� - ������ hp����, �������� �Ⱥ���

	int			hp{ 10 }; //���� hp
	int			att{ 15 }; //���� ���ݷ�

public:
	Boss();
	~Boss();

	void Update();
	void Render();

	void Idle();
	void Back();
	void Move();
	void Attack();
	void Die();
};