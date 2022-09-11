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

	ObRect*		getBox; //pl에게 자석처럼 끌려가기 위한 용도의 getBox

	int			mDirState;
	float		attackTime;

	bool		gearOnoff; //true면 장비중, false면 장비해제


public:
					// 마우스 위치 받아오기
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

