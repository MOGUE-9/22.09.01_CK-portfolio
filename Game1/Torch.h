#pragma once
class Torch : public Weapon
{
	ObImage* torch;

	bool isInterSec{ false };

public:
	Torch();
	~Torch();

	void Update();
	void Render();

	void isInterSect();

	

};

