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
	ObImage*	img = new ObImage(L"Boss.png"); //기본 이미지
	ObImage*	imgAtt = new ObImage(L"BossAtt.png"); //공격 이미지
	ObImage*	imgDie = new ObImage(L"MiniDie.png"); //사망 이미지

	BossState	bossState; //현재상태
	ObCircle*	range[3];
	float		distance;

	float		moveTimer{ 0.0f }; //공격타입 변경 타이머로 사용하기

	// vvv이거 셋중에 몇개는 사라지고 통합시켜도 될듯함??
	bool		isFind{ false }; //플레이어가 범위안에 들어왔는지 체크
	bool		fightMod; //전투모드 비전투모드 확인 - 플레이어가 가까이에 들어옴 - 전투면 hp보임, 비전투면 안보임
	bool		getAttack; //이건 맞았을 때 hp관리 용 bool값

public:
	int			hp{ 100 }; //보스 hp
	int			att{ 15 }; //보스 공격력

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