#pragma once
#include<cstdio>

class BossBlt
{
public:
	double bossblt_X;            //�ӵ�����
	double bossblt_Y;
	double bossblt_speed = 3.2;   //�ӵ��ƶ��ٶ�
	int bossblt_type;           //�ӵ�����
	bool isext = true;          //��������ж��ӵ��Ƿ�Ӧ�ô���
	

	BossBlt* Next;

};
