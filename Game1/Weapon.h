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

	ObRect* col;
	Vector2 target;

	int mDirState;

public:
					// 마우스 위치 받아오기
	void SetWeaponPos(Vector2 target);

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

};

