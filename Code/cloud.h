#pragma once
#include<cstdio>

class Cloud
{
public:
	double cloud_X;     //道具坐标
	double cloud_Y;
	double cloud_speed = 1;   //道具移动速度
	int NumType = 1;   //这个是用来记录随机数的
	int type = 1;      //这个是根据上面的随机数来判断道具类型的
	bool isext = true;

	Cloud* Next;
};