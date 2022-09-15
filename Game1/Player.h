#pragma once

enum class PlayerState
{
	IDLE,
	WALK,
	ACTION
};

class Player : public Character
{
private:
	ObImage*	walk;
	ObImage*	action;

	PlayerState plState;
	
	float		rollTime;

	Vector2		lastPos;
public:
	int			hp{ 30 };

private:
	void Idle();
	void Walk();
	void Action();

	void Input();

public:
	Player();
	~Player();

	void Update();
	void Render();

	void StepBack();
};

