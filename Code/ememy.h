#pragma once
#include<cstdio>

class Enemy
{
public:
	int enemy_HP=200;           //����HP
	int enemy_bullettype = 1;   //Ŀǰ�������û���κε�����
	double enemy_speed =2;      //���˵��ƶ��ٶ�
	int EnemyType;              //�����������¼�������
	int Type=1;                 //����Ǹ����������������жϵ������͵�
	double enemy_X;             //���˵�����
	double enemy_Y;

	int B_Lsec = 0;             //��¼ǰ��ʱ��
	int B_Asec = 0;             //��¼����ʱ��
	int ifB_Lsec = 0;           //�ж�ǰ��ʱ���Ƿ��Ѿ���¼
	int ifB_Asec = 0;			//�жϺ���ʱ���Ƿ��Ѿ���¼
	int ifblast = 1;            //�ж��Ƿ�Ӧ�ñ�ը  1Ϊ��Ӧ�� 0Ϊ������ը
	int blast_i = 0;            //��������
	int blast_j = 0;            //��������
	int stoexist = 1;           //�õл��Ƿ�Ӧ�ô���
};
