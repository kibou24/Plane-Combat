#pragma once
#include<cstdio>

class RetNum
{
public:
	double num_X = 0;    //数字放置在画布中的坐标
	double num_Y = 0;

	double drawnumX = 0;  //对应的数字在图中的坐标
	double drawnumY = 0;

	RetNum* Next;
};
