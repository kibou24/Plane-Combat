#pragma once
#include<cstdio>

class Bullet
{
public:
	double bullet_X;            //�ӵ�����
	double bullet_Y;
	double bullet_speed = 12;   //�ӵ��ƶ��ٶ�
	int bullet_type;           //�ӵ�����
	bool isext = true;          //��������ж��ӵ��Ƿ�Ӧ�ô���

	Bullet* Next;
};