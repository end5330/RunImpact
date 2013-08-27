#include<stdio.h>
#include<conio.h>
#include<windows.h>
#include<time.h>
#include <mmsystem.h>
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? true : false)

int spd_cnt,score,level_ip,ip_max,ip,tmp_ip,time_ip,tmp_use_ip,tmp_run_ip,time_use_ip,jmp,tmp_1,tmp_2,v_0,tmp_jmp,tmp_spd,spd,x,y,dir,exp,spd_l,map[8][33],color[4][2]={{15,15},{7,6},{0,7},{8,0}},level,lev_up[15]={10,200,300,400,500,500,500,500},lev_word[15][4]={{50,50},{40,60},{30,70},{30,50,20},{30,30,30,10},{30,15,40,15},{30,15,35,20},{30,5,45,20}},lev_spd[15]={800,600,500,400,350,300,250,200};
char word[4][3]={{"  "},{"¢Æ"},{"¢É"},{"¢Ì"}},me[2][3]={{"¢¸"},{"¢º"}};
bool ip_mode,ck_jmp,ck_spd,ck_ip,ck_stop,spd_act;

#pragma comment(lib,"winmm.lib")
MCI_OPEN_PARMS mciOpen;
MCI_PLAY_PARMS mciPlay;
int dwID[10],time_music;
char fileName[10][30]={
	"impact.mp3",
		"level1.mp3",
		"level2.mp3",
		"level3.mp3",
		"level4.mp3",
		"level5.mp3",
		"level6.mp3",
		"level7.mp3",
		"levelup.mp3"
};
void PlayMusic(int i)
{
	mciOpen.lpstrElementName=fileName[i];
	mciOpen.lpstrDeviceType="mpegvideo";
	mciSendCommand(NULL,MCI_OPEN,MCI_OPEN_ELEMENT|MCI_OPEN_TYPE,(DWORD)(LPVOID)&mciOpen);
	dwID[i]=mciOpen.wDeviceID;
	mciSendCommand(dwID[i],MCI_PLAY,MCI_NOTIFY,(DWORD)&mciPlay);
}
void StopMusic(int i)
{
	mciSendCommand(dwID[i],MCI_CLOSE,0,NULL);
}
void gotoxy(int gox,int goy)
{
	HANDLE hOut;
	COORD Cur;
	hOut=GetStdHandle(STD_OUTPUT_HANDLE);
	Cur.X=gox;
	Cur.Y=goy;
	SetConsoleCursorPosition(hOut,Cur);
}
void SetColor(int color,int bgcolor)
{
	bgcolor&=0xf;
	color&=0xf;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),color|(bgcolor<<4));
}
void Nocursor()
{
	CONSOLE_CURSOR_INFO CurInfo;
	CurInfo.dwSize=1;
	CurInfo.bVisible=FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&CurInfo);
}
void print_me()
{
	gotoxy(2+y*2,4+x);
	SetColor(0,15);
	printf("%s",me[dir]);
}
void delete_me()
{
	gotoxy(2+y*2,4+x);
	SetColor(0,15);
	printf("  ");
}
void print_map(int t_x,int t_y)
{
	gotoxy(2+t_y*2,4+t_x);
	if(ip_mode&&map[t_x][t_y]==0)
	{
		SetColor(0,0);
	}
	else
	{
		SetColor(color[map[t_x][t_y]][0],color[map[t_x][t_y]][1]);
	}
	printf("%s",word[map[t_x][t_y]]);
}
void up(int t_x,int t_y)
{
	if(map[t_x][t_y]!=0)
	{
		score+=map[t_x][t_y]*(y>=24?2:1);
		gotoxy(43,13);
		SetColor(0,15);
		printf("%d",score);
		map[t_x][t_y]=0;
		if(!ip_mode)
		{
			exp++;
			if(exp>=lev_up[level])
			{
				exp=0;
				if(level!=0)
				{
					StopMusic(level);
				}
				if(level<7)
				{
					level++;
					StopMusic(8);
					PlayMusic(8);
					SetColor(0,level+(spd_act?8:0));
					gotoxy(0,0);
					printf("                                                                    ");
					printf("                                                                    ");
					printf("                                                                    ");
					gotoxy(0,15);
					printf("                                                                    ");
					printf("                                                                    ");
					printf("                                                                   ");
				}
				PlayMusic(level);
				gotoxy(63,13);
				SetColor(0,15);
				printf("%d",level);
				ip=ip_max=100;
				ip_mode=true;
				level_ip=3;
			}
		}
	}
}