#pragma once
#include<cstdio>

class Boss01
{
public:
	double boss_HP = 25000;      //BOSS��Ѫ��
	double boss_Att = 30;        //Boss�Ĺ���
	double boss_speed = 2;		 //Boss���ٶ�
	double boss_Xspeed = 0.8;    //Boss�����ƶ����ٶ�
	int boss_BulletType = 1;	 //Boss���ӵ�����
	int boss_attspeed = 3;       //Boss�Ĺ���Ƶ��

	double boss_X = 0.0;         //Boss������
	double boss_Y = 0.0;

	int boss_isAtt = 0;          //Boss�Ƿ񹥻���û���õ���
	int boss_AttType = 0;        //Boss�Ĺ�������
	int boss_Type1 = 1;          //��û���õ���

	int B_Lsec = 0;             //��¼ǰ��ʱ��
	int B_Asec = 0;             //��¼����ʱ��
	int ifB_Lsec = 0;           //�ж�ǰ��ʱ���Ƿ��Ѿ���¼
	int ifB_Asec = 0;			//�жϺ���ʱ���Ƿ��Ѿ���¼
	int ifblast = 0;            //�ж��Ƿ�Ӧ�ñ�ը  1Ϊ��Ӧ�� 0Ϊ������ը
	int blast_i = 0;            //��������
	int blast_j = 0;            //��������

};
