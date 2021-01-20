#include<graphics.h>
#include<fstream>
#include"IDN.h"
#include"bullet.h"
#include"cloud.h"
#include"map.h"
#include"boss.h"
#include"boss01_bullet.h"
#pragma comment(lib,"Winmm.lib")
#define High 980          //定义画布高度
#define Width 650         //定义画布宽度
#define SHOW_BOSS01 12500 //定义BOSS01出现的时机
#define BOSSHP 25000      //定义BOSS血量
#define FILE "data.dat"   //定义文件名
using namespace std;

SYSTEMTIME ti;              //获取时间
int Lsec = 0;               //前置时间
int Asec = 0;               //后置时间
int ifLsec = 0;             //0表示还未获取时间
int ifAsec = 0;
int ifBoss2 = 0;            //判断Boss是否二次出现



int result_mp3 = 1;       //用于判断结算音效是否播放
int boss_mp3 = 1;         //用于判断BOSS音效是否播放
int isBoss = 0;           //用于判断Boss01是否出现
int ifBossSe = 1;         //1表示Boss存活 即不刷新小怪

int startbutton = 1;      //判断开始按钮有没有被按下  1表示正常状态
int game_backbutton = 1;  //游戏界面的按钮
int cmp_backbutton = 1;   //选图界面的按钮
int helpbutton = 1;       //主界面的帮助按钮
int listbutton = 1;       //主界面的排名按钮

int cmp_map001_down = 1;  //按钮状态变量  控制小地图按钮1的明暗
int cmp_map002_down = 1;  //按钮状态变量  控制小地图按钮2的明暗
int cmp_map003_down = 1;  //按钮状态变量  控制小地图按钮3的明暗

int FullScore = 30;       //实时更新的满子弹数目
int score = FullScore;    //当前子弹数目
int ArmScore = 10;        //装填子弹数目（弹药回复力）
int btype = 1;            //子弹形态
int bret = 1;             //判断子弹是否升级  1为未升级

int KillNum = 0;          //当前击落敌机数目
int KillScore = 0;        //当前得分
double e1speed = 2;       //当前敌人01的速度
double e1_HP = 200.0;     //敌人01当前的HP
int i = 1;                //辅助判断击落敌机数是否是10的倍数(轮数)
int FullHP;               //实时更新的满血量
int temp_score;           //用于判断装弹后子弹数量是否越界
int EnemyType = 1;        //敌人01的类型
int RANGE = 600;          //控制出现敌机的间隔
int range;                //控制出现敌机的间隔0

int MType = 1;            //地图种类

int ksc = 0;              //绘制数字个数
int isksc = 1;            //用于控制  数字只能绘制一次  的变量

int SCORE[10] = {0};      //用于保存前十名的分数
int ifsave = 0;           //用于判断是否已经保存

int Main_music = 1;       //主界面音乐
int map01_music = 0;      //地图1音乐
int map02_music = 0;      //地图2音乐
int map03_music = 0;      //地图3音乐


IMAGE enemy01, enemy01_zz;//敌人01的三种形态
IMAGE enemy0102, enemy0102_zz;
IMAGE enemy0103, enemy0103_zz;

IMAGE Char, Char_zz;      //我方角色

IMAGE HP, HP_D;           //血条
IMAGE Arm;                //弹药槽

IMAGE bullet, bullet_zz;  //子弹
IMAGE bullet02, bullet02_zz;

IMAGE blast, blast_zz;   //爆炸动画
IMAGE Bblast, Bblast_zz;   //BOSS爆炸动画

IMAGE Main, bk, bk2, bk3;        //地图和主界面背景
IMAGE cmpbk, cmp, bk001, bk001d, bk001u, bk002, bk002d, bk002u, bk003, bk003d, bk003u;

IMAGE item01, item01_zz;  //三种道具
IMAGE item02, item02_zz;
IMAGE item03, item03_zz;

IMAGE title, title_zz;    //标题
IMAGE start, start_zz, startd, startd_zz;    //开始按键
IMAGE help, help_zz, helpd, helpd_zz;  //帮助按键
IMAGE helpbk;             //帮助界面


IMAGE back, back_zz;      //返回按键
IMAGE backd, backd_zz;    //返回按键按下
IMAGE listbtn, listbtnd,listbtn_zz;   //排行榜按键

IMAGE ret;                //成绩结算界面
IMAGE num, num_zz;        //数字图片
IMAGE ret2401, ret2402, ret2403, ret24_zz;  //结算界面对话框

IMAGE boss01, boss01_zz;         //Boss01
IMAGE boss01_att01, boss01_att01_zz;         //Boss01攻击1

IMAGE BB01, BB01_zz;             //Boss01的子弹
IMAGE BB02, BB02_zz;
IMAGE BB03, BB03_zz;

IMAGE list;                 //排行榜界面


void IDN::MAIN()
{
	putimage(0, 0, &Main);//绘制背景图
	putimage(Width / 2 - 250, High * 0.2, &title_zz, NOTSRCERASE);  //绘制标题
	putimage(Width / 2 - 250, High * 0.2, &title, SRCINVERT);

	outtextxy(Width * 0.05, High * 0.009, " 版本：1.1         二十四桥明月夜");

	result_mp3 = 1;//初始化结算音效

	if (startbutton == 1)  //开始按钮正常
	{
		putimage(Width / 2 - 83, High * 0.78, &start_zz, NOTSRCERASE);
		putimage(Width / 2 - 83, High * 0.78, &start, SRCINVERT);
	}
	else if (startbutton == 0)  //开始按钮被按下
	{
		putimage(Width / 2 - 83, High * 0.785, &startd_zz, NOTSRCERASE);
		putimage(Width / 2 - 83, High * 0.785, &startd, SRCINVERT);

		mciSendString(_T("close stmusic"), NULL, 0, NULL);
		mciSendString(_T("open data\\audio\\start.mp3 alias stmusic"), NULL, 0, NULL);
		mciSendString(_T("play stmusic"), NULL, 0, NULL);//播放一次音效

		FlushBatchDraw();
		Sleep(300);
		startbutton = 1;
		this->which = 2;
	}



	if (helpbutton == 1)  //帮助按钮正常
	{
		putimage(30, High * 0.03, &help_zz, NOTSRCERASE);
		putimage(30, High * 0.03, &help, SRCINVERT);
	}
	else if (helpbutton == 0)  //帮助按钮被按下
	{
		putimage(30, High * 0.03, &helpd_zz, NOTSRCERASE);
		putimage(30, High * 0.03, &helpd, SRCINVERT);

		mciSendString(_T("close hpmusic"), NULL, 0, NULL);
		mciSendString(_T("open data\\audio\\help.mp3 alias hpmusic"), NULL, 0, NULL);
		mciSendString(_T("play hpmusic"), NULL, 0, NULL);//播放一次音效

		FlushBatchDraw();
		Sleep(250);
		helpbutton = 1;
		this->which = 4;
	}

	if (listbutton == 1)  //开始按钮正常
	{
		putimage(Width / 2 - 100, High * 0.86, &listbtn_zz, NOTSRCERASE);
		putimage(Width / 2 - 100, High * 0.86, &listbtn, SRCINVERT);
	}
	else if (listbutton == 0)  //开始按钮被按下
	{
		putimage(Width / 2 - 100, High * 0.86, &listbtn_zz, NOTSRCERASE);
		putimage(Width / 2 - 100, High * 0.86, &listbtnd, SRCINVERT);

		mciSendString(_T("close lstmusic"), NULL, 0, NULL);
		mciSendString(_T("open data\\audio\\list.mp3 alias lstmusic"), NULL, 0, NULL);
		mciSendString(_T("play lstmusic"), NULL, 0, NULL);//播放一次音效

		FlushBatchDraw();
		Sleep(300);
		listbutton = 1;
		this->which = 5;
	}

	MOUSEMSG m;  //创建对象

	while (MouseHit())  //判断鼠标是否有动作
	{
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN)//按下鼠标左键时
		{
			if (m.x >= Width / 2 - 83 && m.x <= Width / 2 + 83 && m.y >= High * 0.78 && m.y <= High * 0.78 + 46)
			{
				startbutton = 0; //开始按钮被按下
			}

			if (m.x >= 30 && m.x <= 30 + 74 && m.y >= High * 0.03 && m.y <= High * 0.03 + 46)
			{
				helpbutton = 0; //帮助按钮被按下
			}

			if (m.x >= Width/2-100 && m.x <= Width / 2 +100 && m.y >= High * 0.86 && m.y <= High * 0.86 + 40)
			{
				listbutton = 0; //排行榜按钮被按下
			}
		}
	}
}

