#include<graphics.h>
#include<fstream>
#include"IDN.h"
#include"bullet.h"
#include"cloud.h"
#include"map.h"
#include"boss.h"
#include"boss01_bullet.h"
#pragma comment(lib,"Winmm.lib")
#define High 980          //���廭���߶�
#define Width 650         //���廭�����
#define SHOW_BOSS01 12500 //����BOSS01���ֵ�ʱ��
#define BOSSHP 25000      //����BOSSѪ��
#define FILE "data.dat"   //�����ļ���
using namespace std;

SYSTEMTIME ti;              //��ȡʱ��
int Lsec = 0;               //ǰ��ʱ��
int Asec = 0;               //����ʱ��
int ifLsec = 0;             //0��ʾ��δ��ȡʱ��
int ifAsec = 0;
int ifBoss2 = 0;            //�ж�Boss�Ƿ���γ���



int result_mp3 = 1;       //�����жϽ�����Ч�Ƿ񲥷�
int boss_mp3 = 1;         //�����ж�BOSS��Ч�Ƿ񲥷�
int isBoss = 0;           //�����ж�Boss01�Ƿ����
int ifBossSe = 1;         //1��ʾBoss��� ����ˢ��С��

int startbutton = 1;      //�жϿ�ʼ��ť��û�б�����  1��ʾ����״̬
int game_backbutton = 1;  //��Ϸ����İ�ť
int cmp_backbutton = 1;   //ѡͼ����İ�ť
int helpbutton = 1;       //������İ�����ť
int listbutton = 1;       //�������������ť

int cmp_map001_down = 1;  //��ť״̬����  ����С��ͼ��ť1������
int cmp_map002_down = 1;  //��ť״̬����  ����С��ͼ��ť2������
int cmp_map003_down = 1;  //��ť״̬����  ����С��ͼ��ť3������

int FullScore = 30;       //ʵʱ���µ����ӵ���Ŀ
int score = FullScore;    //��ǰ�ӵ���Ŀ
int ArmScore = 10;        //װ���ӵ���Ŀ����ҩ�ظ�����
int btype = 1;            //�ӵ���̬
int bret = 1;             //�ж��ӵ��Ƿ�����  1Ϊδ����

int KillNum = 0;          //��ǰ����л���Ŀ
int KillScore = 0;        //��ǰ�÷�
double e1speed = 2;       //��ǰ����01���ٶ�
double e1_HP = 200.0;     //����01��ǰ��HP
int i = 1;                //�����жϻ���л����Ƿ���10�ı���(����)
int FullHP;               //ʵʱ���µ���Ѫ��
int temp_score;           //�����ж�װ�����ӵ������Ƿ�Խ��
int EnemyType = 1;        //����01������
int RANGE = 600;          //���Ƴ��ֵл��ļ��
int range;                //���Ƴ��ֵл��ļ��0

int MType = 1;            //��ͼ����

int ksc = 0;              //�������ָ���
int isksc = 1;            //���ڿ���  ����ֻ�ܻ���һ��  �ı���

int SCORE[10] = {0};      //���ڱ���ǰʮ���ķ���
int ifsave = 0;           //�����ж��Ƿ��Ѿ�����

int Main_music = 1;       //����������
int map01_music = 0;      //��ͼ1����
int map02_music = 0;      //��ͼ2����
int map03_music = 0;      //��ͼ3����


IMAGE enemy01, enemy01_zz;//����01��������̬
IMAGE enemy0102, enemy0102_zz;
IMAGE enemy0103, enemy0103_zz;

IMAGE Char, Char_zz;      //�ҷ���ɫ

IMAGE HP, HP_D;           //Ѫ��
IMAGE Arm;                //��ҩ��

IMAGE bullet, bullet_zz;  //�ӵ�
IMAGE bullet02, bullet02_zz;

IMAGE blast, blast_zz;   //��ը����
IMAGE Bblast, Bblast_zz;   //BOSS��ը����

IMAGE Main, bk, bk2, bk3;        //��ͼ�������汳��
IMAGE cmpbk, cmp, bk001, bk001d, bk001u, bk002, bk002d, bk002u, bk003, bk003d, bk003u;

IMAGE item01, item01_zz;  //���ֵ���
IMAGE item02, item02_zz;
IMAGE item03, item03_zz;

IMAGE title, title_zz;    //����
IMAGE start, start_zz, startd, startd_zz;    //��ʼ����
IMAGE help, help_zz, helpd, helpd_zz;  //��������
IMAGE helpbk;             //��������


IMAGE back, back_zz;      //���ذ���
IMAGE backd, backd_zz;    //���ذ�������
IMAGE listbtn, listbtnd,listbtn_zz;   //���а񰴼�

IMAGE ret;                //�ɼ��������
IMAGE num, num_zz;        //����ͼƬ
IMAGE ret2401, ret2402, ret2403, ret24_zz;  //�������Ի���

IMAGE boss01, boss01_zz;         //Boss01
IMAGE boss01_att01, boss01_att01_zz;         //Boss01����1

IMAGE BB01, BB01_zz;             //Boss01���ӵ�
IMAGE BB02, BB02_zz;
IMAGE BB03, BB03_zz;

IMAGE list;                 //���а����


void IDN::MAIN()
{
	putimage(0, 0, &Main);//���Ʊ���ͼ
	putimage(Width / 2 - 250, High * 0.2, &title_zz, NOTSRCERASE);  //���Ʊ���
	putimage(Width / 2 - 250, High * 0.2, &title, SRCINVERT);

	outtextxy(Width * 0.05, High * 0.009, " �汾��1.1         ��ʮ��������ҹ");

	result_mp3 = 1;//��ʼ��������Ч

	if (startbutton == 1)  //��ʼ��ť����
	{
		putimage(Width / 2 - 83, High * 0.78, &start_zz, NOTSRCERASE);
		putimage(Width / 2 - 83, High * 0.78, &start, SRCINVERT);
	}
	else if (startbutton == 0)  //��ʼ��ť������
	{
		putimage(Width / 2 - 83, High * 0.785, &startd_zz, NOTSRCERASE);
		putimage(Width / 2 - 83, High * 0.785, &startd, SRCINVERT);

		mciSendString(_T("close stmusic"), NULL, 0, NULL);
		mciSendString(_T("open data\\audio\\start.mp3 alias stmusic"), NULL, 0, NULL);
		mciSendString(_T("play stmusic"), NULL, 0, NULL);//����һ����Ч

		FlushBatchDraw();
		Sleep(300);
		startbutton = 1;
		this->which = 2;
	}



	if (helpbutton == 1)  //������ť����
	{
		putimage(30, High * 0.03, &help_zz, NOTSRCERASE);
		putimage(30, High * 0.03, &help, SRCINVERT);
	}
	else if (helpbutton == 0)  //������ť������
	{
		putimage(30, High * 0.03, &helpd_zz, NOTSRCERASE);
		putimage(30, High * 0.03, &helpd, SRCINVERT);

		mciSendString(_T("close hpmusic"), NULL, 0, NULL);
		mciSendString(_T("open data\\audio\\help.mp3 alias hpmusic"), NULL, 0, NULL);
		mciSendString(_T("play hpmusic"), NULL, 0, NULL);//����һ����Ч

		FlushBatchDraw();
		Sleep(250);
		helpbutton = 1;
		this->which = 4;
	}

	if (listbutton == 1)  //��ʼ��ť����
	{
		putimage(Width / 2 - 100, High * 0.86, &listbtn_zz, NOTSRCERASE);
		putimage(Width / 2 - 100, High * 0.86, &listbtn, SRCINVERT);
	}
	else if (listbutton == 0)  //��ʼ��ť������
	{
		putimage(Width / 2 - 100, High * 0.86, &listbtn_zz, NOTSRCERASE);
		putimage(Width / 2 - 100, High * 0.86, &listbtnd, SRCINVERT);

		mciSendString(_T("close lstmusic"), NULL, 0, NULL);
		mciSendString(_T("open data\\audio\\list.mp3 alias lstmusic"), NULL, 0, NULL);
		mciSendString(_T("play lstmusic"), NULL, 0, NULL);//����һ����Ч

		FlushBatchDraw();
		Sleep(300);
		listbutton = 1;
		this->which = 5;
	}

	MOUSEMSG m;  //��������

	while (MouseHit())  //�ж�����Ƿ��ж���
	{
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN)//����������ʱ
		{
			if (m.x >= Width / 2 - 83 && m.x <= Width / 2 + 83 && m.y >= High * 0.78 && m.y <= High * 0.78 + 46)
			{
				startbutton = 0; //��ʼ��ť������
			}

			if (m.x >= 30 && m.x <= 30 + 74 && m.y >= High * 0.03 && m.y <= High * 0.03 + 46)
			{
				helpbutton = 0; //������ť������
			}

			if (m.x >= Width/2-100 && m.x <= Width / 2 +100 && m.y >= High * 0.86 && m.y <= High * 0.86 + 40)
			{
				listbutton = 0; //���а�ť������
			}
		}
	}
}

