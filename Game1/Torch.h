#pragma once

enum class TorchState
{
	STAND, //세워둠 (고정상태)
	MINI, //깨짐 (먹을 수 있는 상태)
	NONE //먹힘 (안보이는 상태)
};

class Torch : public Weapon
{
	ObImage*	torch;
	ObImage*	torchIcon;

	TorchState	torchState;

	bool		isInterSec{ false };

	Vector2		playerPivot; //mini상태일때 가야할 좌표

public:

	int			count{ 3 };
	int a;


public:

	Torch();
	~Torch();

	void Update();
	void Render();

	void Stand();
	void Mini();
	void None();

	bool isInterSect(ObRect* col);
	
	void GetPlayer(Vector2 pivot);

};