void IDN::start_game()
{
	initgraph(Width, High);//绘制画布

	setbkcolor(46154254);  //底色
	setbkmode(TRANSPARENT);//透明
	cleardevice();

	readin_score();  //游戏开始时读取记录
	
	loadimage(&title, _T("data//title.png"), 500, 320);   //标题
	loadimage(&title_zz, _T("data//title_zz.png"), 500, 320);

	loadimage(&ret2401, _T("data//ret2401.png"), Width, 223);  //ret24
	loadimage(&ret2402, _T("data//ret2402.png"), Width, 223);
	loadimage(&ret2403, _T("data//ret2403.png"), Width, 223);
	loadimage(&ret24_zz, _T("data//ret24_zz.png"), Width, 223);

	loadimage(&num, _T("data//number.png"), 384, 512);   //数字
	loadimage(&num_zz, _T("data//number_zz.png"), 384, 512);

	loadimage(&back, _T("data//back.png"), 89, 46);   //返回按钮
	loadimage(&back_zz, _T("data//back_zz.png"), 89, 46);
	loadimage(&backd, _T("data//backdown.png"), 89, 46);  //返回按钮按下
	loadimage(&backd_zz, _T("data//backdown_zz.png"), 89, 46);

	loadimage(&listbtn, _T("data//listbtn.png"), 200, 40);   //排名按钮
	loadimage(&listbtn_zz, _T("data//listbtn_zz.png"), 200, 40);
	loadimage(&listbtnd, _T("data//listbtn_down.png"), 200, 40);  //排名按钮按下

	loadimage(&ret, _T("data//result.png"), Width, High);  //结算背景

	loadimage(&Main, _T("data//MAIN.png"), Width, High);
	loadimage(&start, _T("data//start.png"), 166, 46);
	loadimage(&start_zz, _T("data//start_zz.png"), 166, 46);//开始按键
	loadimage(&startd, _T("data//startdown.png"), 166, 46);
	loadimage(&startd_zz, _T("data//startdown_zz.png"), 166, 46);//开始按键按下

	loadimage(&help, _T("data//help.png"), 74, 46);
	loadimage(&help_zz, _T("data//help_zz.png"), 74, 46);//帮助按键
	loadimage(&helpd, _T("data//helpd.png"), 74, 46);
	loadimage(&helpd_zz, _T("data//helpd_zz.png"), 74, 46);//帮助按键按下
	loadimage(&helpbk, _T("data//helpbk.png"), Width, High);//帮助界面背景

	loadimage(&list, _T("data//list.png"), Width, High);//排名界面背景

	loadimage(&enemy01, _T("data//e01.png"), 150, 150);
	loadimage(&enemy01_zz, _T("data//e01_zz.png"), 150, 150);//敌人01
	loadimage(&enemy0102, _T("data//e0102.png"), 150, 150);
	loadimage(&enemy0102_zz, _T("data//e0102_zz.png"), 150, 150);//敌人0102
	loadimage(&enemy0103, _T("data//e0103.png"), 150, 150);
	loadimage(&enemy0103_zz, _T("data//e0103_zz.png"), 150, 150);//敌人0103

	loadimage(&Char, _T("data//char.png"), 120, 120);
	loadimage(&Char_zz, _T("data//char_zz.png"), 120, 120);//角色

	loadimage(&boss01, _T("data//boss01.png"), 250, 250);
	loadimage(&boss01_zz, _T("data//boss01_zz.png"), 250, 250);//BOSS01

	loadimage(&boss01_att01, _T("data//boss01_att01.png"), 250, 250);
	loadimage(&boss01_att01_zz, _T("data//boss01_att01_zz.png"), 250, 250);//BOSS01攻击1

	loadimage(&bullet, _T("data//bullet.png"), 30, 75);
	loadimage(&bullet_zz, _T("data//bullet_zz.png"), 30, 75);//子弹

	loadimage(&bullet02, _T("data//bullet02.png"), 60, 75);
	loadimage(&bullet02_zz, _T("data//bullet02_zz.png"), 60, 75);//子弹02

	loadimage(&blast, _T("data//blast.png"), 512, 512);
	loadimage(&blast_zz, _T("data//blast_zz.png"), 512, 512);//爆炸动画

	loadimage(&Bblast, _T("data//blast.png"), 1024, 1024);
	loadimage(&Bblast_zz, _T("data//blast_zz.png"), 1024, 1024);//BOSS爆炸动画

	loadimage(&BB01, _T("data//BB01.png"), 30, 30);
	loadimage(&BB01_zz, _T("data//BB01_zz.png"),30,30);//BOSS子弹01
	loadimage(&BB02, _T("data//BB02.png"), 30, 30);
	loadimage(&BB02_zz, _T("data//BB02_zz.png"), 30, 30);//BOSS子弹02
	loadimage(&BB03, _T("data//BB03.png"), 30, 30);
	loadimage(&BB03_zz, _T("data//BB03_zz.png"), 30, 30);//BOSS子弹03

	loadimage(&HP, _T("data//HP.png"), 400, 35);//体力条
	loadimage(&HP_D, _T("data//HP_D.png"), 400, 35);

	loadimage(&bk, _T("data//map.png"), Width, High);//地图背景
	loadimage(&bk2, _T("data//map2.png"), Width, High);
	loadimage(&bk3, _T("data//map3.png"), Width, High);

	loadimage(&bk001, _T("data//map001.png"), 150, 150);//地图小图
	loadimage(&bk002, _T("data//map002.png"), 150, 150);//地图小图
	loadimage(&bk003, _T("data//map003.png"), 150, 150);//地图小图
	loadimage(&bk001d, _T("data//map001_down.png"), 150, 150);
	loadimage(&bk002d, _T("data//map002_down.png"), 150, 150);
	loadimage(&bk003d, _T("data//map003_down.png"), 150, 150);

	loadimage(&bk001u, _T("data//map001_up.png"), 150, 150);
	loadimage(&bk002u, _T("data//map002_up.png"), 150, 150);
	loadimage(&bk003u, _T("data//map003_up.png"), 150, 150);

	loadimage(&cmpbk, _T("data//cmpbk.png"), Width, High);//选图背景
	loadimage(&cmp, _T("data//cmp.png"), Width, 350);//选图背景

	loadimage(&Arm, _T("data//arm.png"), 400, 15);//弹药条

	loadimage(&item01, _T("data//item01.png"), 80, 80);
	loadimage(&item01_zz, _T("data//item01_zz.png"), 80, 80);//道具1  回复HP

	loadimage(&item02, _T("data//item02.png"), 80, 80);
	loadimage(&item02_zz, _T("data//item02_zz.png"), 80, 80);//道具2  恢复并增加弹药上限

	loadimage(&item03, _T("data//item03.png"), 80, 80);
	loadimage(&item03_zz, _T("data//item03_zz.png"), 80, 80);//道具3  恢复血量并增加攻击力


	//mciSendString(_T("open data\\audio\\bgm.mp3 alias bkmusic"), NULL, 0, NULL);//背景音乐
	//mciSendString(_T("play bkmusic repeat"), NULL, 0, NULL);

	FullHP = this->char_HP;//记录初始HP

	BeginBatchDraw();
}

void IDN::play_game(Bullet*& TempHead, Bullet*& TempTail , Cloud*& TempHead2, Cloud*& TempTail2 )
{
	GetLocalTime(&ti);

	putimage(Width * 0.08, High * 0.012, &HP_D);
	putimage(Width * 0.08, High * 0.012, 400 * this->char_HP / FullHP, 35, &HP, 0, 0); //放置实时血条

	putimage(Width * 0.08, High * 0.045, 400 * score / FullScore, 15, &Arm, 0, 0);  //放置实时弹药条
	outtextxy(Width * 0.02, High * 0.045, "弹药");

	char Hp[50];
	sprintf_s(Hp, "%d", this->char_HP);
	outtextxy(Width * 0.02, High * 0.02, "能量");
	outtextxy(Width * 0.1, High * 0.022, Hp);  //放置能量即数量

	char FHp[50];
	sprintf_s(FHp, "%d", FullHP);
	outtextxy(Width * 0.155, High * 0.02, "/");
	outtextxy(Width * 0.18, High * 0.022, FHp);  //放置满能量数量

	char s0[50];
	sprintf_s(s0, "%d", KillScore);
	outtextxy(Width * 0.02, High * 0.08, "得分");
	outtextxy(Width * 0.1, High * 0.081, s0);   //放置得分


	Cloud* Current2 = TempHead2;
	Cloud* TempQ2 = NULL;
	while (Current2)
	{
		if (Current2->type == 1)//绘制道具1
		{
			putimage(Current2->cloud_X, Current2->cloud_Y, &item01_zz, NOTSRCERASE);
			putimage(Current2->cloud_X, Current2->cloud_Y, &item01, SRCINVERT);
		}
		else if (Current2->type == 2)//绘制道具2
		{
			putimage(Current2->cloud_X, Current2->cloud_Y, &item02_zz, NOTSRCERASE);
			putimage(Current2->cloud_X, Current2->cloud_Y, &item02, SRCINVERT);
		}
		else if (Current2->type == 3)//绘制道具3
		{
			putimage(Current2->cloud_X, Current2->cloud_Y, &item03_zz, NOTSRCERASE);
			putimage(Current2->cloud_X, Current2->cloud_Y, &item03, SRCINVERT);
		}

		Current2->cloud_Y += Current2->cloud_speed;//让道具按设定的速度移动


		//对越界的道具做删除处理
		if (Current2->cloud_Y > High + 100.0 || Current2->isext == false)
		{
			if (Current2 == TempHead2 && Current2 == TempTail2)
			{
				TempHead2 = NULL;
				TempTail2 = NULL;
			}
			else if (Current2 == TempHead2 && TempHead2->Next == NULL)
			{
				TempHead2 = NULL;
				TempTail2 = NULL;
			}
			else if (Current2 == TempHead2)
			{
				Cloud* Temp = TempHead2;
				TempHead2 = TempHead2->Next;
				delete Temp;
				Temp = NULL;
			}
			else if (Current2->Next == NULL)
			{
				TempQ2->Next = NULL;
				delete Current2;
				Current2 = TempQ2;
			}
			else
			{
				Cloud* Temp = Current2;
				TempQ2->Next = Current2->Next;
				delete Temp;
				Temp = NULL;
				Current2 = TempQ2->Next;
			}
			Current2 = TempHead2;
		}

		TempQ2 = Current2;

		if (Current2 != NULL)
		{
			Current2 = Current2->Next;
		}
		
	}




	Bullet* Current = TempHead;
	Bullet* TempQ = NULL;
	Bullet* Temp = TempHead;
	Bullet* Temp2;
	while (Current)
	{
		if (Current->bullet_type == 1)  //绘制相应类型的子弹
		{
			putimage(Current->bullet_X - 16, Current->bullet_Y - 30, &bullet_zz, NOTSRCERASE);
			putimage(Current->bullet_X - 16, Current->bullet_Y - 30, &bullet, SRCINVERT);
		}
		else if (Current->bullet_type == 2)  //绘制相应类型的子弹
		{
			putimage(Current->bullet_X - 30, Current->bullet_Y - 35, &bullet02_zz, NOTSRCERASE);
			putimage(Current->bullet_X - 30, Current->bullet_Y - 35, &bullet02, SRCINVERT);
		}

		Current->bullet_Y -= Current->bullet_speed;//让子弹按设定的速度移动

		//对越界的子弹做删除处理
		if ((Current->bullet_Y < -100.0) || (Current->isext == false))
		{
			if (Current == TempHead && Current == TempTail)
			{
				TempHead = NULL;
				TempTail = NULL;
			}
			else if (Current == TempHead && TempHead->Next == NULL)
			{
				TempHead = NULL;
				TempTail = NULL;
			}
			else if (Current == TempHead)
			{
				TempHead = TempHead->Next;
				delete Temp;
				Temp = NULL;
			}
			else if (Current->Next == NULL)
			{
				TempQ->Next = NULL;
				delete Current;
				Current = TempQ;
			}
			else
			{
				Temp2 = Current;
				TempQ->Next = Current->Next;
				delete Temp2;
				Temp2 = NULL;
				Current = TempQ->Next;
			}

			Current = TempHead;
		}
		TempQ = Current;

		if (Current!=NULL)
		{
			Current = Current->Next;
		}
		
	}



	if (this->char_HP <= 0)  //判断血量是否为0
	{
		this->which = 3;
	}
}

