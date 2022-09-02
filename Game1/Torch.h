#pragma once
class Torch : public Weapon
{
	ObImage* torch;

public:
	Torch();
	~Torch();

	void Update();
	void Render();
};

