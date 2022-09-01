#include "stdafx.h"

void Character::LookTarget(Vector2 target, ObImage* img)
{
	Vector2 dir = target - col->GetWorldPos();
	float radian = Utility::DirToRadian(dir);

	//오른쪽
	if (-DIV4PI <= radian && radian <= DIV4PI)
	{
		//cout << "우측" << endl;
		dirState = Dir_R;
	}
	else if (DIV4PI <= radian && radian <= DIV2PI)
	{
		//cout << "우측상단" << endl;
		dirState = Dir_RT;
	}
	else if (DIV2PI <= radian && radian <= DIV2PI + DIV4PI)
	{
		//cout << "좌측상단" << endl;
		dirState = Dir_LT;
	}
	else if (-(DIV2PI + DIV4PI) <= radian && radian <= -DIV2PI)
	{
		//cout << "좌측하단" << endl;
		dirState = Dir_LB;
	}
	else if (-DIV4PI >= radian && radian >= -DIV2PI)
	{
		//cout << "우측하단" << endl;
		dirState = Dir_RB;
	}
	else
	{
		//cout << "좌측" << endl;
		dirState = Dir_L;
	}

	img->frame.y = frameY[dirState];
}