void IDN::chose_map()
{
	putimage(0, 0, &cmpbk);   //放置背景
	putimage(0, High - 350, &cmp);

	if (cmp_backbutton == 1)   //返回按钮正常
	{
		putimage(Width * 0.81, High * 0.02, &back_zz, NOTSRCERASE);//放置返回键
		putimage(Width * 0.81, High * 0.02, &back, SRCINVERT);
	}
	else if (cmp_backbutton == 0)  //返回按钮按下
	{
		putimage(Width * 0.81, High * 0.03, &backd_zz, NOTSRCERASE);//放置返回键
		putimage(Width * 0.81, High * 0.03, &backd, SRCINVERT);

		mciSendString(_T("close btmmusic"), NULL, 0, NULL);
		mciSendString(_T("open data\\audio\\btm.mp3 alias btmmusic"), NULL, 0, NULL);
		mciSendString(_T("play btmmusic"), NULL, 0, NULL);//播放一次音效

		FlushBatchDraw();
		Sleep(300);

		this->which = 0;
		cmp_backbutton = 1;
	}

	if (cmp_map001_down == 2)  //小地图按钮1高亮（被鼠标经过）
	{
		putimage(Width / 3 - 125, High / 3 - 100, &bk001u);
	}
	else if (cmp_map001_down == 1)//小地图按钮1正常
	{
		putimage(Width / 3 - 125, High / 3 - 100, &bk001);
	}
	else if (cmp_map001_down == 0)//小地图按钮1被按下
	{
		putimage(Width / 3 - 125, High / 3 - 100, &bk001d);

		mciSendString(_T("close gsmmusic"), NULL, 0, NULL);
		mciSendString(_T("open data\\audio\\gamestart.mp3 alias gsmmusic"), NULL, 0, NULL);
		mciSendString(_T("play gsmmusic"), NULL, 0, NULL);//播放一次音效
		
		

		FlushBatchDraw();
		Sleep(300);

		map01_music = 1;
		map02_music = 0;
		map03_music = 0;
		Main_music = 0;
		
		MType = 1;

		cmp_map001_down = 1;
		this->which = 1;
	}

	if (cmp_map002_down == 2) //小地图按钮2高亮（被鼠标经过）
	{
		putimage(Width / 3 + 185, High / 3 - 100, &bk002u);
	}
	else if (cmp_map002_down == 1)//小地图按钮2正常
	{
		putimage(Width / 3 + 185, High / 3 - 100, &bk002);
	}
	else if (cmp_map002_down == 0)//小地图按钮2被按下
	{
		putimage(Width / 3 + 185, High / 3 - 100, &bk002d);

		mciSendString(_T("close gsmmusic"), NULL, 0, NULL);
		mciSendString(_T("open data\\audio\\gamestart.mp3 alias gsmmusic"), NULL, 0, NULL);
		mciSendString(_T("play gsmmusic"), NULL, 0, NULL);//播放一次音效

		FlushBatchDraw();
		Sleep(300);

		map01_music = 0;
		map02_music = 1;
		map03_music = 0;
		Main_music = 0;

		MType = 2;
		cmp_map002_down = 1;
		this->which = 1;
	}

	if (cmp_map003_down == 2) //小地图按钮3高亮（被鼠标经过）
	{
		putimage(Width / 3 + 25, High / 3 + 100, &bk003u);
	}
	else if (cmp_map003_down == 1)//小地图按钮3正常
	{
		putimage(Width / 3 + 25, High / 3 + 100, &bk003);
	}
	else if (cmp_map003_down == 0)//小地图按钮3被按下
	{
		putimage(Width / 3 + 25, High / 3 + 100, &bk003d);

		mciSendString(_T("close gsmmusic"), NULL, 0, NULL);
		mciSendString(_T("open data\\audio\\gamestart.mp3 alias gsmmusic"), NULL, 0, NULL);
		mciSendString(_T("play gsmmusic"), NULL, 0, NULL);//播放一次音效

		FlushBatchDraw();
		Sleep(300);

		map01_music = 0;
		map02_music = 0;
		map03_music = 1;
		Main_music = 0;

		MType = 3;
		cmp_map002_down = 1;
		this->which = 1;
	}


	if (GetAsyncKeyState(VK_ESCAPE)) //也可以通过ESC来返回
	{
		cmp_backbutton = 0;
	}


	MOUSEMSG m;  //创建对象

	while (MouseHit())  //判断鼠标是否有动作
	{
		m = GetMouseMsg();

		if (m.uMsg == WM_MOUSEMOVE)//鼠标移动检测
		{

			if (m.x >= Width / 3 - 125 && m.x <= (Width / 3 - 125 + 150) && m.y >= (High / 3 - 100) && m.y <= (High / 3 - 100 + 150))
			{
				cmp_map001_down = 2;//小地图按钮1高亮（被鼠标经过）
			}
			else
			{
				cmp_map001_down = 1;//按钮2正常
			}


			if (m.x >= Width / 3 + 185 && m.x <= (Width / 3 + 185 + 150) && m.y >= (High / 3 - 100) && m.y <= (High / 3 - 100 + 150))
			{
				cmp_map002_down = 2;//小地图按钮2高亮（被鼠标经过）
			}
			else
			{
				cmp_map002_down = 1;//按钮2正常
			}

			if (m.x >= Width / 3 + 25 && m.x <= (Width / 3 + 25 + 150) && m.y >= (High / 3 + 100) && m.y <= (High / 3 + 100 + 150))
			{
				cmp_map003_down = 2;//小地图按钮3高亮（被鼠标经过）
			}
			else
			{
				cmp_map003_down = 1;//按钮3正常
			}
		}

		if (m.uMsg == WM_LBUTTONDOWN)//按下鼠标左键时
		{
			if (m.x >= Width * 0.8 && m.x <= Width * 0.8 + 89 && m.y >= High * 0.02 && m.y <= High * 0.02 + 46)
			{
				cmp_backbutton = 0;  //返回按钮
			}

			if (m.x >= Width / 3 - 125 && m.x <= (Width / 3 - 125 + 150) && m.y >= (High / 3 - 100) && m.y <= (High / 3 - 100 + 150))
			{
				cmp_map001_down = 0;//小地图按钮1被按下
			}

			if (m.x >= Width / 3 + 185 && m.x <= (Width / 3 + 185 + 150) && m.y >= (High / 3 - 100) && m.y <= (High / 3 - 100 + 150))
			{
				cmp_map002_down = 0;//小地图按钮2被按下
			}

			if (m.x >= Width / 3 + 25 && m.x <= (Width / 3 + 25 + 150) && m.y >= (High / 3 + 100) && m.y <= (High / 3 + 100 + 150))
			{
				cmp_map003_down = 0;//小地图按钮3被按下
			}
		}
	}

}

void IDN::help_player()
{
	putimage(0, 0, &helpbk);

	if (GetAsyncKeyState(VK_ESCAPE)) //也可以通过ESC来返回
	{
		this->which = 0;
	}

	MOUSEMSG m;
	while (MouseHit())  //判断鼠标是否有动作
	{
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN)//按下鼠标左键时
		{
			this->which = 0;
		}
	}
}

