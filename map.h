#pragma once
#include<cstdio>

class Map
{
public:
	int MapType = 1;   //地图种类
	double map_Y=0;    //地图纵坐标
	double map_speed = 1.2;   //地图移动速度

	Map* Next;
};