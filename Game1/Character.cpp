#include "stdafx.h"

void Character::LookTarget(Vector2 target, ObImage* img)
{
	Vector2 dir = target - col->GetWorldPos();
	float radian = Utility::DirToRadian(dir);

	//������
	if (-DIV4PI <= radian && radian <= DIV4PI)
	{
		//cout << "����" << endl;
		dirState = Dir_R;
	}
	else if (DIV4PI <= radian && radian <= DIV2PI)
	{
		//cout << "�������" << endl;
		dirState = Dir_RT;
	}
	else if (DIV2PI <= radian && radian <= DIV2PI + DIV4PI)
	{
		//cout << "�������" << endl;
		dirState = Dir_LT;
	}
	else if (-(DIV2PI + DIV4PI) <= radian && radian <= -DIV2PI)
	{
		//cout << "�����ϴ�" << endl;
		dirState = Dir_LB;
	}
	else if (-DIV4PI >= radian && radian >= -DIV2PI)
	{
		//cout << "�����ϴ�" << endl;
		dirState = Dir_RB;
	}
	else
	{
		//cout << "����" << endl;
		dirState = Dir_L;
	}

	img->frame.y = frameY[dirState];
}

