#include<graphics.h>
#include<conio.h>
#include<ctime>
#include"IDN.h"
#include"bullet.h"
#include"cloud.h"
#include"Ememy01.h"
#include"map.h"
#include"number.h"
#include"boss.h"
#include"boss01_bullet.h"


/////////////  ����޷�������ʾȫ������Ļ�    ����1920*1080(������)����Ļ  ��Ļ���Ÿ�Ϊ125%���ɣ�����������


Bullet* ListHead = NULL; //ͷָ�� ���ڴ����ӵ���
Bullet* ListTail = NULL; //βָ�� ���ڱ����ӵ���

Cloud* ListHead2 = NULL; //ͷָ�� ���ڴ������߱�
Cloud* ListTail2 = NULL; //βָ�� ���ڱ������߱�

Enemy01* e1Head = NULL;  //ͷָ�� ���ڴ�������01��
Enemy01* e1Tail = NULL;  //βָ�� ���ڱ�������01��

Map* MapHead = NULL;     //ͷָ�� ���ڴ�����ͼ��
Map* MapTail = NULL;     //βָ�� ���ڱ�����ͼ��

RetNum* NumHead = NULL;  //ͷָ�� ���ڴ������ֱ�
RetNum* NumTail = NULL;  //βָ�� ���ڱ������ֱ�

BossBlt* BBHead = NULL;  //ͷָ�� ���ڴ���Boss�ӵ���
BossBlt* BBTail = NULL;  //βָ�� ���ڱ���Boss�ӵ���

Boss01 b;                //����Boss����

int main()
{
	srand((unsigned int)time(NULL));  //���ڴ��������

	IDN Game;             //��������
	Game.start_game();    //��Ϸ��ʼ֮ǰ��׼������

	while (1)
	{
		if (Game.which == 0)  //���˵�����
		{
			Game.MAIN();
			Game.GameEnd();
		}
		else if (Game.which == 1)  //��Ϸ����
		{
			Game.draw_map(MapHead, MapTail);
			Game.updateWithoutInput(ListHead2, ListTail2);
			Game.play_game(ListHead, ListTail, ListHead2, ListTail2);
			Game.draw_char();
			Game.creat_enemy01(e1Head, e1Tail);
			Game.boss_01(b,BBHead,BBTail);
			Game.blast_Boss(b);
			Game.blast_enemy(e1Head);
			Game.attack_enemy01(ListHead, e1Head,b);
			Game.eat_item01(ListHead2, ListTail2);
			Game.mouse_move(e1Head, ListHead, ListTail, ListHead2, MapHead, NumHead);
			Game.GameEnd();
		}
		else if (Game.which == 2)  //ѡͼ����
		{
			Game.chose_map();
			Game.GameEnd();
		}
		else if (Game.which == 3) //�ɼ��������
		{
			Game.result(NumHead, NumTail, e1Head, ListHead, ListHead2, MapHead,b,BBHead);
			Game.GameEnd();
		}
		else if (Game.which == 4) //��������
		{
			Game.help_player();
			Game.GameEnd();
		}
		else if (Game.which == 5)
		{
			Game.score_list();
			Game.GameEnd();
		}
	}

	int zero = _getch();
	closegraph();
	return 0;
}