void IDN::creat_Num(RetNum*& TempHead, RetNum*& TempTail, double X, double Y)
{
	//函数用于创建数字表的节点
	if (TempHead == NULL)
	{
		TempHead = new RetNum;
		TempHead->num_X = Width * 0.7 - ksc * 100.0;
		TempHead->num_Y = High * 0.5;
		TempHead->drawnumX = X;
		TempHead->drawnumY = Y;
		TempTail = TempHead;
		TempTail->Next = NULL;
	}
	else
	{
		TempTail->Next = new RetNum;
		TempTail = TempTail->Next;
		TempTail->num_X = Width * 0.7 - ksc * 100.0;
		TempTail->num_Y = High * 0.5;
		TempTail->drawnumX = X;
		TempTail->drawnumY = Y;
		TempTail->Next = NULL;
	}
}

void IDN::Print(int N, RetNum*& TempHead, RetNum*& TempTail)
{
	//函数用于绘制数字相应的图片
	if (N != 0)
	{
		int m_N = N % 10;

		if (m_N == 0)
		{
			creat_Num(TempHead, TempTail, 130, 0);
			ksc++;
		}
		else if (m_N == 1)
		{
			creat_Num(TempHead, TempTail, 0, 110);
			ksc++;
		}
		else if (m_N == 2)
		{
			creat_Num(TempHead, TempTail, 130, 110);
			ksc++;
		}
		else if (m_N == 3)
		{
			creat_Num(TempHead, TempTail, 260, 110);
			ksc++;
		}
		else if (m_N == 4)
		{
			creat_Num(TempHead, TempTail, 0, 240);
			ksc++;
		}
		else if (m_N == 5)
		{
			creat_Num(TempHead, TempTail, 130, 240);
			ksc++;
		}
		else if (m_N == 6)
		{
			creat_Num(TempHead, TempTail, 260, 235);
			ksc++;
		}
		else if (m_N == 7)
		{
			creat_Num(TempHead, TempTail, 0, 370);
			ksc++;
		}
		else if (m_N == 8)
		{
			creat_Num(TempHead, TempTail, 130, 370);
			ksc++;
		}
		else if (m_N == 9)
		{
			creat_Num(TempHead, TempTail, 260, 365);
			ksc++;
		}
		Print(N / 10, TempHead, TempTail);  //函数的递归
	}

}

void IDN::result(RetNum*& TempHead, RetNum*& TempTail, Enemy01*& TempHead1, Bullet*& TempHead2, Cloud*& TempHead3, Map*& TempHead4, Boss01& b, BossBlt*& BBHead)
{
	cleardevice();
	putimage(0, 0, &ret);

	if (ifsave==0)
	{
		save_score();//保存分数
		ifsave = 1;
	}
	

	if (isksc == 1)  //保证只会绘制一遍
	{
		Print(KillScore, TempHead, TempTail);
		isksc = 0; //保证只会绘制一遍
	}

	if (KillScore > 0)  //如果不是0的话 开始绘制数字
	{
		RetNum* Current = TempHead;
		while (Current)
		{
			putimage(Current->num_X, Current->num_Y, 128, 128, &num_zz, Current->drawnumX, Current->drawnumY, NOTSRCERASE);
			putimage(Current->num_X, Current->num_Y, 128, 128, &num, Current->drawnumX, Current->drawnumY, SRCINVERT);
			Current = Current->Next;
		}
	}
	else  //如果是0的话直接放0的图片
	{
		putimage(Width * 0.5 - 50, High * 0.5, 128, 128, &num_zz, 130, 0, NOTSRCERASE);
		putimage(Width * 0.5 - 50, High * 0.5, 128, 128, &num, 130, 0, SRCINVERT);
	}


	//下面是相应范围分数对应的 结算界面的 对话框中的不同文字
	if (KillScore <= 7500)
	{
		putimage(0, High - 250, &ret24_zz, NOTSRCERASE);
		putimage(0, High - 250, &ret2401, SRCINVERT);
	}
	else if (KillScore > 7500 && KillScore <= 17000)
	{
		putimage(0, High - 250, &ret24_zz, NOTSRCERASE);
		putimage(0, High - 250, &ret2402, SRCINVERT);
	}
	else if (KillScore > 17000)
	{
		putimage(0, High - 250, &ret24_zz, NOTSRCERASE);
		putimage(0, High - 250, &ret2403, SRCINVERT);
	}


	if (GetAsyncKeyState(VK_ESCAPE)) //也可以通过ESC来返回
	{
		this->which = 0;//回到主菜单

		show_gameover(TempHead1, TempHead2, TempHead3, TempHead4, TempHead, b,BBHead); //初始化游戏数据
	}


	//用于  成绩结算界面  的鼠标行为检测
	MOUSEMSG m;  //创建对象
	while (MouseHit())  //判断鼠标是否有动作
	{
		m = GetMouseMsg();

		if (m.uMsg == WM_MBUTTONDOWN)//按下鼠标中键
		{
			this->which = 0;//回到主菜单

			show_gameover(TempHead1, TempHead2, TempHead3, TempHead4, TempHead, b,BBHead); //初始化游戏数据
		}
	}

	mciSendString(_T("close bkmusic"), NULL, 0, NULL);
	mciSendString(_T("close mp1music"), NULL, 0, NULL);
	mciSendString(_T("close mp2music"), NULL, 0, NULL);
	mciSendString(_T("close mp3music"), NULL, 0, NULL);



	if (result_mp3 == 0)
	{
		mciSendString(_T("open data\\audio\\bgm.mp3 alias bkmusic"), NULL, 0, NULL);
		mciSendString(_T("play bkmusic repeat"), NULL, 0, NULL);
	}
	else if (result_mp3 == 1)
	{
		mciSendString(_T("close retmusic"), NULL, 0, NULL);
		mciSendString(_T("open data\\audio\\result.mp3 alias retmusic"), NULL, 0, NULL);
		mciSendString(_T("play retmusic"), NULL, 0, NULL);//播放一次音效
		FlushBatchDraw();
		Sleep(5600);

		result_mp3 = 0;
	}

}

void IDN::updateWithoutInput(Cloud*& TempHead, Cloud*& TempTail)
{
	//函数用于敌人属性的更新等
	if (KillNum != 0 && KillNum / 10 == i)//判断杀敌数是否到达10的倍数  每到达一次10的倍数为1轮
	{
		draw_cloud(TempHead, TempTail);

		if (i % 12 == 0)  //每12轮敌人HP增加30%
		{
			e1_HP *= 1.3;
		}

		if (RANGE > 200 && i > 0) //每轮缩小出敌间隔
		{
			RANGE -= 50;
		}
		else if (RANGE <= 200 && RANGE > 30 && i > 0) //每轮缩小出敌间隔
		{
			RANGE -= 10;
		}

		if (e1speed <= 4.8)  //改变敌人速度
		{
			e1speed += 0.3;
		}
		else
		{
			e1speed = 4.8;  //敌人速度上限
		}
		i++;  //进入下一轮
	}

	if (score <= 0) //判断弹药情况
	{
		outtextxy(Width * 0.44, High * 0.515, "鼠标右键装弹");
		outtextxy(Width * 0.45, High * 0.47, "弹药用光辣");
	}
}

void IDN::show_gameover(Enemy01*& TempHead, Bullet*& TempHead2, Cloud*& TempHead3, Map*& TempHead4, RetNum*& TempHead5, Boss01& b, BossBlt*& BBHead)
{
	//该函数用于初始化游戏数据
	this->char_HP = 500;    //初始化体力
	FullHP = this->char_HP;  //初始化体力

	FullScore = 30;      //初始化满子弹数目
	score = FullScore;   //初始化当前子弹数目
	ArmScore = 10;       //初始化装填子弹数目
	btype = 1;           //初始化子弹类型
	bret = 1;            //初始化用于判断子弹形态是否变化的数据 1为未变化

	this->bullet_Att = 100.0;  //初始化攻击力

	KillScore = 0;  //初始化得分
	KillNum = 0;    //初始化击落敌机数目

	e1speed = 2;   //初始化敌人01的速度
	e1_HP = 200.0; //初始化敌人01的HP

	i = 1;         //初始化轮数

	this->char_X = Width / 2.0 + 20.0;  //初始化坐标
	this->char_Y = 700.0;

	ksc = 0;        //初始化数字个数
	isksc = 1;      //初始化  是否绘制过数字  的变量

	b.boss_HP = BOSSHP;  //初始化Boss血量
	isBoss = 0;        //初始化 BOSS是否出现 变量
	ifBossSe = 1;      //初始化 Boss是否存活 变量
	b.boss_X = Width / 2.0 - 125.0;
	b.boss_Y = -300.0;
	b.boss_AttType = 0;   //初始化Boss攻击状态
	b.boss_attspeed = 3;   //初始化Boss攻击频率
	ifBoss2 = 0;           //初始化Boss是否第二次出场
	b.boss_Att = 30;       //初始化Boss攻击力

	b.B_Lsec = 0;             //初始化爆炸前置时间
	b.B_Asec = 0;             //初始化爆炸后置时间
	b.ifB_Lsec = 0;           //初始化爆炸判断前置时间是否已经记录
	b.ifB_Asec = 0;			  //初始化爆炸判断后置时间是否已经记录
	b.ifblast = 0;            //初始化爆炸判断是否应该爆炸  0为即将爆炸
	b.blast_i = 0;            //初始化爆炸绘制行数
	b.blast_j = 0;            //初始化爆炸绘制列数

	boss_mp3 = 1;      //初始化 Boss出场音效

	Main_music = 1;       //初始化主界面音乐
	map01_music = 0;      //初始化地图1音乐
	map02_music = 0;      //初始化地图2音乐
	map03_music = 0;      //初始化地图3音乐

	Lsec = 0;               //初始化前置时间
	Asec = 0;               //初始化后置时间
	ifLsec = 0;             //0表示还未获取时间
	ifAsec = 0;

	ifsave = 0;               //为下一次保存做准备

	//6个链表的头指针全部指向空   即清空所有链表
	TempHead = NULL;             //初始化敌人01表
	TempHead2 = NULL;            //初始化子弹表
	TempHead3 = NULL;            //初始化道具表
	TempHead4 = NULL;            //初始化地图表
	TempHead5 = NULL;            //初始化数字表
	BBHead = NULL;               //初始化BOSS子弹表
}

