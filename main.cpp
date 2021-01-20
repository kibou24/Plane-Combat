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


/////////////  如果无法正常显示全部画面的话    对于1920*1080(或左右)的屏幕  屏幕缩放改为125%即可！！！！！！


Bullet* ListHead = NULL; //头指针 用于创建子弹表
Bullet* ListTail = NULL; //尾指针 用于遍历子弹表

Cloud* ListHead2 = NULL; //头指针 用于创建道具表
Cloud* ListTail2 = NULL; //尾指针 用于遍历道具表

Enemy01* e1Head = NULL;  //头指针 用于创建敌人01表
Enemy01* e1Tail = NULL;  //尾指针 用于遍历敌人01表

Map* MapHead = NULL;     //头指针 用于创建地图表
Map* MapTail = NULL;     //尾指针 用于遍历地图表

RetNum* NumHead = NULL;  //头指针 用于创建数字表
RetNum* NumTail = NULL;  //尾指针 用于遍历数字表

BossBlt* BBHead = NULL;  //头指针 用于创建Boss子弹表
BossBlt* BBTail = NULL;  //尾指针 用于遍历Boss子弹表

Boss01 b;                //创建Boss对象

int main()
{
	srand((unsigned int)time(NULL));  //用于创建随机数

	IDN Game;             //创建对象
	Game.start_game();    //游戏开始之前的准备工作

	while (1)
	{
		if (Game.which == 0)  //主菜单界面
		{
			Game.MAIN();
			Game.GameEnd();
		}
		else if (Game.which == 1)  //游戏界面
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
		else if (Game.which == 2)  //选图界面
		{
			Game.chose_map();
			Game.GameEnd();
		}
		else if (Game.which == 3) //成绩结算界面
		{
			Game.result(NumHead, NumTail, e1Head, ListHead, ListHead2, MapHead,b,BBHead);
			Game.GameEnd();
		}
		else if (Game.which == 4) //帮助界面
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