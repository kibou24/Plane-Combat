#pragma once
#include<cstdio>

class Enemy
{
public:
	int enemy_HP=200;           //敌人HP
	int enemy_bullettype = 1;   //目前这个变量没有任何的作用
	double enemy_speed =2;      //敌人的移动速度
	int EnemyType;              //这个是用来记录随机数的
	int Type=1;                 //这个是根据上面的随机数来判断敌人类型的
	double enemy_X;             //敌人的坐标
	double enemy_Y;

	int B_Lsec = 0;             //记录前置时间
	int B_Asec = 0;             //记录后置时间
	int ifB_Lsec = 0;           //判断前置时间是否已经记录
	int ifB_Asec = 0;			//判断后置时间是否已经记录
	int ifblast = 1;            //判断是否应该爆炸  1为不应该 0为即将爆炸
	int blast_i = 0;            //绘制行数
	int blast_j = 0;            //绘制列数
	int stoexist = 1;           //该敌机是否应该存在
};
