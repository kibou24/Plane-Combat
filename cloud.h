#pragma once
#include<cstdio>

class Cloud
{
public:
	double cloud_X;     //��������
	double cloud_Y;
	double cloud_speed = 1;   //�����ƶ��ٶ�
	int NumType = 1;   //�����������¼�������
	int type = 1;      //����Ǹ����������������жϵ������͵�
	bool isext = true;

	Cloud* Next;
};