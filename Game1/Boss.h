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
	ObImage*	imgRune = new ObImage(L"BossRune.png"); //바닥 소환진
	bool		isOnRune{ false }; //룬 위에 올라서면 true로 변경시켜서 idle상태로 만들기
	
	ObImage*	img = new ObImage(L"Boss.png"); //기본 이미지
	ObImage*	imgAtt = new ObImage(L"BossAtt.png"); //공격 이미지
	ObImage*	imgDie = new ObImage(L"MiniDie.png"); //사망 이미지

	BossState	bossState; //현재상태
	ObCircle*	range[3];
	float		distance;

	Vector2		firstPlace{ 0.0f, -1000.0f };

	float		moveSpeed; //보스 이동속도

	float		moveTimer{ 0.0f }; //공격타입 변경 타이머로 사용하기

	// vvv이거 셋중에 몇개는 사라지고 통합시켜도 될듯함??
	bool		isFind{ false }; //플레이어가 범위안에 들어왔는지 체크
	bool		isDie{ false }; //죽는 효과음 플레이 하려고 만들었음

public:
	bool		getHited{ false }; //맞는 효과음

	bool		getAttack{ false }; //이건 맞았을 때 hp관리 용 bool값
	bool		fightMod; //전투모드 비전투모드 확인 - 플레이어가 가까이에 들어옴 - 전투면 hp보임, 비전투면 안보임

	int			hp{ 30 }; //보스 hp
	int			att{ 8 }; //보스 공격력

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