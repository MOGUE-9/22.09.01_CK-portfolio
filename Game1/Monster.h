#pragma once

enum class MonsterState
{
	IDLE,
	LOOK = 200,
	MOVE = 150,
	ATTACK = 25,
	DIE
};

class Monster : public Character
{
private:
	ObImage*		img = new ObImage(L"Mini.png"); //�⺻ �̹���
	ObImage*		imgAtt = new ObImage(L"MiniAtt.png"); //���� �̹���
	ObImage*		imgDie = new ObImage(L"MiniDie.png"); //��� �̹���

	MonsterState	monsterState;
	ObCircle*		range[3];
	float			distance;

	bool			scaleSwitching;
	
	float			moveTimer{ 0.0f }; //��ȸ��ȯ Ÿ�̸� ���µ� ������ �ȵ��̾��ٰ� ��?�ε�
	
	Vector2			freeMov{ DOWN }; //�����̵� ���Ⱚ
	bool			isFind{ false }; //�÷��̾ �ֺ��� �Դ��� üũ



	int				playerHP{ 0 };
	
public:
	int				hp; //�� hp
	int				att{ 5 }; //�� ���ݷ�

	//�ٵ� �̰� ��� �ɵ� ������ ����̴ϱ�
	bool			fightMod{ false }; //������� ��������� Ȯ�� - �÷��̾ �����̿� ���� - ������ hp����, �������� �Ⱥ���

		//�̰� ���� �׳� hp�� �����ϰ� ���൵ ������ .... 
	bool			getHit{ false }; //���ڰ���
	bool			getJump{ false }; //��������

	bool			getHited{ false }; //�´»����
	bool			getAttack{ false }; //ü�°��� Ÿ�̹� Ȯ�ο� .. Ÿ�̸�? ������

private:

	void Idle();
	void Look();
	void Move();
	void Attack();
	void Die();

public:
	Monster();
	~Monster();

	void Update();
	void Render();

	void MonAtt(int& plHp); //���� ����

	void GetHp(int plHp); //�÷��̾� hp��������
	int	 SetHp(); //�÷��̾����� hp �����ֱ�
};

