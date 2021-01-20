#pragma once
#include<cstdio>

class BossBlt
{
public:
	double bossblt_X;            //子弹坐标
	double bossblt_Y;
	double bossblt_speed = 3.2;   //子弹移动速度
	int bossblt_type;           //子弹类型
	bool isext = true;          //这个用于判断子弹是否应该存在
	

	BossBlt* Next;

};
