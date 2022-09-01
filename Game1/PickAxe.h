#pragma once
enum class AxeState
{
	IDLE,
	ATTACK
};

class PickAxe : public Weapon
{
	ObImage* axe;

	AxeState axeState;

public:
	void Idle();
	void Attack();

public:

	PickAxe();
	~PickAxe();

	void Update();
	void Render();

};