void IDN::draw_map(Map*& MapHead, Map*& MapTail)
{
	//画连续的地图
	if (MapHead == NULL)
	{
		MapHead = new Map;
		MapTail = MapHead;
		MapHead->MapType = MType;
		if (MapHead->MapType == 2)   //判断地图种类
		{
			MapHead->map_speed = 1.5;
		}
		else if (MapHead->MapType == 3)
		{
			MapHead->map_speed = 0.8;
		}
		MapTail->Next = NULL;
	}
	else
	{
		if (MapTail->map_Y > 0)  //绘制第二张或之后地图的条件
		{
			MapTail->Next = new Map;
			MapTail->Next->map_Y = MapTail->map_Y - High;
			MapTail = MapTail->Next;
			MapTail->MapType = MType;

			if (MapTail->MapType == 2) //判断地图种类
			{
				MapTail->map_speed = 1.5;
			}
			else if (MapTail->MapType == 3)
			{
				MapTail->map_speed = 0.8;
			}
			MapTail->Next = NULL;
		}
	}

	//绘制背景
	Map* Current2 = MapHead;
	Map* TempQ2 = NULL;
	while (Current2)
	{
		if (Current2->MapType == 1)//第一类背景
		{
			putimage(0, Current2->map_Y, &bk);
		}
		else if (Current2->MapType == 2)//第二类背景
		{
			putimage(0, Current2->map_Y, &bk2);
		}
		else if (Current2->MapType == 3)//第三类背景
		{
			putimage(0, Current2->map_Y, &bk3);
		}

		Current2->map_Y += Current2->map_speed;

		//对越界的地图做删除处理  防止后期可能产生的卡顿
		if (Current2->map_Y > High + 100.0)
		{

			if (Current2 == MapHead && Current2 == MapTail)
			{
				MapHead = NULL;
				MapTail = NULL;
			}
			else if (Current2 == MapHead && MapHead->Next == NULL)
			{
				MapHead = NULL;
				MapTail = NULL;
			}
			else if (Current2 == MapHead)
			{
				Map* Temp = MapHead;
				MapHead = MapHead->Next;
				delete Temp;
				Temp = NULL;
			}
			else if (Current2->Next == NULL)
			{
				TempQ2->Next = NULL;
				delete Current2;
				Current2 = TempQ2;
			}
			else
			{
				Map* Temp = Current2;
				TempQ2->Next = Current2->Next;
				delete Temp;
				Temp = NULL;
				Current2 = TempQ2->Next;
			}

			Current2= MapHead;
		}
		TempQ2 = Current2;

		if (Current2 != NULL)
		{
			Current2 = Current2->Next;
		}
		
	}
}

void IDN::add_bullet(double X, double Y, Bullet*& TempHead, Bullet*& TempTail)
{
	if (score > 0)  //弹药大于0才能发射子弹
	{
		if (TempHead != NULL)
		{
			TempTail->Next = new Bullet;
			TempTail = TempTail->Next;
			TempTail->bullet_X = X;
			TempTail->bullet_Y = Y;
			TempTail->bullet_type = btype;
			TempTail->Next = NULL;
		}
		else if (TempHead == NULL)
		{
			TempHead = new Bullet;
			TempHead->bullet_X = X;
			TempHead->bullet_Y = Y;
			TempHead->bullet_type = btype;
			TempTail = TempHead;
			TempTail->Next = NULL;
		}
		score--;//发射后弹药数量减少
	}
}

void IDN::add_Boss_blt(BossBlt*& BBHead, BossBlt*& BBTail,Boss01&b)
{
	int ranGe = rand() % 300 + 1;
	
	if (BBHead != NULL)
	{
		if (BBTail->bossblt_Y + 35 >= ranGe)
		{
			BBTail->Next = new BossBlt;
			BBTail = BBTail->Next;
			BBTail->bossblt_X = 1.0 * (rand() % Width  + 1);
			BBTail->bossblt_Y = -30;
			BBTail->bossblt_type = MType;
			BBTail->Next = NULL;
		}
	}
	else if (BBHead == NULL)
	{
		BBHead = new BossBlt;
		BBHead->bossblt_X = 1.0 * (rand() % Width + 1);
		BBHead->bossblt_Y = -30;
		BBHead->bossblt_type = MType;
		BBTail = BBHead;
		BBTail->Next = NULL;
	}

	BossBlt* Current = BBHead; //被子弹击中
	while (Current)
	{
		double X = this->char_X + 60;
		double Y = this->char_Y + 60;
		
		double distance = (Current->bossblt_X + 15 - X) * (Current->bossblt_X + 15 - X) + (Current->bossblt_Y + 15 - Y) * (Current->bossblt_Y + 15 - Y);
		if (distance <= 900)
		{
			this->char_HP -= 50;
			Current->isext = false;

			mciSendString(_T("close bbbmusic"), NULL, 0, NULL);
			mciSendString(_T("open data\\audio\\BB_bomb.mp3 alias bbbmusic"), NULL, 0, NULL);
			mciSendString(_T("play bbbmusic"), NULL, 0, NULL);//播放一次音效
		}

		Current = Current->Next;
	}

	//绘制BOSS子弹
	BossBlt* Current2 = BBHead;
	BossBlt* TempQ2 = NULL;
	while (Current2)
	{
		if (Current2->bossblt_type == 2)
		{
			putimage(Current2->bossblt_X, Current2->bossblt_Y, &BB01_zz, NOTSRCERASE);
			putimage(Current2->bossblt_X, Current2->bossblt_Y, &BB01, SRCINVERT);
		}
		else if (Current2->bossblt_type == 1)
		{
			putimage(Current2->bossblt_X, Current2->bossblt_Y, &BB02_zz, NOTSRCERASE);
			putimage(Current2->bossblt_X, Current2->bossblt_Y, &BB02, SRCINVERT);
		}
		else if (Current2->bossblt_type == 3)
		{
			putimage(Current2->bossblt_X, Current2->bossblt_Y, &BB03_zz, NOTSRCERASE);
			putimage(Current2->bossblt_X, Current2->bossblt_Y, &BB03, SRCINVERT);
		}
		
		Current2->bossblt_Y += Current2->bossblt_speed;//让BOSS子弹按设定的速度移动


	//对越界的BOSS子弹做删除处理
		if (Current2->bossblt_Y > High + 100.0 || Current2->isext == 0)
		{
			if (Current2 == BBHead && Current2 == BBTail)
			{
				BBHead = NULL;
				BBTail = NULL;
			}
			else if (Current2 == BBHead && BBHead->Next == NULL)
			{
				BBHead = NULL;
				BBTail = NULL;
			}
			else if (Current2 == BBHead)
			{
				BossBlt* Temp = BBHead;
				BBHead = BBHead->Next;
				delete Temp;
				Temp = NULL;
			}
			else if (Current2->Next == NULL)
			{
				TempQ2->Next = NULL;
				delete Current2;
				Current2 = TempQ2;
			}
			else
			{
				BossBlt* Temp = Current2;
				TempQ2->Next = Current2->Next;
				delete Temp;
				Temp = NULL;
				Current2 = TempQ2->Next;
			}
			Current2 = BBHead;

		}
		TempQ2 = Current2;

		if (Current2 != NULL)
		{
			Current2 = Current2->Next;
		}
		
	}
}

void IDN::mouse_move(Enemy01*& TempHead0, Bullet*& TempHead, Bullet*& TempTail, Cloud*& TempHead3, Map*& TempHead4, RetNum*& TempHead5)
{
	if (game_backbutton == 1)
	{
		putimage(Width * 0.81, High * 0.02, &back_zz, NOTSRCERASE);//放置返回键
		putimage(Width * 0.81, High * 0.02, &back, SRCINVERT);
	}
	else if (game_backbutton == 0)
	{
		putimage(Width * 0.81, High * 0.03, &backd_zz, NOTSRCERASE);//放置返回键
		putimage(Width * 0.81, High * 0.03, &backd, SRCINVERT);

		
		mciSendString(_T("close btmmusic"), NULL, 0, NULL);
		mciSendString(_T("open data\\audio\\btm.mp3 alias btmmusic"), NULL, 0, NULL);
		mciSendString(_T("play btmmusic"), NULL, 0, NULL);//播放一次音效

		FlushBatchDraw();
		Sleep(300);
		
		this->char_HP -= 9999999;
		game_backbutton = 1;
	}


	if (GetAsyncKeyState(VK_ESCAPE)) //也可以通过ESC来返回
	{
		game_backbutton = 0;
	}



	//这个函数会在游戏时检测鼠标动作情况
	MOUSEMSG m;  //创建对象

	while (MouseHit())  //判断鼠标是否有动作
	{
		m = GetMouseMsg();

		if (m.uMsg == WM_MOUSEMOVE)//鼠标移动检测
		{
			this->char_X = m.x - 60.0;
			this->char_Y = m.y - 60.0;
		}

		if (m.uMsg == WM_LBUTTONDOWN)//按下鼠标左键时
		{
			if (m.x >= Width * 0.8 && m.x <= Width * 0.8 + 89 && m.y >= High * 0.02 && m.y <= High * 0.02 + 46)
			{	//先判断是不是在按返回键
				game_backbutton = 0;
			}
			else
			{
				add_bullet(m.x, m.y, TempHead, TempTail);//发射子弹
			}
		}

		if (m.uMsg == WM_RBUTTONDOWN)//按下鼠标右键时增加子弹
		{
			temp_score = score + ArmScore;//先判定直接加上后会不会越界

			if (score < FullScore)
			{
				if (temp_score >= FullScore)
				{
					score = FullScore;
				}
				else if (temp_score <= FullScore)
				{
					score += ArmScore;
				}
			}
		}
	}
}

