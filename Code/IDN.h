#pragma once        //防止头文件重复包含
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
	//角色坐标
	double char_X = 440.0;
	double char_Y = 900.0;
	int char_HP = 500;   //角色血量初始值
	double bullet_Att = 100.0;   //角色攻击力初始值
	int which = 0;   //判断位于哪个界面  
	//0表示主菜单  1表示游戏界面   2表示选择地图界面  3表示成绩结算界面  4表示帮助界面  5表示排行榜界面

	//共有 25 个函数

	//主菜单界面
	void MAIN();

	//选择地图界面
	void chose_map();

	//帮助界面
	void help_player();

	//排名界面
	void score_list();

	//成绩结算界面
	void result(RetNum*& TempHead, RetNum*& TempTail,Enemy01*& TempHead1, Bullet*& TempHead2, Cloud*& TempHead3, Map*& TempHead4, Boss01& b, BossBlt*& BBHead);

	//保存分数信息
	void save_score();

	//读取分数信息
	void readin_score();

	//Boss01
	void boss_01(Boss01& b, BossBlt*& BBHead, BossBlt*& BBTail);
	
	//用于在结算界面打印数字分数
	void Print(int N,RetNum*&TempHead, RetNum*& TempTail);

	//用于创建数字表
	void creat_Num(RetNum*& TempHead, RetNum*& TempTail, double X, double Y);

	//用于更新一些敌人属性等
	void updateWithoutInput(Cloud*& TempHead, Cloud*& TempTail);

	//绘制背景
	void draw_map(Map*& MapHead, Map*& MapTail);

	//用于初始化游戏数据
	void show_gameover(Enemy01*& TempHead, Bullet*& TempHead2, Cloud*& TempHead3, Map*& TempHead4,RetNum*&TempHead5, Boss01& b, BossBlt*& BBHead);

	//创建子弹表
	void add_bullet(double X, double Y, Bullet*& TempHead, Bullet*& TempTail);

	//创建BOSS子弹表
	void add_Boss_blt(BossBlt*& BBHead, BossBlt*& BBTail, Boss01& b);

	//为游戏开始做准备
	void start_game();

	//绘制道具
	void draw_cloud(Cloud*& TempHead, Cloud*& TempTail);

	//设置游戏中的鼠标行为
	void mouse_move(Enemy01*& TempHead0, Bullet*& TempHead, Bullet*& TempTail, Cloud*& TempHead3, Map*& TempHead4,RetNum*&TempHead5);

	//绘制角色
	void draw_char();

	//游戏过程中的一些行为
	void play_game(Bullet*& TempHead, Bullet*& TempTail, Cloud*& TempHead2, Cloud*& TempTail2);

	//创建敌人01
	void creat_enemy01(Enemy01*& TempHead, Enemy01*& TempTail);

	//判断和敌人01的碰撞情况
	void attack_enemy01(Bullet*& TempHead, Enemy01*& TempHead2, Boss01& b);

	//绘制爆炸动画
	void blast_enemy(Enemy01*& Temp);

	//绘制Boss爆炸动画
	void blast_Boss(Boss01 & b);

	//判断和道具01的碰撞情况
	void eat_item01(Cloud*& TempHead, Cloud*& TempTail);

	//结束
	void GameEnd();
};