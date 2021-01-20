#pragma once
#include<cstdio>

class Bullet
{
public:
	double bullet_X;            //子弹坐标
	double bullet_Y;
	double bullet_speed = 12;   //子弹移动速度
	int bullet_type;           //子弹类型
	bool isext = true;          //这个用于判断子弹是否应该存在

	Bullet* Next;
};