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
	ObRect*	colRune = new ObRect();
	ObImage*	imgRune = new ObImage(L"BossRune.png"); //�ٴ� ��ȯ��
	bool		isOnRune{ false }; //�� ���� �ö󼭸� true�� ������Ѽ� idle���·� �����
	
	ObImage*	img = new ObImage(L"Boss.png"); //�⺻ �̹���
	ObImage*	imgAtt = new ObImage(L"BossAtt.png"); //���� �̹���
	ObImage*	imgDie = new ObImage(L"MiniDie.png"); //��� �̹���

	BossState	bossState; //�������
	ObCircle*	range[3];
	float		distance;

	Vector2		firstPlace{ 0.0f, -1000.0f };

	float		moveSpeed; //���� �̵��ӵ�

	float		moveTimer{ 0.0f }; //����Ÿ�� ���� Ÿ�̸ӷ� ����ϱ�

	// vvv�̰� ���߿� ��� ������� ���ս��ѵ� �ɵ���??
	bool		isFind{ false }; //�÷��̾ �����ȿ� ���Դ��� üũ
	bool		isDie{ false }; //�״� ȿ���� �÷��� �Ϸ��� �������

public:
	bool		getHited{ false }; //�´� ȿ����

	bool		getAttack{ false }; //�̰� �¾��� �� hp���� �� bool��
	bool		fightMod; //������� ��������� Ȯ�� - �÷��̾ �����̿� ���� - ������ hp����, �������� �Ⱥ���

	int			hp{ 30 }; //���� hp
	int			att{ 8 }; //���� ���ݷ�

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