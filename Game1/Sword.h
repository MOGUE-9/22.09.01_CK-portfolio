#pragma once

enum class SwordState
{
	IDLE,
	ATTACK
};

class Sword : public Weapon
{
	//ObImage*	sword;

	float		att{ 5.0f }; //������ݷ�

	SwordState	swordState;

	float		attackTime;
		
public:
	void Idle();
	void Attack();

public:

	Sword();
	~Sword();

	void Update();
	void Render();

	

};