void IDN::start_game()
{
	initgraph(Width, High);//���ƻ���

	setbkcolor(46154254);  //��ɫ
	setbkmode(TRANSPARENT);//͸��
	cleardevice();

	readin_score();  //��Ϸ��ʼʱ��ȡ��¼
	
	loadimage(&title, _T("data//title.png"), 500, 320);   //����
	loadimage(&title_zz, _T("data//title_zz.png"), 500, 320);

	loadimage(&ret2401, _T("data//ret2401.png"), Width, 223);  //ret24
	loadimage(&ret2402, _T("data//ret2402.png"), Width, 223);
	loadimage(&ret2403, _T("data//ret2403.png"), Width, 223);
	loadimage(&ret24_zz, _T("data//ret24_zz.png"), Width, 223);

	loadimage(&num, _T("data//number.png"), 384, 512);   //����
	loadimage(&num_zz, _T("data//number_zz.png"), 384, 512);

	loadimage(&back, _T("data//back.png"), 89, 46);   //���ذ�ť
	loadimage(&back_zz, _T("data//back_zz.png"), 89, 46);
	loadimage(&backd, _T("data//backdown.png"), 89, 46);  //���ذ�ť����
	loadimage(&backd_zz, _T("data//backdown_zz.png"), 89, 46);

	loadimage(&listbtn, _T("data//listbtn.png"), 200, 40);   //������ť
	loadimage(&listbtn_zz, _T("data//listbtn_zz.png"), 200, 40);
	loadimage(&listbtnd, _T("data//listbtn_down.png"), 200, 40);  //������ť����

	loadimage(&ret, _T("data//result.png"), Width, High);  //���㱳��

	loadimage(&Main, _T("data//MAIN.png"), Width, High);
	loadimage(&start, _T("data//start.png"), 166, 46);
	loadimage(&start_zz, _T("data//start_zz.png"), 166, 46);//��ʼ����
	loadimage(&startd, _T("data//startdown.png"), 166, 46);
	loadimage(&startd_zz, _T("data//startdown_zz.png"), 166, 46);//��ʼ��������

	loadimage(&help, _T("data//help.png"), 74, 46);
	loadimage(&help_zz, _T("data//help_zz.png"), 74, 46);//��������
	loadimage(&helpd, _T("data//helpd.png"), 74, 46);
	loadimage(&helpd_zz, _T("data//helpd_zz.png"), 74, 46);//������������
	loadimage(&helpbk, _T("data//helpbk.png"), Width, High);//�������汳��

	loadimage(&list, _T("data//list.png"), Width, High);//�������汳��

	loadimage(&enemy01, _T("data//e01.png"), 150, 150);
	loadimage(&enemy01_zz, _T("data//e01_zz.png"), 150, 150);//����01
	loadimage(&enemy0102, _T("data//e0102.png"), 150, 150);
	loadimage(&enemy0102_zz, _T("data//e0102_zz.png"), 150, 150);//����0102
	loadimage(&enemy0103, _T("data//e0103.png"), 150, 150);
	loadimage(&enemy0103_zz, _T("data//e0103_zz.png"), 150, 150);//����0103

	loadimage(&Char, _T("data//char.png"), 120, 120);
	loadimage(&Char_zz, _T("data//char_zz.png"), 120, 120);//��ɫ

	loadimage(&boss01, _T("data//boss01.png"), 250, 250);
	loadimage(&boss01_zz, _T("data//boss01_zz.png"), 250, 250);//BOSS01

	loadimage(&boss01_att01, _T("data//boss01_att01.png"), 250, 250);
	loadimage(&boss01_att01_zz, _T("data//boss01_att01_zz.png"), 250, 250);//BOSS01����1

	loadimage(&bullet, _T("data//bullet.png"), 30, 75);
	loadimage(&bullet_zz, _T("data//bullet_zz.png"), 30, 75);//�ӵ�

	loadimage(&bullet02, _T("data//bullet02.png"), 60, 75);
	loadimage(&bullet02_zz, _T("data//bullet02_zz.png"), 60, 75);//�ӵ�02

	loadimage(&blast, _T("data//blast.png"), 512, 512);
	loadimage(&blast_zz, _T("data//blast_zz.png"), 512, 512);//��ը����

	loadimage(&Bblast, _T("data//blast.png"), 1024, 1024);
	loadimage(&Bblast_zz, _T("data//blast_zz.png"), 1024, 1024);//BOSS��ը����

	loadimage(&BB01, _T("data//BB01.png"), 30, 30);
	loadimage(&BB01_zz, _T("data//BB01_zz.png"),30,30);//BOSS�ӵ�01
	loadimage(&BB02, _T("data//BB02.png"), 30, 30);
	loadimage(&BB02_zz, _T("data//BB02_zz.png"), 30, 30);//BOSS�ӵ�02
	loadimage(&BB03, _T("data//BB03.png"), 30, 30);
	loadimage(&BB03_zz, _T("data//BB03_zz.png"), 30, 30);//BOSS�ӵ�03

	loadimage(&HP, _T("data//HP.png"), 400, 35);//������
	loadimage(&HP_D, _T("data//HP_D.png"), 400, 35);

	loadimage(&bk, _T("data//map.png"), Width, High);//��ͼ����
	loadimage(&bk2, _T("data//map2.png"), Width, High);
	loadimage(&bk3, _T("data//map3.png"), Width, High);

	loadimage(&bk001, _T("data//map001.png"), 150, 150);//��ͼСͼ
	loadimage(&bk002, _T("data//map002.png"), 150, 150);//��ͼСͼ
	loadimage(&bk003, _T("data//map003.png"), 150, 150);//��ͼСͼ
	loadimage(&bk001d, _T("data//map001_down.png"), 150, 150);
	loadimage(&bk002d, _T("data//map002_down.png"), 150, 150);
	loadimage(&bk003d, _T("data//map003_down.png"), 150, 150);

	loadimage(&bk001u, _T("data//map001_up.png"), 150, 150);
	loadimage(&bk002u, _T("data//map002_up.png"), 150, 150);
	loadimage(&bk003u, _T("data//map003_up.png"), 150, 150);

	loadimage(&cmpbk, _T("data//cmpbk.png"), Width, High);//ѡͼ����
	loadimage(&cmp, _T("data//cmp.png"), Width, 350);//ѡͼ����

	loadimage(&Arm, _T("data//arm.png"), 400, 15);//��ҩ��

	loadimage(&item01, _T("data//item01.png"), 80, 80);
	loadimage(&item01_zz, _T("data//item01_zz.png"), 80, 80);//����1  �ظ�HP

	loadimage(&item02, _T("data//item02.png"), 80, 80);
	loadimage(&item02_zz, _T("data//item02_zz.png"), 80, 80);//����2  �ָ������ӵ�ҩ����

	loadimage(&item03, _T("data//item03.png"), 80, 80);
	loadimage(&item03_zz, _T("data//item03_zz.png"), 80, 80);//����3  �ָ�Ѫ�������ӹ�����


	//mciSendString(_T("open data\\audio\\bgm.mp3 alias bkmusic"), NULL, 0, NULL);//��������
	//mciSendString(_T("play bkmusic repeat"), NULL, 0, NULL);

	FullHP = this->char_HP;//��¼��ʼHP

	BeginBatchDraw();
}

