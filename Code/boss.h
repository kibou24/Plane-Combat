#pragma once
#include<cstdio>

class Boss01
{
public:
	double boss_HP = 25000;      //BOSS的血量
	double boss_Att = 30;        //Boss的攻击
	double boss_speed = 2;		 //Boss的速度
	double boss_Xspeed = 0.8;    //Boss左右移动的速度
	int boss_BulletType = 1;	 //Boss的子弹种类
	int boss_attspeed = 3;       //Boss的攻击频率

	double boss_X = 0.0;         //Boss的坐标
	double boss_Y = 0.0;

	int boss_isAtt = 0;          //Boss是否攻击（没有用到）
	int boss_AttType = 0;        //Boss的攻击类型
	int boss_Type1 = 1;          //（没有用到）

	int B_Lsec = 0;             //记录前置时间
	int B_Asec = 0;             //记录后置时间
	int ifB_Lsec = 0;           //判断前置时间是否已经记录
	int ifB_Asec = 0;			//判断后置时间是否已经记录
	int ifblast = 0;            //判断是否应该爆炸  1为不应该 0为即将爆炸
	int blast_i = 0;            //绘制行数
	int blast_j = 0;            //绘制列数

};
