#pragma once
#include<cstdio>

class Map
{
public:
	int MapType = 1;   //��ͼ����
	double map_Y=0;    //��ͼ������
	double map_speed = 1.2;   //��ͼ�ƶ��ٶ�

	Map* Next;
};