void IDN::draw_char()
{
	//画主角 不用多说了8
	//下方注释掉的是用Easyx图形库+纯代码画出来的 舍不得删
	//有兴趣可以试一下
	//但是后来就没有对这个飞机做坐标和子弹位置的兼容了(
	putimage(this->char_X, this->char_Y, &Char_zz, NOTSRCERASE);
	putimage(this->char_X, this->char_Y, &Char, SRCINVERT);

	//fillrectangle(this->char_X - 18, this->char_Y - 50, this->char_X + 18, this->char_Y + 50);//身体
	//fillrectangle(this->char_X - 10, this->char_Y + 50, this->char_X + 10, this->char_Y + 75);//下部
	//fillrectangle(this->char_X - 17, this->char_Y + 75, this->char_X + 17, this->char_Y + 85);//底部
	//fillcircle(this->char_X, this->char_Y - 50, 18);
	//POINT pts[] = { {this->char_X - 20, this->char_Y + 45}, {this->char_X - 20, this->char_Y - 45}, {this->char_X - 80, this->char_Y + 50} };//左机翼
	//POINT pts2[] = { {this->char_X + 20, this->char_Y + 45}, {this->char_X + 20, this->char_Y - 45}, {this->char_X + 80, this->char_Y + 50} };//右机翼
	//POINT pts3[] = { {this->char_X - 18, this->char_Y - 57}, {this->char_X + 18, this->char_Y - 57}, {this->char_X , this->char_Y - 95} };//机头
	//POINT pts4[] = { {this->char_X - 20, this->char_Y + 75}, {this->char_X - 20, this->char_Y + 85}, {this->char_X - 30, this->char_Y + 85} };//左机尾
	//POINT pts5[] = { {this->char_X + 20, this->char_Y + 75}, {this->char_X + 20, this->char_Y + 85}, {this->char_X + 30, this->char_Y + 85} };//左机尾

	//fillpolygon(pts, 3);
	//fillpolygon(pts2, 3);
	//fillpolygon(pts3, 3);
	//fillpolygon(pts4, 3);
	//fillpolygon(pts5, 3);

	//setfillcolor(YELLOW);
	//setlinecolor(YELLOW);
}

void IDN::draw_cloud(Cloud*& TempHead, Cloud*& TempTail)
{
	//绘制道具
	if (TempHead == NULL)//头道具
	{
		TempHead = new Cloud;
		TempHead->cloud_X = 1.0 * (rand() % (Width - 100 - 0 + 1) + 0);
		TempHead->cloud_Y = -180;

		TempHead->NumType = rand() % 90 + 1;

		if (TempHead->NumType > 60)   //更改道具类型的地方   下面也要改
		{
			TempHead->type = 1;
		}
		else if (TempHead->NumType <= 30)
		{
			TempHead->type = 2;
		}
		else if (TempHead->NumType > 30 && TempHead->NumType <= 60)
		{
			TempHead->type = 3;
		}

		TempTail = TempHead;
		TempTail->Next = NULL;
	}
	else if (TempHead != NULL)//后续道具
	{
		if (TempTail->cloud_Y >= range)
		{
			TempTail->Next = new Cloud;
			TempTail = TempTail->Next;
			TempTail->cloud_X = 1.0 * (rand() % (Width - 100 - 0 + 1) + 0);
			TempTail->cloud_Y = -180;
			TempTail->NumType = rand() % 90 + 1;
			TempTail->Next = NULL;

			if (TempTail->NumType > 60)   //更改道具类型的地方   上面也要改
			{
				TempTail->type = 1;
			}
			else if (TempTail->NumType <= 30)
			{
				TempTail->type = 2;
			}
			else if (TempTail->NumType > 30 && TempTail->NumType <= 60)
			{
				TempTail->type = 3;
			}
		}
	}
}

void IDN::creat_enemy01(Enemy01*& TempHead, Enemy01*& TempTail)
{
	//绘制敌人
	if (KillScore <= SHOW_BOSS01 || ifBossSe==0)
	{
		int range;
		range = rand() % RANGE + 1;

		if (TempHead == NULL)
		{
			TempHead = new Enemy01;
			TempHead->enemy_X = 1.0 * (rand() % (Width - 100 - 0 + 1) + 0);
			TempHead->enemy_Y = -155;

			TempHead->EnemyType = rand() % 25 + 1;

			if (TempHead->EnemyType >= 14)   //更改敌人属性的地方   下面也要改
			{
				TempHead->Type = 1;
				TempHead->enemy_HP = e1_HP;
				TempHead->enemy_speed = e1speed;
			}
			else if (TempHead->EnemyType <= 7)
			{
				TempHead->Type = 2;
				TempHead->enemy_HP = e1_HP * 0.5;
				TempHead->enemy_speed = e1speed * 1.3;
			}
			else
			{
				TempHead->Type = 3;
				TempHead->enemy_HP = e1_HP * 2;
				TempHead->enemy_speed = e1speed * 0.5;
			}

			TempTail = TempHead;
			TempTail->Next = NULL;
		}
		else if (TempHead != NULL)
		{
			if (TempTail->enemy_Y + 35 >= range)
			{
				TempTail->Next = new Enemy01;
				TempTail = TempTail->Next;
				TempTail->enemy_X = 1.0 * (rand() % (Width - 100 - 0 + 1) + 0);
				TempTail->enemy_Y = -155;
				TempTail->EnemyType = rand() % 25 + 1;
				TempTail->Next = NULL;

				if (TempTail->EnemyType >= 14)    //更改敌人属性的地方   上面也要改
				{
					TempTail->Type = 1;
					TempTail->enemy_HP = e1_HP;
					TempTail->enemy_speed = e1speed;
				}
				else if (TempTail->EnemyType <= 7)
				{
					TempTail->Type = 2;
					TempTail->enemy_HP = e1_HP * 0.5;
					TempTail->enemy_speed = e1speed * 1.3;
				}
				else
				{
					TempTail->Type = 3;
					TempTail->enemy_HP = e1_HP * 2;
					TempTail->enemy_speed = e1speed * 0.5;
				}
			}
		}
	}

	//绘制敌人01
	Enemy01* Current2 = TempHead;
	Enemy01* TempQ2 = NULL;
	Enemy01* Temp;
	Enemy01* Temp2;
	while (Current2)
	{
		if (Current2->enemy_HP > 0  && Current2->stoexist == 1)  //应该存在的敌人才能被绘制
		{
			if (Current2->Type == 1)
			{
				putimage(Current2->enemy_X, Current2->enemy_Y, &enemy01_zz, NOTSRCERASE);
				putimage(Current2->enemy_X, Current2->enemy_Y, &enemy01, SRCINVERT);
			}
			else if (Current2->Type == 2)
			{
				putimage(Current2->enemy_X, Current2->enemy_Y, &enemy0102_zz, NOTSRCERASE);
				putimage(Current2->enemy_X, Current2->enemy_Y, &enemy0102, SRCINVERT);
			}
			else if (Current2->Type == 3)
			{
				putimage(Current2->enemy_X, Current2->enemy_Y, &enemy0103_zz, NOTSRCERASE);
				putimage(Current2->enemy_X, Current2->enemy_Y, &enemy0103, SRCINVERT);
			}

			Current2->enemy_Y += Current2->enemy_speed;//让敌人01按设定的速度移动
		}


		if (Current2->enemy_Y > High + 70.0)
		{
			this->char_HP -= 225;    //敌人01的越界伤害
			Current2->stoexist = 0;  //越界后敌人就不应该存在
		}

		//对越界的敌人01做删除处理     必要条件是  不应该存在
		if ((Current2->enemy_Y > High + 70.0 || Current2->enemy_HP <= 0) && Current2->stoexist == 0)
		{
			if (Current2 == TempHead && TempHead->Next == NULL)
			{//只有一个节点的情况
				TempHead = nullptr;
				TempTail = NULL;
			}
			else if (Current2 == TempHead && TempHead->Next != NULL)
			{
				//什么也不做
				//Temp = TempHead;
				//TempHead = TempHead->Next;   //如果执行这行代码的话就会导致闪屏
				//delete Temp;
				//Temp = NULL;
			}
			else if (Current2->Next == NULL)
			{
				TempQ2->Next = NULL;
				delete Current2;
				Current2 = TempQ2;
			}
			else
			{
				//节点在中间的情况
				Temp2 = Current2;
				TempQ2->Next = Current2->Next;
				delete Temp2;
				Temp2 = NULL;
				Current2 = TempQ2->Next;
			}
			//}

			Current2 = TempHead;  //这会导致闪屏  但是不这么写的话会崩溃
		}

		if (Current2 != NULL)
		{
			TempQ2 = Current2;
			Current2 = Current2->Next;
		}

	}
}

