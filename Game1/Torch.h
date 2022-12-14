#pragma once

enum class TorchState
{
	STAND, //세워둠 (고정상태)
	MINI, //깨짐 (먹을 수 있는 상태)
	NONE //먹힘 (안보이는 상태)
};

class Torch : public Weapon
{
	//ObImage*	torch;


	ObImage*	torchIcon;

	TorchState	torchState;

	bool		isInterSec{ false };

	float		udTimer;
	Vector2		ud{ 0.0f, 1.0f }; //mini상태일때 위아래로 제자리 움직임 방향
	Vector2		playerPivot; //mini상태일때 가야할 좌표

public:

	int			count{ 3 };
	//int			a; //count 잘 깎이는지 확인용이었음


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