void IDN::play_game(Bullet*& TempHead, Bullet*& TempTail , Cloud*& TempHead2, Cloud*& TempTail2 )
{
	GetLocalTime(&ti);

	putimage(Width * 0.08, High * 0.012, &HP_D);
	putimage(Width * 0.08, High * 0.012, 400 * this->char_HP / FullHP, 35, &HP, 0, 0); //����ʵʱѪ��

	putimage(Width * 0.08, High * 0.045, 400 * score / FullScore, 15, &Arm, 0, 0);  //����ʵʱ��ҩ��
	outtextxy(Width * 0.02, High * 0.045, "��ҩ");

	char Hp[50];
	sprintf_s(Hp, "%d", this->char_HP);
	outtextxy(Width * 0.02, High * 0.02, "����");
	outtextxy(Width * 0.1, High * 0.022, Hp);  //��������������

	char FHp[50];
	sprintf_s(FHp, "%d", FullHP);
	outtextxy(Width * 0.155, High * 0.02, "/");
	outtextxy(Width * 0.18, High * 0.022, FHp);  //��������������

	char s0[50];
	sprintf_s(s0, "%d", KillScore);
	outtextxy(Width * 0.02, High * 0.08, "�÷�");
	outtextxy(Width * 0.1, High * 0.081, s0);   //���õ÷�


	Cloud* Current2 = TempHead2;
	Cloud* TempQ2 = NULL;
	while (Current2)
	{
		if (Current2->type == 1)//���Ƶ���1
		{
			putimage(Current2->cloud_X, Current2->cloud_Y, &item01_zz, NOTSRCERASE);
			putimage(Current2->cloud_X, Current2->cloud_Y, &item01, SRCINVERT);
		}
		else if (Current2->type == 2)//���Ƶ���2
		{
			putimage(Current2->cloud_X, Current2->cloud_Y, &item02_zz, NOTSRCERASE);
			putimage(Current2->cloud_X, Current2->cloud_Y, &item02, SRCINVERT);
		}
		else if (Current2->type == 3)//���Ƶ���3
		{
			putimage(Current2->cloud_X, Current2->cloud_Y, &item03_zz, NOTSRCERASE);
			putimage(Current2->cloud_X, Current2->cloud_Y, &item03, SRCINVERT);
		}

		Current2->cloud_Y += Current2->cloud_speed;//�õ��߰��趨���ٶ��ƶ�


		//��Խ��ĵ�����ɾ������
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
		if (Current->bullet_type == 1)  //������Ӧ���͵��ӵ�
		{
			putimage(Current->bullet_X - 16, Current->bullet_Y - 30, &bullet_zz, NOTSRCERASE);
			putimage(Current->bullet_X - 16, Current->bullet_Y - 30, &bullet, SRCINVERT);
		}
		else if (Current->bullet_type == 2)  //������Ӧ���͵��ӵ�
		{
			putimage(Current->bullet_X - 30, Current->bullet_Y - 35, &bullet02_zz, NOTSRCERASE);
			putimage(Current->bullet_X - 30, Current->bullet_Y - 35, &bullet02, SRCINVERT);
		}

		Current->bullet_Y -= Current->bullet_speed;//���ӵ����趨���ٶ��ƶ�

		//��Խ����ӵ���ɾ������
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



	if (this->char_HP <= 0)  //�ж�Ѫ���Ƿ�Ϊ0
	{
		this->which = 3;
	}
}

void IDN::chose_map()
{
	putimage(0, 0, &cmpbk);   //���ñ���
	putimage(0, High - 350, &cmp);

	if (cmp_backbutton == 1)   //���ذ�ť����
	{
		putimage(Width * 0.81, High * 0.02, &back_zz, NOTSRCERASE);//���÷��ؼ�
		putimage(Width * 0.81, High * 0.02, &back, SRCINVERT);
	}
	else if (cmp_backbutton == 0)  //���ذ�ť����
	{
		putimage(Width * 0.81, High * 0.03, &backd_zz, NOTSRCERASE);//���÷��ؼ�
		putimage(Width * 0.81, High * 0.03, &backd, SRCINVERT);

		mciSendString(_T("close btmmusic"), NULL, 0, NULL);
		mciSendString(_T("open data\\audio\\btm.mp3 alias btmmusic"), NULL, 0, NULL);
		mciSendString(_T("play btmmusic"), NULL, 0, NULL);//����һ����Ч

		FlushBatchDraw();
		Sleep(300);

		this->which = 0;
		cmp_backbutton = 1;
	}

	if (cmp_map001_down == 2)  //С��ͼ��ť1����������꾭����
	{
		putimage(Width / 3 - 125, High / 3 - 100, &bk001u);
	}
	else if (cmp_map001_down == 1)//С��ͼ��ť1����
	{
		putimage(Width / 3 - 125, High / 3 - 100, &bk001);
	}
	else if (cmp_map001_down == 0)//С��ͼ��ť1������
	{
		putimage(Width / 3 - 125, High / 3 - 100, &bk001d);

		mciSendString(_T("close gsmmusic"), NULL, 0, NULL);
		mciSendString(_T("open data\\audio\\gamestart.mp3 alias gsmmusic"), NULL, 0, NULL);
		mciSendString(_T("play gsmmusic"), NULL, 0, NULL);//����һ����Ч
		
		

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

	if (cmp_map002_down == 2) //С��ͼ��ť2����������꾭����
	{
		putimage(Width / 3 + 185, High / 3 - 100, &bk002u);
	}
	else if (cmp_map002_down == 1)//С��ͼ��ť2����
	{
		putimage(Width / 3 + 185, High / 3 - 100, &bk002);
	}
	else if (cmp_map002_down == 0)//С��ͼ��ť2������
	{
		putimage(Width / 3 + 185, High / 3 - 100, &bk002d);

		mciSendString(_T("close gsmmusic"), NULL, 0, NULL);
		mciSendString(_T("open data\\audio\\gamestart.mp3 alias gsmmusic"), NULL, 0, NULL);
		mciSendString(_T("play gsmmusic"), NULL, 0, NULL);//����һ����Ч

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

	if (cmp_map003_down == 2) //С��ͼ��ť3����������꾭����
	{
		putimage(Width / 3 + 25, High / 3 + 100, &bk003u);
	}
	else if (cmp_map003_down == 1)//С��ͼ��ť3����
	{
		putimage(Width / 3 + 25, High / 3 + 100, &bk003);
	}
	else if (cmp_map003_down == 0)//С��ͼ��ť3������
	{
		putimage(Width / 3 + 25, High / 3 + 100, &bk003d);

		mciSendString(_T("close gsmmusic"), NULL, 0, NULL);
		mciSendString(_T("open data\\audio\\gamestart.mp3 alias gsmmusic"), NULL, 0, NULL);
		mciSendString(_T("play gsmmusic"), NULL, 0, NULL);//����һ����Ч

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


	if (GetAsyncKeyState(VK_ESCAPE)) //Ҳ����ͨ��ESC������
	{
		cmp_backbutton = 0;
	}


	MOUSEMSG m;  //��������

	while (MouseHit())  //�ж�����Ƿ��ж���
	{
		m = GetMouseMsg();

		if (m.uMsg == WM_MOUSEMOVE)//����ƶ����
		{

			if (m.x >= Width / 3 - 125 && m.x <= (Width / 3 - 125 + 150) && m.y >= (High / 3 - 100) && m.y <= (High / 3 - 100 + 150))
			{
				cmp_map001_down = 2;//С��ͼ��ť1����������꾭����
			}
			else
			{
				cmp_map001_down = 1;//��ť2����
			}


			if (m.x >= Width / 3 + 185 && m.x <= (Width / 3 + 185 + 150) && m.y >= (High / 3 - 100) && m.y <= (High / 3 - 100 + 150))
			{
				cmp_map002_down = 2;//С��ͼ��ť2����������꾭����
			}
			else
			{
				cmp_map002_down = 1;//��ť2����
			}

			if (m.x >= Width / 3 + 25 && m.x <= (Width / 3 + 25 + 150) && m.y >= (High / 3 + 100) && m.y <= (High / 3 + 100 + 150))
			{
				cmp_map003_down = 2;//С��ͼ��ť3����������꾭����
			}
			else
			{
				cmp_map003_down = 1;//��ť3����
			}
		}

		if (m.uMsg == WM_LBUTTONDOWN)//����������ʱ
		{
			if (m.x >= Width * 0.8 && m.x <= Width * 0.8 + 89 && m.y >= High * 0.02 && m.y <= High * 0.02 + 46)
			{
				cmp_backbutton = 0;  //���ذ�ť
			}

			if (m.x >= Width / 3 - 125 && m.x <= (Width / 3 - 125 + 150) && m.y >= (High / 3 - 100) && m.y <= (High / 3 - 100 + 150))
			{
				cmp_map001_down = 0;//С��ͼ��ť1������
			}

			if (m.x >= Width / 3 + 185 && m.x <= (Width / 3 + 185 + 150) && m.y >= (High / 3 - 100) && m.y <= (High / 3 - 100 + 150))
			{
				cmp_map002_down = 0;//С��ͼ��ť2������
			}

			if (m.x >= Width / 3 + 25 && m.x <= (Width / 3 + 25 + 150) && m.y >= (High / 3 + 100) && m.y <= (High / 3 + 100 + 150))
			{
				cmp_map003_down = 0;//С��ͼ��ť3������
			}
		}
	}

}

void IDN::help_player()
{
	putimage(0, 0, &helpbk);

	if (GetAsyncKeyState(VK_ESCAPE)) //Ҳ����ͨ��ESC������
	{
		this->which = 0;
	}

	MOUSEMSG m;
	while (MouseHit())  //�ж�����Ƿ��ж���
	{
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN)//����������ʱ
		{
			this->which = 0;
		}
	}
}

void IDN::creat_Num(RetNum*& TempHead, RetNum*& TempTail, double X, double Y)
{
	//�������ڴ������ֱ�Ľڵ�
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
	//�������ڻ���������Ӧ��ͼƬ
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
		Print(N / 10, TempHead, TempTail);  //�����ĵݹ�
	}

}

void IDN::result(RetNum*& TempHead, RetNum*& TempTail, Enemy01*& TempHead1, Bullet*& TempHead2, Cloud*& TempHead3, Map*& TempHead4, Boss01& b, BossBlt*& BBHead)
{
	cleardevice();
	putimage(0, 0, &ret);

	if (ifsave==0)
	{
		save_score();//�������
		ifsave = 1;
	}
	

	if (isksc == 1)  //��ֻ֤�����һ��
	{
		Print(KillScore, TempHead, TempTail);
		isksc = 0; //��ֻ֤�����һ��
	}

	if (KillScore > 0)  //�������0�Ļ� ��ʼ��������
	{
		RetNum* Current = TempHead;
		while (Current)
		{
			putimage(Current->num_X, Current->num_Y, 128, 128, &num_zz, Current->drawnumX, Current->drawnumY, NOTSRCERASE);
			putimage(Current->num_X, Current->num_Y, 128, 128, &num, Current->drawnumX, Current->drawnumY, SRCINVERT);
			Current = Current->Next;
		}
	}
	else  //�����0�Ļ�ֱ�ӷ�0��ͼƬ
	{
		putimage(Width * 0.5 - 50, High * 0.5, 128, 128, &num_zz, 130, 0, NOTSRCERASE);
		putimage(Width * 0.5 - 50, High * 0.5, 128, 128, &num, 130, 0, SRCINVERT);
	}


	//��������Ӧ��Χ������Ӧ�� �������� �Ի����еĲ�ͬ����
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


	if (GetAsyncKeyState(VK_ESCAPE)) //Ҳ����ͨ��ESC������
	{
		this->which = 0;//�ص����˵�

		show_gameover(TempHead1, TempHead2, TempHead3, TempHead4, TempHead, b,BBHead); //��ʼ����Ϸ����
	}


	//����  �ɼ��������  �������Ϊ���
	MOUSEMSG m;  //��������
	while (MouseHit())  //�ж�����Ƿ��ж���
	{
		m = GetMouseMsg();

		if (m.uMsg == WM_MBUTTONDOWN)//��������м�
		{
			this->which = 0;//�ص����˵�

			show_gameover(TempHead1, TempHead2, TempHead3, TempHead4, TempHead, b,BBHead); //��ʼ����Ϸ����
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
		mciSendString(_T("play retmusic"), NULL, 0, NULL);//����һ����Ч
		FlushBatchDraw();
		Sleep(5600);

		result_mp3 = 0;
	}

}

void IDN::updateWithoutInput(Cloud*& TempHead, Cloud*& TempTail)
{
	//�������ڵ������Եĸ��µ�
	if (KillNum != 0 && KillNum / 10 == i)//�ж�ɱ�����Ƿ񵽴�10�ı���  ÿ����һ��10�ı���Ϊ1��
	{
		draw_cloud(TempHead, TempTail);

		if (i % 12 == 0)  //ÿ12�ֵ���HP����30%
		{
			e1_HP *= 1.3;
		}

		if (RANGE > 200 && i > 0) //ÿ����С���м��
		{
			RANGE -= 50;
		}
		else if (RANGE <= 200 && RANGE > 30 && i > 0) //ÿ����С���м��
		{
			RANGE -= 10;
		}

		if (e1speed <= 4.8)  //�ı�����ٶ�
		{
			e1speed += 0.3;
		}
		else
		{
			e1speed = 4.8;  //�����ٶ�����
		}
		i++;  //������һ��
	}

	if (score <= 0) //�жϵ�ҩ���
	{
		outtextxy(Width * 0.44, High * 0.515, "����Ҽ�װ��");
		outtextxy(Width * 0.45, High * 0.47, "��ҩ�ù���");
	}
}

void IDN::show_gameover(Enemy01*& TempHead, Bullet*& TempHead2, Cloud*& TempHead3, Map*& TempHead4, RetNum*& TempHead5, Boss01& b, BossBlt*& BBHead)
{
	//�ú������ڳ�ʼ����Ϸ����
	this->char_HP = 500;    //��ʼ������
	FullHP = this->char_HP;  //��ʼ������

	FullScore = 30;      //��ʼ�����ӵ���Ŀ
	score = FullScore;   //��ʼ����ǰ�ӵ���Ŀ
	ArmScore = 10;       //��ʼ��װ���ӵ���Ŀ
	btype = 1;           //��ʼ���ӵ�����
	bret = 1;            //��ʼ�������ж��ӵ���̬�Ƿ�仯������ 1Ϊδ�仯

	this->bullet_Att = 100.0;  //��ʼ��������

	KillScore = 0;  //��ʼ���÷�
	KillNum = 0;    //��ʼ������л���Ŀ

	e1speed = 2;   //��ʼ������01���ٶ�
	e1_HP = 200.0; //��ʼ������01��HP

	i = 1;         //��ʼ������

	this->char_X = Width / 2.0 + 20.0;  //��ʼ������
	this->char_Y = 700.0;

	ksc = 0;        //��ʼ�����ָ���
	isksc = 1;      //��ʼ��  �Ƿ���ƹ�����  �ı���

	b.boss_HP = BOSSHP;  //��ʼ��BossѪ��
	isBoss = 0;        //��ʼ�� BOSS�Ƿ���� ����
	ifBossSe = 1;      //��ʼ�� Boss�Ƿ��� ����
	b.boss_X = Width / 2.0 - 125.0;
	b.boss_Y = -300.0;
	b.boss_AttType = 0;   //��ʼ��Boss����״̬
	b.boss_attspeed = 3;   //��ʼ��Boss����Ƶ��
	ifBoss2 = 0;           //��ʼ��Boss�Ƿ�ڶ��γ���
	b.boss_Att = 30;       //��ʼ��Boss������

	b.B_Lsec = 0;             //��ʼ����ըǰ��ʱ��
	b.B_Asec = 0;             //��ʼ����ը����ʱ��
	b.ifB_Lsec = 0;           //��ʼ����ը�ж�ǰ��ʱ���Ƿ��Ѿ���¼
	b.ifB_Asec = 0;			  //��ʼ����ը�жϺ���ʱ���Ƿ��Ѿ���¼
	b.ifblast = 0;            //��ʼ����ը�ж��Ƿ�Ӧ�ñ�ը  0Ϊ������ը
	b.blast_i = 0;            //��ʼ����ը��������
	b.blast_j = 0;            //��ʼ����ը��������

	boss_mp3 = 1;      //��ʼ�� Boss������Ч

	Main_music = 1;       //��ʼ������������
	map01_music = 0;      //��ʼ����ͼ1����
	map02_music = 0;      //��ʼ����ͼ2����
	map03_music = 0;      //��ʼ����ͼ3����

	Lsec = 0;               //��ʼ��ǰ��ʱ��
	Asec = 0;               //��ʼ������ʱ��
	ifLsec = 0;             //0��ʾ��δ��ȡʱ��
	ifAsec = 0;

	ifsave = 0;               //Ϊ��һ�α�����׼��

	//6�������ͷָ��ȫ��ָ���   �������������
	TempHead = NULL;             //��ʼ������01��
	TempHead2 = NULL;            //��ʼ���ӵ���
	TempHead3 = NULL;            //��ʼ�����߱�
	TempHead4 = NULL;            //��ʼ����ͼ��
	TempHead5 = NULL;            //��ʼ�����ֱ�
	BBHead = NULL;               //��ʼ��BOSS�ӵ���
}

void IDN::draw_map(Map*& MapHead, Map*& MapTail)
{
	//�������ĵ�ͼ
	if (MapHead == NULL)
	{
		MapHead = new Map;
		MapTail = MapHead;
		MapHead->MapType = MType;
		if (MapHead->MapType == 2)   //�жϵ�ͼ����
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
		if (MapTail->map_Y > 0)  //���Ƶڶ��Ż�֮���ͼ������
		{
			MapTail->Next = new Map;
			MapTail->Next->map_Y = MapTail->map_Y - High;
			MapTail = MapTail->Next;
			MapTail->MapType = MType;

			if (MapTail->MapType == 2) //�жϵ�ͼ����
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

	//���Ʊ���
	Map* Current2 = MapHead;
	Map* TempQ2 = NULL;
	while (Current2)
	{
		if (Current2->MapType == 1)//��һ�౳��
		{
			putimage(0, Current2->map_Y, &bk);
		}
		else if (Current2->MapType == 2)//�ڶ��౳��
		{
			putimage(0, Current2->map_Y, &bk2);
		}
		else if (Current2->MapType == 3)//�����౳��
		{
			putimage(0, Current2->map_Y, &bk3);
		}

		Current2->map_Y += Current2->map_speed;

		//��Խ��ĵ�ͼ��ɾ������  ��ֹ���ڿ��ܲ����Ŀ���
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
	if (score > 0)  //��ҩ����0���ܷ����ӵ�
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
		score--;//�����ҩ��������
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

	BossBlt* Current = BBHead; //���ӵ�����
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
			mciSendString(_T("play bbbmusic"), NULL, 0, NULL);//����һ����Ч
		}

		Current = Current->Next;
	}

	//����BOSS�ӵ�
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
		
		Current2->bossblt_Y += Current2->bossblt_speed;//��BOSS�ӵ����趨���ٶ��ƶ�


	//��Խ���BOSS�ӵ���ɾ������
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
		putimage(Width * 0.81, High * 0.02, &back_zz, NOTSRCERASE);//���÷��ؼ�
		putimage(Width * 0.81, High * 0.02, &back, SRCINVERT);
	}
	else if (game_backbutton == 0)
	{
		putimage(Width * 0.81, High * 0.03, &backd_zz, NOTSRCERASE);//���÷��ؼ�
		putimage(Width * 0.81, High * 0.03, &backd, SRCINVERT);

		
		mciSendString(_T("close btmmusic"), NULL, 0, NULL);
		mciSendString(_T("open data\\audio\\btm.mp3 alias btmmusic"), NULL, 0, NULL);
		mciSendString(_T("play btmmusic"), NULL, 0, NULL);//����һ����Ч

		FlushBatchDraw();
		Sleep(300);
		
		this->char_HP -= 9999999;
		game_backbutton = 1;
	}


	if (GetAsyncKeyState(VK_ESCAPE)) //Ҳ����ͨ��ESC������
	{
		game_backbutton = 0;
	}



	//�������������Ϸʱ�����궯�����
	MOUSEMSG m;  //��������

	while (MouseHit())  //�ж�����Ƿ��ж���
	{
		m = GetMouseMsg();

		if (m.uMsg == WM_MOUSEMOVE)//����ƶ����
		{
			this->char_X = m.x - 60.0;
			this->char_Y = m.y - 60.0;
		}

		if (m.uMsg == WM_LBUTTONDOWN)//����������ʱ
		{
			if (m.x >= Width * 0.8 && m.x <= Width * 0.8 + 89 && m.y >= High * 0.02 && m.y <= High * 0.02 + 46)
			{	//���ж��ǲ����ڰ����ؼ�
				game_backbutton = 0;
			}
			else
			{
				add_bullet(m.x, m.y, TempHead, TempTail);//�����ӵ�
			}
		}

		if (m.uMsg == WM_RBUTTONDOWN)//��������Ҽ�ʱ�����ӵ�
		{
			temp_score = score + ArmScore;//���ж�ֱ�Ӽ��Ϻ�᲻��Խ��

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
	//������ ���ö�˵��8
	//�·�ע�͵�������Easyxͼ�ο�+�����뻭������ �᲻��ɾ
	//����Ȥ������һ��
	//���Ǻ�����û�ж�����ɻ���������ӵ�λ�õļ�����(
	putimage(this->char_X, this->char_Y, &Char_zz, NOTSRCERASE);
	putimage(this->char_X, this->char_Y, &Char, SRCINVERT);

	//fillrectangle(this->char_X - 18, this->char_Y - 50, this->char_X + 18, this->char_Y + 50);//����
	//fillrectangle(this->char_X - 10, this->char_Y + 50, this->char_X + 10, this->char_Y + 75);//�²�
	//fillrectangle(this->char_X - 17, this->char_Y + 75, this->char_X + 17, this->char_Y + 85);//�ײ�
	//fillcircle(this->char_X, this->char_Y - 50, 18);
	//POINT pts[] = { {this->char_X - 20, this->char_Y + 45}, {this->char_X - 20, this->char_Y - 45}, {this->char_X - 80, this->char_Y + 50} };//�����
	//POINT pts2[] = { {this->char_X + 20, this->char_Y + 45}, {this->char_X + 20, this->char_Y - 45}, {this->char_X + 80, this->char_Y + 50} };//�һ���
	//POINT pts3[] = { {this->char_X - 18, this->char_Y - 57}, {this->char_X + 18, this->char_Y - 57}, {this->char_X , this->char_Y - 95} };//��ͷ
	//POINT pts4[] = { {this->char_X - 20, this->char_Y + 75}, {this->char_X - 20, this->char_Y + 85}, {this->char_X - 30, this->char_Y + 85} };//���β
	//POINT pts5[] = { {this->char_X + 20, this->char_Y + 75}, {this->char_X + 20, this->char_Y + 85}, {this->char_X + 30, this->char_Y + 85} };//���β

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
	//���Ƶ���
	if (TempHead == NULL)//ͷ����
	{
		TempHead = new Cloud;
		TempHead->cloud_X = 1.0 * (rand() % (Width - 100 - 0 + 1) + 0);
		TempHead->cloud_Y = -180;

		TempHead->NumType = rand() % 90 + 1;

		if (TempHead->NumType > 60)   //���ĵ������͵ĵط�   ����ҲҪ��
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
	else if (TempHead != NULL)//��������
	{
		if (TempTail->cloud_Y >= range)
		{
			TempTail->Next = new Cloud;
			TempTail = TempTail->Next;
			TempTail->cloud_X = 1.0 * (rand() % (Width - 100 - 0 + 1) + 0);
			TempTail->cloud_Y = -180;
			TempTail->NumType = rand() % 90 + 1;
			TempTail->Next = NULL;

			if (TempTail->NumType > 60)   //���ĵ������͵ĵط�   ����ҲҪ��
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
	//���Ƶ���
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

			if (TempHead->EnemyType >= 14)   //���ĵ������Եĵط�   ����ҲҪ��
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

				if (TempTail->EnemyType >= 14)    //���ĵ������Եĵط�   ����ҲҪ��
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

	//���Ƶ���01
	Enemy01* Current2 = TempHead;
	Enemy01* TempQ2 = NULL;
	Enemy01* Temp;
	Enemy01* Temp2;
	while (Current2)
	{
		if (Current2->enemy_HP > 0  && Current2->stoexist == 1)  //Ӧ�ô��ڵĵ��˲��ܱ�����
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

			Current2->enemy_Y += Current2->enemy_speed;//�õ���01���趨���ٶ��ƶ�
		}


		if (Current2->enemy_Y > High + 70.0)
		{
			this->char_HP -= 225;    //����01��Խ���˺�
			Current2->stoexist = 0;  //Խ�����˾Ͳ�Ӧ�ô���
		}

		//��Խ��ĵ���01��ɾ������     ��Ҫ������  ��Ӧ�ô���
		if ((Current2->enemy_Y > High + 70.0 || Current2->enemy_HP <= 0) && Current2->stoexist == 0)
		{
			if (Current2 == TempHead && TempHead->Next == NULL)
			{//ֻ��һ���ڵ�����
				TempHead = nullptr;
				TempTail = NULL;
			}
			else if (Current2 == TempHead && TempHead->Next != NULL)
			{
				//ʲôҲ����
				//Temp = TempHead;
				//TempHead = TempHead->Next;   //���ִ�����д���Ļ��ͻᵼ������
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
				//�ڵ����м�����
				Temp2 = Current2;
				TempQ2->Next = Current2->Next;
				delete Temp2;
				Temp2 = NULL;
				Current2 = TempQ2->Next;
			}
			//}

			Current2 = TempHead;  //��ᵼ������  ���ǲ���ôд�Ļ������
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

	//�ӵ���ײ����01�ж�
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
					Currente->ifblast = 0;  //׼�����ű�ը����

					mciSendString(_T("close btmusic"), NULL, 0, NULL);
					mciSendString(_T("open data\\audio\\bomb0.mp3 alias btmusic"), NULL, 0, NULL);
					mciSendString(_T("play btmusic"), NULL, 0, NULL);//����һ�α�ը��Ч

					KillNum++;//����л�������1

					if (Currente->Type == 1)       //�������01һ���͵ĵ÷����
					{
						KillScore += 100;
					}
					else if (Currente->Type == 2)  //�������01�����͵ĵ÷����
					{
						KillScore += 75;
					}
					else if (Currente->Type == 3)//�������01�����͵ĵ÷����
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

	while (Currentb) //�ӵ�����boss01���ж�
	{
		if (b.boss_HP>0&& b.boss_Y >= High / 5 && Currentb->bullet_X >= b.boss_X && Currentb->bullet_X <= b.boss_X + 250 && Currentb->bullet_Y >= b.boss_Y && Currentb->bullet_Y <= b.boss_Y + 235)
		{
			b.boss_HP -= this->bullet_Att;

			if (b.boss_HP <= 0)
			{
				mciSendString(_T("close bsdmusic"), NULL, 0, NULL);
				mciSendString(_T("open data\\audio\\boss_defeated.mp3 alias bsdmusic"), NULL, 0, NULL);
				mciSendString(_T("play bsdmusic"), NULL, 0, NULL);//����һ�α�ը��Ч

				KillNum++;//����л�������1
				KillScore += 5000;
			}
			Currentb->isext = false;
		}
		Currentb = Currentb->Next;
	}

	Currentb = TempHead;

	if (b.boss_HP > 0 && b.boss_Y >= High / 5 && this->char_X >= b.boss_X - 110 && this->char_X <= b.boss_X + 230 && this->char_Y >= b.boss_Y + 5 && this->char_Y <= b.boss_Y + 220)
	{//��BOSS01��ײ���ж�
		this->char_HP -= b.boss_Att;
		mciSendString(_T("close bt1music"), NULL, 0, NULL);
		mciSendString(_T("open data\\audio\\bomb.mp3 alias bt1music"), NULL, 0, NULL);
		mciSendString(_T("play bt1music"), NULL, 0, NULL);//����һ�α�ը��Ч
	}

	Currente = TempHead2;
	while (Currente)
	{
		if (Currente->enemy_HP > 0 && this->char_X > Currente->enemy_X - 20 && this->char_X < Currente->enemy_X + 75 && this->char_Y> Currente->enemy_Y - 65 && this->char_Y < Currente->enemy_Y + 100)
		{
			if (Currente->Type == 1)
			{
				KillScore += 50;
                this->char_HP -= 100;  //�͵���01һ������ײ�˺�
			}
			else if (Currente->Type == 2)
			{
			KillScore += 60;
			this->char_HP -= 165;  //�͵���01��������ײ�˺�
			}
			else if (Currente->Type == 3)
			{
			KillScore += 70;
			this->char_HP -= 135;  //�͵���01��������ײ�˺�
			}

			Currente->ifblast = 0;  //׼�����ű�ը����
			Currente->enemy_HP -=999999;
			KillNum++;//��ײ��л�ֱ������ ����л���+1

			mciSendString(_T("close bt1music"), NULL, 0, NULL);
			mciSendString(_T("open data\\audio\\bomb.mp3 alias bt1music"), NULL, 0, NULL);
			mciSendString(_T("play bt1music"), NULL, 0, NULL);//����һ�α�ը��Ч
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
				b.ifB_Asec = 0;  //���ڼ�¼��һ�ֵ�ʱ��

				b.blast_j++;     //����++  ������һ��ͼ

				if (b.blast_j == 4)  //һ�в������  �������� ����++
				{
					b.blast_j = 0;
					b.blast_i++;
				}

				if (b.blast_i == 4)  //�����ж��������ʱ
				{
					b.ifblast = 1;  //ֹͣ���Ŷ���

					b.B_Lsec = 0;             //����ǰ��ʱ��
					b.B_Asec = 0;             //���ú���ʱ��
					b.ifB_Lsec = 0;           //�����ж�ǰ��ʱ���Ƿ��Ѿ���¼
					b.ifB_Asec = 0;			  //�����жϺ���ʱ���Ƿ��Ѿ���¼
					b.blast_i = 0;            //���û�������
					b.blast_j = 0;            //���û�������
				}
			}
		}
	}
}

void IDN::blast_enemy(Enemy01*& Temp)
{
	Enemy01* Current = Temp;//��¼ͷ�ڵ�λ��

	while (Current)
	{
		double X = Current->enemy_X;
		double Y = Current->enemy_Y;

		if (Current->ifblast == 0)
		{
			if (Current->ifB_Lsec == 0)  //��ȡ��ʼ������
			{
				Current->B_Lsec = ti.wMilliseconds;
				Current->ifB_Lsec = 1;
			}

			if (Current->ifB_Asec == 0)
			{
				Current->B_Asec = ti.wMilliseconds; //��ȡ��ֹ����
				putimage(X, Y, 128, 128, &blast_zz, Current->blast_j * 127, Current->blast_i * 127, NOTSRCERASE);
				putimage(X, Y, 128, 128, &blast, Current->blast_j * 127, Current->blast_i * 127, SRCINVERT);
				if ((Current->B_Asec - Current->B_Lsec >= 3 && Current->B_Asec > Current->B_Lsec) || (Current->B_Asec - Current->B_Lsec + 1000 >= 3 && Current->B_Asec < Current->B_Lsec))
				{

					Current->ifB_Lsec = 0;
					Current->ifB_Asec = 0;  //���ڼ�¼��һ�ֵ�ʱ��

					Current->blast_j++;     //����++  ������һ��ͼ

					if (Current->blast_j == 4)  //һ�в������  �������� ����++
					{
						Current->blast_j = 0;
						Current->blast_i++;
					}

					if (Current->blast_i == 4)  //�����ж��������ʱ
					{
						Current->ifblast = 1;  //ֹͣ���Ŷ���
						Current->stoexist = 0;  //����״̬Ϊ����Ӧ�ô��ڡ� �漴��ɾ��
					}
				}
			}
		}
		Current = Current->Next;
	}
	
}

void IDN::eat_item01(Cloud*& TempHead, Cloud*& TempTail)
{
	//�����������ø��ֵ��ߵ�Ч��
	Cloud* Current = TempHead;

	while (Current)
	{
		double iX = Current->cloud_X + 40;
		double iY = Current->cloud_Y + 40;
		double distance = (this->char_X + 50 - iX) * (this->char_X + 50 - iX) + (this->char_Y + 50 - iY) * (this->char_Y + 50 - iY);

		if (distance <= 3600)
		{
			Current->isext = false;
			if (Current->type == 1)  //�жϵ�������1
			{

				mciSendString(_T("close lfmusic"), NULL, 0, NULL);
				mciSendString(_T("open data\\audio\\life.mp3 alias lfmusic"), NULL, 0, NULL);
				mciSendString(_T("play lfmusic"), NULL, 0, NULL);//����һ����Ч

				if (this->char_HP + FullHP * 0.25 <= FullHP)//��Ѫ�ж�
				{
					this->char_HP += FullHP * 0.25;  //�ظ�4��֮1��Ѫ��
				}
				else
				{
					this->char_HP = FullHP;
				}
			}
			else if (Current->type == 2)  //�жϵ�������2
			{
				FullScore += 5;  //���ӵ�ҩ����
				ArmScore += 1;   //���ӵ�ҩ�ظ���
				this->bullet_Att += 25;  //���ӹ�����
				if (this->bullet_Att >= 200 && bret == 1) //���������ﵽ200���ӵ���̬�����仯
				{
					btype = 2;  //��̬����Ϊ2
					bret = 0;   //�Ƿ�仯����Ϊ���ѱ仯��(��0��1Ϊδ�仯)

					mciSendString(_T("close apmusic"), NULL, 0, NULL);
					mciSendString(_T("open data\\audio\\armup.mp3 alias apmusic"), NULL, 0, NULL);
					mciSendString(_T("play apmusic"), NULL, 0, NULL);//����һ����Ч
				}
				else
				{
					mciSendString(_T("close ammusic"), NULL, 0, NULL);
					mciSendString(_T("open data\\audio\\arm.mp3 alias ammusic"), NULL, 0, NULL);
					mciSendString(_T("play ammusic"), NULL, 0, NULL);//����һ����Ч

				}
				
			}
			else if (Current->type == 3)  //�жϵ�������3
			{
				this->char_HP += 65;  //����Ѫ������
				FullHP += 65;         //������Ӧ���ӵ�Ѫ��
				score = FullScore;    //���Ҳ�����ҩ

				mciSendString(_T("close lpmusic"), NULL, 0, NULL);
				mciSendString(_T("open data\\audio\\levelup.mp3 alias lpmusic"), NULL, 0, NULL);
				mciSendString(_T("play lpmusic"), NULL, 0, NULL);//����һ����Ч
			}
		}
		Current = Current->Next;
	}
}

void IDN::boss_01(Boss01& b, BossBlt*& BBHead, BossBlt*& BBTail)
{
	if (KillScore > SHOW_BOSS01)
	{
		if (KillScore > SHOW_BOSS01*4 && ifBoss2==0) //��Boss�ڶ��γ��ֵ��ж�����
		{
			b.boss_HP = BOSSHP * 5.0;  //�ڶ��γ���100000Ѫ��
			b.boss_attspeed--;         //����Ƶ�ʼӿ�
			b.boss_Att = 50;           //�����˺�����
			ifBoss2 = 1;
			ifBossSe = 1;

			b.ifblast = 0;             //׼�����Ŷ���
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
			
			if (b.boss_AttType == 0)//����BOSS��ͼƬ
			{
				putimage(b.boss_X, b.boss_Y, &boss01_zz, NOTSRCERASE);
				putimage(b.boss_X, b.boss_Y, &boss01, SRCINVERT);
			}
			else if (b.boss_AttType == 1 || b.boss_AttType == 10)
			{
				putimage(b.boss_X, b.boss_Y, &boss01_att01_zz, NOTSRCERASE);
				putimage(b.boss_X, b.boss_Y, &boss01_att01, SRCINVERT);
			}

			if (b.boss_Y <= High / 5)  //BOSS�����ƶ���ָ��λ��
			{
				
				b.boss_Y += b.boss_speed;
			}


			if (b.boss_Y > High / 5)   //BOSS�ƶ���ָ��λ��֮��
			{

				if (ifLsec == 0) //��ȡ��ʼʱ��
				{
					Lsec = ti.wSecond;
					ifLsec = 1;
				}

				if (ifAsec == 0)
				{
					Asec = ti.wSecond;  //��ȡ��ǰʱ��

					if (Asec > Lsec)
					{
						if (Asec - Lsec == b.boss_attspeed)
						{
							ifAsec = 1;
							b.boss_AttType = 1;  //BOSS��Ϊ  ����ҲҪ��
						}
					}
					else
					{
						if (Asec + 60 - Lsec == b.boss_attspeed)
						{
							ifAsec = 1;
							b.boss_AttType = 1;  //BOSS��Ϊ  ����ҲҪ��
						}
					}
				}

				if (boss_mp3 == 1)   //����һ��BOSS������Ч
				{
					mciSendString(_T("close bsmusic"), NULL, 0, NULL);
					mciSendString(_T("open data\\audio\\boss.mp3 alias bsmusic"), NULL, 0, NULL);
					mciSendString(_T("play bsmusic"), NULL, 0, NULL);//����һ����Ч
					boss_mp3 = 0;
				}


				if (b.boss_AttType == 0) //BOSS�����ƶ�
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

				if (b.boss_AttType == 1)  //BOss������ʽ1����ײ
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
				else if (b.boss_AttType == 10)  //��ײ���� ����
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

			Lsec = 0;               //ǰ��ʱ��
			Asec = 0;               //����ʱ��
			ifLsec = 0;             //0��ʾ��δ��ȡʱ��
			ifAsec = 0;

			BBHead = NULL;         //�����ӵ���


			//b.ifblast = 0;            //��ը  1Ϊ��Ӧ�� 0Ϊ������ը

			
		}

		
	}
}

void IDN::save_score()
{	
	for (int iii = 0; iii < 9; iii++) //��ʾ֮ǰ�ȶ����з�������
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
	}//�����Ѿ��Ӵ�С�������

	int temp_i = -1;

	for (int iii = 0; iii < 10; iii++)//һһ�Ƚ��жϷ����ܷ����ǰʮ��
	{
		if (KillScore > SCORE[iii])
		{
			temp_i = iii;           //��¼λ��
			break;                  //Ȼ���˳�ѭ��
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

	for (int iii = 0; iii < 9; iii++) //�����з�������
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
	}//�����Ѿ��Ӵ�С�������
}

void IDN::score_list()
{
	cleardevice();
	putimage(0, 0, &list);

	char S1[50];
	for (int i = 0; i < 10; i++)  //ѭ����ӡ����
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



	if (GetAsyncKeyState(VK_ESCAPE)) //Ҳ����ͨ��ESC������
	{
		this->which = 0;
	}

	MOUSEMSG m;
	while (MouseHit())  //�ж�����Ƿ��ж���
	{
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN)//����������ʱ
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
		mciSendString(_T("open data\\audio\\bgm.mp3 alias bkmusic"), NULL, 0, NULL);//��������
		mciSendString(_T("play bkmusic repeat"), NULL, 0, NULL);
		Main_music = 0;
	}
	else if(map01_music==1)
	{
		mciSendString(_T("close bkmusic"), NULL, 0, NULL);
		mciSendString(_T("open data\\audio\\map01.mp3 alias mp1music"), NULL, 0, NULL);//��������
		mciSendString(_T("play mp1music repeat"), NULL, 0, NULL);
		map01_music = 0;
	}
	else if (map02_music == 1)
	{
		mciSendString(_T("close bkmusic"), NULL, 0, NULL);
		mciSendString(_T("open data\\audio\\map02.mp3 alias mp2music"), NULL, 0, NULL);//��������
		mciSendString(_T("play mp2music repeat"), NULL, 0, NULL);
		map02_music = 0;
	}
	else if (map03_music == 1)
	{
		mciSendString(_T("close bkmusic"), NULL, 0, NULL);
		mciSendString(_T("open data\\audio\\map03.mp3 alias mp3music"), NULL, 0, NULL);//��������
		mciSendString(_T("play mp3music repeat"), NULL, 0, NULL);
		map03_music = 0;
	}


	//��β
	Sleep(10);
	FlushBatchDraw();
}