void IDN::attack_enemy01(Bullet*& TempHead, Enemy01*& TempHead2, Boss01& b)
{
	Bullet* Currentb = TempHead;
	Enemy01* Currente = TempHead2;

	//子弹碰撞敌人01判定
	while (Currentb)
	{
		while (Currente)
		{
			if (Currente->enemy_HP > 0 && Currentb->bullet_X > Currente->enemy_X - 5 && Currentb->bullet_X < Currente->enemy_X + 155 && Currentb->bullet_Y> Currente->enemy_Y - 5 && Currentb->bullet_Y < Currente->enemy_Y + 155)
			{
				Currente->enemy_HP -= this->bullet_Att;
				Currentb->isext = false;

				if (Currente->enemy_HP <= 0)
				{
					Currente->ifblast = 0;  //准备播放爆炸动画

					mciSendString(_T("close btmusic"), NULL, 0, NULL);
					mciSendString(_T("open data\\audio\\bomb0.mp3 alias btmusic"), NULL, 0, NULL);
					mciSendString(_T("play btmusic"), NULL, 0, NULL);//播放一次爆炸音效

					KillNum++;//击落敌机数增加1

					if (Currente->Type == 1)       //击落敌人01一类型的得分情况
					{
						KillScore += 100;
					}
					else if (Currente->Type == 2)  //击落敌人01二类型的得分情况
					{
						KillScore += 75;
					}
					else if (Currente->Type == 3)//击落敌人01三类型的得分情况
					{
						KillScore += 125;
					}

				}
				
			}
			Currente = Currente->Next;
		}
		Currentb = Currentb->Next;
		Currente = TempHead2;
	}


	Currentb = TempHead;

	while (Currentb) //子弹攻击boss01的判定
	{
		if (b.boss_HP>0&& b.boss_Y >= High / 5 && Currentb->bullet_X >= b.boss_X && Currentb->bullet_X <= b.boss_X + 250 && Currentb->bullet_Y >= b.boss_Y && Currentb->bullet_Y <= b.boss_Y + 235)
		{
			b.boss_HP -= this->bullet_Att;

			if (b.boss_HP <= 0)
			{
				mciSendString(_T("close bsdmusic"), NULL, 0, NULL);
				mciSendString(_T("open data\\audio\\boss_defeated.mp3 alias bsdmusic"), NULL, 0, NULL);
				mciSendString(_T("play bsdmusic"), NULL, 0, NULL);//播放一次爆炸音效

				KillNum++;//击落敌机数增加1
				KillScore += 5000;
			}
			Currentb->isext = false;
		}
		Currentb = Currentb->Next;
	}

	Currentb = TempHead;

	if (b.boss_HP > 0 && b.boss_Y >= High / 5 && this->char_X >= b.boss_X - 110 && this->char_X <= b.boss_X + 230 && this->char_Y >= b.boss_Y + 5 && this->char_Y <= b.boss_Y + 220)
	{//与BOSS01碰撞的判定
		this->char_HP -= b.boss_Att;
		mciSendString(_T("close bt1music"), NULL, 0, NULL);
		mciSendString(_T("open data\\audio\\bomb.mp3 alias bt1music"), NULL, 0, NULL);
		mciSendString(_T("play bt1music"), NULL, 0, NULL);//播放一次爆炸音效
	}

	Currente = TempHead2;
	while (Currente)
	{
		if (Currente->enemy_HP > 0 && this->char_X > Currente->enemy_X - 20 && this->char_X < Currente->enemy_X + 75 && this->char_Y> Currente->enemy_Y - 65 && this->char_Y < Currente->enemy_Y + 100)
		{
			if (Currente->Type == 1)
			{
				KillScore += 50;
                this->char_HP -= 100;  //和敌人01一类型碰撞伤害
			}
			else if (Currente->Type == 2)
			{
			KillScore += 60;
			this->char_HP -= 165;  //和敌人01二类型碰撞伤害
			}
			else if (Currente->Type == 3)
			{
			KillScore += 70;
			this->char_HP -= 135;  //和敌人01三类型碰撞伤害
			}

			Currente->ifblast = 0;  //准备播放爆炸动画
			Currente->enemy_HP -=999999;
			KillNum++;//碰撞后敌机直接死亡 击落敌机数+1

			mciSendString(_T("close bt1music"), NULL, 0, NULL);
			mciSendString(_T("open data\\audio\\bomb.mp3 alias bt1music"), NULL, 0, NULL);
			mciSendString(_T("play bt1music"), NULL, 0, NULL);//播放一次爆炸音效
		}
		Currente = Currente->Next;
	}

	Currente = NULL;
	Currentb = NULL;
}

void IDN::blast_Boss(Boss01& b)
{
	double X = b.boss_X;
	double Y = b.boss_Y;

	if (b.ifblast == 0 && b.boss_HP<=0)
	{
		if (b.ifB_Lsec == 0)
		{
			b.B_Lsec= ti.wMilliseconds;
			b.ifB_Lsec = 1;
		}

		if (b.ifB_Asec == 0)
		{
			b.B_Asec= ti.wMilliseconds;
			putimage(X, Y, 256, 256, &Bblast_zz, b.blast_j * 255, b.blast_i * 255, NOTSRCERASE);
			putimage(X, Y, 256, 256, &Bblast, b.blast_j * 255, b.blast_i * 255, SRCINVERT);

			if ((b.B_Asec - b.B_Lsec >= 10 && b.B_Asec > b.B_Lsec) || (b.B_Asec - b.B_Lsec + 1000 >= 10 && b.B_Asec < b.B_Lsec))
			{

				b.ifB_Lsec = 0;
				b.ifB_Asec = 0;  //便于记录下一轮的时间

				b.blast_j++;     //列数++  播放下一张图

				if (b.blast_j == 4)  //一列播放完成  列数归零 行数++
				{
					b.blast_j = 0;
					b.blast_i++;
				}

				if (b.blast_i == 4)  //所有行都播放完成时
				{
					b.ifblast = 1;  //停止播放动画

					b.B_Lsec = 0;             //重置前置时间
					b.B_Asec = 0;             //重置后置时间
					b.ifB_Lsec = 0;           //重置判断前置时间是否已经记录
					b.ifB_Asec = 0;			  //重置判断后置时间是否已经记录
					b.blast_i = 0;            //重置绘制行数
					b.blast_j = 0;            //重置绘制列数
				}
			}
		}
	}
}

void IDN::blast_enemy(Enemy01*& Temp)
{
	Enemy01* Current = Temp;//记录头节点位置

	while (Current)
	{
		double X = Current->enemy_X;
		double Y = Current->enemy_Y;

		if (Current->ifblast == 0)
		{
			if (Current->ifB_Lsec == 0)  //获取起始毫秒数
			{
				Current->B_Lsec = ti.wMilliseconds;
				Current->ifB_Lsec = 1;
			}

			if (Current->ifB_Asec == 0)
			{
				Current->B_Asec = ti.wMilliseconds; //获取终止秒数
				putimage(X, Y, 128, 128, &blast_zz, Current->blast_j * 127, Current->blast_i * 127, NOTSRCERASE);
				putimage(X, Y, 128, 128, &blast, Current->blast_j * 127, Current->blast_i * 127, SRCINVERT);
				if ((Current->B_Asec - Current->B_Lsec >= 3 && Current->B_Asec > Current->B_Lsec) || (Current->B_Asec - Current->B_Lsec + 1000 >= 3 && Current->B_Asec < Current->B_Lsec))
				{

					Current->ifB_Lsec = 0;
					Current->ifB_Asec = 0;  //便于记录下一轮的时间

					Current->blast_j++;     //列数++  播放下一张图

					if (Current->blast_j == 4)  //一列播放完成  列数归零 行数++
					{
						Current->blast_j = 0;
						Current->blast_i++;
					}

					if (Current->blast_i == 4)  //所有行都播放完成时
					{
						Current->ifblast = 1;  //停止播放动画
						Current->stoexist = 0;  //敌人状态为【不应该存在】 随即被删除
					}
				}
			}
		}
		Current = Current->Next;
	}
	
}

void IDN::eat_item01(Cloud*& TempHead, Cloud*& TempTail)
{
	//函数用于设置各种道具的效果
	Cloud* Current = TempHead;

	while (Current)
	{
		double iX = Current->cloud_X + 40;
		double iY = Current->cloud_Y + 40;
		double distance = (this->char_X + 50 - iX) * (this->char_X + 50 - iX) + (this->char_Y + 50 - iY) * (this->char_Y + 50 - iY);

		if (distance <= 3600)
		{
			Current->isext = false;
			if (Current->type == 1)  //判断道具类型1
			{

				mciSendString(_T("close lfmusic"), NULL, 0, NULL);
				mciSendString(_T("open data\\audio\\life.mp3 alias lfmusic"), NULL, 0, NULL);
				mciSendString(_T("play lfmusic"), NULL, 0, NULL);//播放一次音效

				if (this->char_HP + FullHP * 0.25 <= FullHP)//回血判断
				{
					this->char_HP += FullHP * 0.25;  //回复4分之1的血量
				}
				else
				{
					this->char_HP = FullHP;
				}
			}
			else if (Current->type == 2)  //判断道具类型2
			{
				FullScore += 5;  //增加弹药上限
				ArmScore += 1;   //增加弹药回复力
				this->bullet_Att += 25;  //增加攻击力
				if (this->bullet_Att >= 200 && bret == 1) //当攻击力达到200后子弹形态发生变化
				{
					btype = 2;  //形态设置为2
					bret = 0;   //是否变化设置为“已变化”(即0，1为未变化)

					mciSendString(_T("close apmusic"), NULL, 0, NULL);
					mciSendString(_T("open data\\audio\\armup.mp3 alias apmusic"), NULL, 0, NULL);
					mciSendString(_T("play apmusic"), NULL, 0, NULL);//播放一次音效
				}
				else
				{
					mciSendString(_T("close ammusic"), NULL, 0, NULL);
					mciSendString(_T("open data\\audio\\arm.mp3 alias ammusic"), NULL, 0, NULL);
					mciSendString(_T("play ammusic"), NULL, 0, NULL);//播放一次音效

				}
				
			}
			else if (Current->type == 3)  //判断道具类型3
			{
				this->char_HP += 65;  //提升血量上限
				FullHP += 65;         //补充相应增加的血量
				score = FullScore;    //并且补满弹药

				mciSendString(_T("close lpmusic"), NULL, 0, NULL);
				mciSendString(_T("open data\\audio\\levelup.mp3 alias lpmusic"), NULL, 0, NULL);
				mciSendString(_T("play lpmusic"), NULL, 0, NULL);//播放一次音效
			}
		}
		Current = Current->Next;
	}
}

