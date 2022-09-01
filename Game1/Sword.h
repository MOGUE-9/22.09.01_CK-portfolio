#pragma once

enum class SwordState
{
	IDLE,
	ATTACK
};

class Sword : public Weapon
{
	ObImage* sword;

	SwordState swordState;
		
public:
	void Idle();
	void Attack();

public:

	Sword();
	~Sword();

	void Update();
	void Render();

};

