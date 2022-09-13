#pragma once

enum class SwordState
{
	IDLE,
	ATTACK
};

class Sword : public Weapon
{
	//ObImage*	sword;


	SwordState	swordState;

	float		attackTime;

public:
	int		att{ 5 }; //������ݷ�
		
public:
	void Idle();
	void Attack();

public:

	Sword();
	~Sword();

	void Update();
	void Render();

	

};