void IDN::boss_01(Boss01& b, BossBlt*& BBHead, BossBlt*& BBTail)
{
	if (KillScore > SHOW_BOSS01)
	{
		if (KillScore > SHOW_BOSS01*4 && ifBoss2==0) //让Boss第二次出现的判定条件
		{
			b.boss_HP = BOSSHP * 5.0;  //第二次出现100000血量
			b.boss_attspeed--;         //攻击频率加快
			b.boss_Att = 50;           //攻击伤害增加
			ifBoss2 = 1;
			ifBossSe = 1;

			b.ifblast = 0;             //准备播放动画
		}

		if (b.boss_HP > 0)
		{
			add_Boss_blt(BBHead, BBTail,b);

			if (isBoss == 0)
			{
				b.boss_X = Width / 2.0 - 125.0;
				b.boss_Y = -300.0;

				isBoss = 1;
			}
			
			if (b.boss_AttType == 0)//绘制BOSS的图片
			{
				putimage(b.boss_X, b.boss_Y, &boss01_zz, NOTSRCERASE);
				putimage(b.boss_X, b.boss_Y, &boss01, SRCINVERT);
			}
			else if (b.boss_AttType == 1 || b.boss_AttType == 10)
			{
				putimage(b.boss_X, b.boss_Y, &boss01_att01_zz, NOTSRCERASE);
				putimage(b.boss_X, b.boss_Y, &boss01_att01, SRCINVERT);
			}

			if (b.boss_Y <= High / 5)  //BOSS会先移动到指定位置
			{
				
				b.boss_Y += b.boss_speed;
			}


			if (b.boss_Y > High / 5)   //BOSS移动到指定位置之后
			{

				if (ifLsec == 0) //获取起始时间
				{
					Lsec = ti.wSecond;
					ifLsec = 1;
				}

				if (ifAsec == 0)
				{
					Asec = ti.wSecond;  //获取当前时间

					if (Asec > Lsec)
					{
						if (Asec - Lsec == b.boss_attspeed)
						{
							ifAsec = 1;
							b.boss_AttType = 1;  //BOSS行为  下面也要改
						}
					}
					else
					{
						if (Asec + 60 - Lsec == b.boss_attspeed)
						{
							ifAsec = 1;
							b.boss_AttType = 1;  //BOSS行为  上面也要改
						}
					}
				}

				if (boss_mp3 == 1)   //播放一次BOSS出现音效
				{
					mciSendString(_T("close bsmusic"), NULL, 0, NULL);
					mciSendString(_T("open data\\audio\\boss.mp3 alias bsmusic"), NULL, 0, NULL);
					mciSendString(_T("play bsmusic"), NULL, 0, NULL);//播放一次音效
					boss_mp3 = 0;
				}


				if (b.boss_AttType == 0) //BOSS左右移动
				{
					b.boss_X -= b.boss_Xspeed;

					if (b.boss_X <= 0)
					{
						b.boss_Xspeed = -b.boss_Xspeed;
					}
					if (b.boss_X >= Width -250)
					{
						b.boss_Xspeed = -b.boss_Xspeed;
					}

				}

				if (b.boss_AttType == 1)  //BOss攻击方式1：冲撞
				{
					if (b.boss_Y < High * 0.7)
					{
						b.boss_Y += 15.0;
						if (b.boss_Y >= High * 0.7)
						{
							b.boss_AttType = 10;
						}
					}
				}
				else if (b.boss_AttType == 10)  //冲撞结束 倒车
				{
					b.boss_Y -= 3;
					if (b.boss_Y <= High / 5)
					{
						b.boss_AttType = 0;

						ifAsec = 0;
						ifLsec = 0;
					}

				}
			}


		}
		else if (b.boss_HP <= 0)
		{
			isBoss = 0;
			ifBossSe = 0;
			b.boss_AttType = 0;
			boss_mp3 = 1;
			b.boss_Att = 25;

			Lsec = 0;               //前置时间
			Asec = 0;               //后置时间
			ifLsec = 0;             //0表示还未获取时间
			ifAsec = 0;

			BBHead = NULL;         //重置子弹表


			//b.ifblast = 0;            //爆炸  1为不应该 0为即将爆炸

			
		}

		
	}
}

void IDN::save_score()
{	
	for (int iii = 0; iii < 9; iii++) //显示之前先对所有分数排序
	{
		for (int jjj = 0; jjj < 9 - iii; jjj++)
		{
			if (SCORE[jjj] < SCORE[jjj+ 1])
			{
				int temp = SCORE[jjj];
				SCORE[jjj] = SCORE[jjj + 1];
				SCORE[jjj + 1] = temp;
			}
		}
	}//现在已经从大到小排序完成

	int temp_i = -1;

	for (int iii = 0; iii < 10; iii++)//一一比较判断分数能否加入前十名
	{
		if (KillScore > SCORE[iii])
		{
			temp_i = iii;           //记录位置
			break;                  //然后退出循环
		}
	}

	

	if (temp_i != -1)
	{
		for (int m = 9; m > temp_i; m--)
		{
			SCORE[m] = SCORE[m - 1];
		}

		SCORE[temp_i] = KillScore;
	}
	

	ofstream ofs;
	ofs.open(FILE, ios::out);
	
	for(int iii = 0; iii < 10; iii++)
	{
		ofs << SCORE[iii] << " ";
	}

	ofs.close();
}

void IDN::readin_score()
{
	ifstream ifs;
	ifs.open(FILE, ios::in);
	int i = 0;
	while (ifs>>SCORE[i])
	{
		i++;
	}
	ifs.close();

	for (int iii = 0; iii < 9; iii++) //对所有分数排序
	{
		for (int jjj = 0; jjj < 9 - iii; jjj++)
		{
			if (SCORE[jjj] < SCORE[jjj + 1])
			{
				int temp = SCORE[jjj];
				SCORE[jjj] = SCORE[jjj + 1];
				SCORE[jjj + 1] = temp;
			}
		}
	}//现在已经从大到小排序完成
}

void IDN::score_list()
{
	cleardevice();
	putimage(0, 0, &list);

	char S1[50];
	for (int i = 0; i < 10; i++)  //循环打印分数
	{
		if (i < 3)
		{
			sprintf_s(S1, "%d", SCORE[i]);
			outtextxy(Width * 0.55, High * 0.20 + i * 78, S1);
		}
		else if (i >= 3)
		{
			sprintf_s(S1, "%d", SCORE[i]);
			outtextxy(Width * 0.55, High * 0.20 + 3 * 71.9 + (i-3) * 54, S1);
		}
		
	}



	if (GetAsyncKeyState(VK_ESCAPE)) //也可以通过ESC来返回
	{
		this->which = 0;
	}

	MOUSEMSG m;
	while (MouseHit())  //判断鼠标是否有动作
	{
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN)//按下鼠标左键时
		{
			this->which = 0;
		}
	}

}

void IDN::GameEnd()
{
	if (Main_music == 1)
	{
		mciSendString(_T("close bkmusic"), NULL, 0, NULL);
		mciSendString(_T("open data\\audio\\bgm.mp3 alias bkmusic"), NULL, 0, NULL);//背景音乐
		mciSendString(_T("play bkmusic repeat"), NULL, 0, NULL);
		Main_music = 0;
	}
	else if(map01_music==1)
	{
		mciSendString(_T("close bkmusic"), NULL, 0, NULL);
		mciSendString(_T("open data\\audio\\map01.mp3 alias mp1music"), NULL, 0, NULL);//背景音乐
		mciSendString(_T("play mp1music repeat"), NULL, 0, NULL);
		map01_music = 0;
	}
	else if (map02_music == 1)
	{
		mciSendString(_T("close bkmusic"), NULL, 0, NULL);
		mciSendString(_T("open data\\audio\\map02.mp3 alias mp2music"), NULL, 0, NULL);//背景音乐
		mciSendString(_T("play mp2music repeat"), NULL, 0, NULL);
		map02_music = 0;
	}
	else if (map03_music == 1)
	{
		mciSendString(_T("close bkmusic"), NULL, 0, NULL);
		mciSendString(_T("open data\\audio\\map03.mp3 alias mp3music"), NULL, 0, NULL);//背景音乐
		mciSendString(_T("play mp3music repeat"), NULL, 0, NULL);
		map03_music = 0;
	}


	//收尾
	Sleep(10);
	FlushBatchDraw();
}