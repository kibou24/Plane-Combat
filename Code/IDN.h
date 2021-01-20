#pragma once        //��ֹͷ�ļ��ظ�����
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include"bullet.h"
#include"cloud.h"
#include"Ememy01.h"
#include"map.h"
#include"number.h"
#include"boss.h"
#include"boss01_bullet.h"

class IDN
{
public:
	//��ɫ����
	double char_X = 440.0;
	double char_Y = 900.0;
	int char_HP = 500;   //��ɫѪ����ʼֵ
	double bullet_Att = 100.0;   //��ɫ��������ʼֵ
	int which = 0;   //�ж�λ���ĸ�����  
	//0��ʾ���˵�  1��ʾ��Ϸ����   2��ʾѡ���ͼ����  3��ʾ�ɼ��������  4��ʾ��������  5��ʾ���а����

	//���� 25 ������

	//���˵�����
	void MAIN();

	//ѡ���ͼ����
	void chose_map();

	//��������
	void help_player();

	//��������
	void score_list();

	//�ɼ��������
	void result(RetNum*& TempHead, RetNum*& TempTail,Enemy01*& TempHead1, Bullet*& TempHead2, Cloud*& TempHead3, Map*& TempHead4, Boss01& b, BossBlt*& BBHead);

	//���������Ϣ
	void save_score();

	//��ȡ������Ϣ
	void readin_score();

	//Boss01
	void boss_01(Boss01& b, BossBlt*& BBHead, BossBlt*& BBTail);
	
	//�����ڽ�������ӡ���ַ���
	void Print(int N,RetNum*&TempHead, RetNum*& TempTail);

	//���ڴ������ֱ�
	void creat_Num(RetNum*& TempHead, RetNum*& TempTail, double X, double Y);

	//���ڸ���һЩ�������Ե�
	void updateWithoutInput(Cloud*& TempHead, Cloud*& TempTail);

	//���Ʊ���
	void draw_map(Map*& MapHead, Map*& MapTail);

	//���ڳ�ʼ����Ϸ����
	void show_gameover(Enemy01*& TempHead, Bullet*& TempHead2, Cloud*& TempHead3, Map*& TempHead4,RetNum*&TempHead5, Boss01& b, BossBlt*& BBHead);

	//�����ӵ���
	void add_bullet(double X, double Y, Bullet*& TempHead, Bullet*& TempTail);

	//����BOSS�ӵ���
	void add_Boss_blt(BossBlt*& BBHead, BossBlt*& BBTail, Boss01& b);

	//Ϊ��Ϸ��ʼ��׼��
	void start_game();

	//���Ƶ���
	void draw_cloud(Cloud*& TempHead, Cloud*& TempTail);

	//������Ϸ�е������Ϊ
	void mouse_move(Enemy01*& TempHead0, Bullet*& TempHead, Bullet*& TempTail, Cloud*& TempHead3, Map*& TempHead4,RetNum*&TempHead5);

	//���ƽ�ɫ
	void draw_char();

	//��Ϸ�����е�һЩ��Ϊ
	void play_game(Bullet*& TempHead, Bullet*& TempTail, Cloud*& TempHead2, Cloud*& TempTail2);

	//��������01
	void creat_enemy01(Enemy01*& TempHead, Enemy01*& TempTail);

	//�жϺ͵���01����ײ���
	void attack_enemy01(Bullet*& TempHead, Enemy01*& TempHead2, Boss01& b);

	//���Ʊ�ը����
	void blast_enemy(Enemy01*& Temp);

	//����Boss��ը����
	void blast_Boss(Boss01 & b);

	//�жϺ͵���01����ײ���
	void eat_item01(Cloud*& TempHead, Cloud*& TempTail);

	//����
	void GameEnd();
};