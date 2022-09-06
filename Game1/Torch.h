#pragma once

enum class TorchState
{
	STAND, //������ (��������)
	MINI, //���� (���� �� �ִ� ����)
	NONE //���� (�Ⱥ��̴� ����)
};

class Torch : public Weapon
{
	ObImage*	torch;
	ObImage*	torchIcon;

	TorchState	torchState;

	bool		isInterSec{ false };

	Vector2		playerPivot; //mini�����϶� ������ ��ǥ

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