#include "stdafx.h"

void Weapon::SetWeaponPos(Vector2 target)
{
	Vector2 dir = target - col->GetWorldPos();
	float radian = Utility::DirToRadian(dir);

	//¿À¸¥ÂÊ
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

int Weapon::GetWeaponDir()
{
	return mDirState;
}
