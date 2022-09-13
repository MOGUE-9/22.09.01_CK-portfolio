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
	int		att{ 5 }; //무기공격력
		
public:
	void Idle();
	void Attack();

public:

	Sword();
	~Sword();

	void Update();
	void Render();

	

};

