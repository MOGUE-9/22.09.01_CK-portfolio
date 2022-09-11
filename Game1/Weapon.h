#pragma once

enum MouseDir
{
	mDir_R,
	mDir_L,
	mDir_T,
	mDir_B,
	mDir_N
};

class Weapon
{
protected:

	ObRect*		col;
	Vector2		target;
	ObImage*	img;

	ObCircle*	range;
	ObRect*		hitBox;

	ObRect*		getBox; //pl���� �ڼ�ó�� �������� ���� �뵵�� getBox

	int			mDirState;
	float		attackTime;

	bool		gearOnoff; //true�� �����, false�� �������


public:
					// ���콺 ��ġ �޾ƿ���
	void SetWeaponPos(Vector2 target);

	int GetWeaponDir()
	{
		return mDirState;
	}

	void SetTarget(Vector2 target)
	{
		this->target = target;
	}

	Vector2 GetPos()
	{
		return col->GetWorldPos();
	}

	void SetPos(Vector2 pos)
	{
		col->SetWorldPos(pos);
	}

	void attackCoolTime()
	{
		hitBox->colOnOff = false;
	}

	ObRect* ReturnCol()
	{
		return col;
	}

	ObRect* ReturnHitBox()
	{
		return hitBox;
	}

	void GetHiBox(ObRect* box)
	{
		getBox = box;
	}

	void GearOn();

	void GearOff();

};

