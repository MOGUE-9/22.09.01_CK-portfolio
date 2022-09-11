#include "stdafx.h"

void Weapon::SetWeaponPos(Vector2 target)
{
	Vector2 dir = target - col->GetWorldPos();
	float radian = Utility::DirToRadian(dir);

	//������
	if (-DIV4PI <= radian && radian <= DIV4PI)
	{
		mDirState = mDir_R;
	}
	else if (DIV4PI <= radian && radian <= DIV2PI + DIV4PI)
	{
		mDirState = mDir_T;
	}
	else if (-(DIV2PI + DIV4PI) <= radian && radian <= -DIV4PI)
	{
		mDirState = mDir_B;
	}
	else
	{
		mDirState = mDir_L;
	}
}

void Weapon::GearOn()
{
	gearOnoff = true;
	col->visible = true;
	img->visible = true;
	gearOnoff = true;
}

void Weapon::GearOff()
{
	gearOnoff = false;
	col->visible = false;
	img->visible = false;
	gearOnoff = false;
}
