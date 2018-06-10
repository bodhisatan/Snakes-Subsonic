#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>

#define LEN 30
#define WID 25

int Snake[LEN][WID]={0};
char Sna_Hea_Dir='a';
char Sna_Hea_X,Sna_Hea_Y;
int Snake_Len=3;
clock_t Now_Time;
int Wait_Time;
int Eat_Apple=1;
int Level;
int All_Score=-1;
int Apple_Num=-1;

HANDLE hConsole=GetStdHandle(STD_OUTPUT_HANDLE);

void gotoxy(int x,int y)
{
	COORD pos={x,y};
	SetConsoleCursorPosition(hConsole,pos);

}

void Hide_Cursor()
{
	CONSOLE_CURSOR_INFO cursor_info={1,0};
	SetConsoleCursorInfo(hConsole,&cursor_info);
}

void SetColor(int color)
{
	SetConsoleTextAttribute(hConsole,color);
}

void Print_Snake()
{
	int ix,iy,color;
	for(int iy=0;iy<WID;++iy)
	for(int ix=0;ix<LEN;++ix)
	{
		if(Snake[ix][iy]==1)
		{
			SetColor(0xf);
			gotoxy(ix*2,iy);
			printf("@");
		}
		if(Snake[ix][iy]==2)
		{
			color=rand()%15+1;
			if(color==14) color-=rand()%13+1;
		    SetColor(color);
		    gotoxy(ix*2,iy);
		    printf("#");
		}
		if(Snake[ix][iy]==Snake_Len)
		{
			gotoxy(ix*2,iy);
			SetColor(0xe);
			printf("=");
		}
	}
}

void Clear_Snake()
{
	int iy,ix;
	for(int iy=0;iy<WID;++iy)
	for(int ix=0;ix<LEN;++ix)
	{
		gotoxy(ix*2,iy);
		if(Snake[ix][iy]==Snake_Len)  printf(" ");
	}
}

void Rand_Apple()
{
	int ix,iy;
	do
	{
		ix=rand()%LEN;
		iy=rand()%WID;
	}
	while(Snake[ix][iy]);
	Snake[ix][iy]=-1;
	gotoxy(ix*2,iy);
	printf("*");
	Eat_Apple=0;
}

void Game_Over()
{
	gotoxy(30,10);
	printf("Game Over");
	Sleep(3000);
	system("pause>nul");
	exit(0);
}

void Move_Snake()
{
	int ix,iy;
	for(ix=0;ix<LEN;++ix)
	for(iy=0;iy<WID;++iy)
	if(Snake[ix][iy]==1)
	{
		switch(Sna_Hea_Dir)
		{
			case 'w':
				if(iy==0)  Game_Over();
				else
				Sna_Hea_Y=iy-1;
				Sna_Hea_X=ix;
				break;
			case 's':
				if(iy==(WID-1))  Game_Over();
				else
				Sna_Hea_Y=iy+1;
				Sna_Hea_X=ix;
				break;
			case 'a':
				if(ix==0)  Game_Over();
				else
				Sna_Hea_X=ix-1;
				Sna_Hea_Y=iy;
				break;
			case 'd':
				if(ix==(LEN-1))  Game_Over();
				else
				Sna_Hea_X=ix+1;
				Sna_Hea_Y=iy;
				break;
			default:break;
		}
	}
	if(Snake[Sna_Hea_X][Sna_Hea_Y]!=1 && Snake[Sna_Hea_X][Sna_Hea_Y]!=0 && Snake[Sna_Hea_X][Sna_Hea_Y]!=-1)  Game_Over();
    if(Snake[Sna_Hea_X][Sna_Hea_Y]<0)
    {
    	++Snake_Len;
    	Eat_Apple=1;
	}
	for(ix=0;ix<LEN;++ix)
	for(iy=0;iy<WID;++iy)
	{
		if(Snake[ix][iy]>0)
		{
			if(Snake[ix][iy]!=Snake_Len)  Snake[ix][iy]++;
			else Snake[ix][iy]=0;
		}
	}
	Snake[Sna_Hea_X][Sna_Hea_Y]=1;
}

void Get_Input()
{
	if(kbhit())
	{
		switch(getch())
		{
			case 72:
				Sna_Hea_Dir='w';
				break;
			case 80:
				Sna_Hea_Dir='s';
				break;
			case 75:
				Sna_Hea_Dir='a';
				break;
			case 77:
				Sna_Hea_Dir='d';
				break;
			default:
				break;
		}
	}
	if(clock()-Now_Time>=Wait_Time)
	{
		Clear_Snake();
		Move_Snake();
		Print_Snake();
		Now_Time=clock();
	}
}

void Init()
{
	system("title For SAMA_Tang");
	system("mode con:cols=80 lines=25");
	Hide_Cursor();
	gotoxy(61,4);
	printf("You Score:");
	gotoxy(61,6);
	printf("You Level:");
	gotoxy(61,8);
	printf("The Length:");
	gotoxy(61,10);
	printf("The Speed:");
	gotoxy(61,12);
	printf("Apple Num:");
	int i;
	for(i=0;i<Snake_Len;++i)
	Snake[10+i][15]=i+1;
	int iy,ix;
	for(iy=0;iy<WID;++iy)
	for(ix=0;ix<LEN;++ix)
	{
		if(Snake[ix][iy])
		{
			SetColor(Snake[ix][iy]);
			gotoxy(ix*2,iy);
			printf("#");
		}
	}
}

void Pri_News()
{
	SetColor(0xe);
	gotoxy(73,4);
	All_Score+=Level;
	printf("%3d",All_Score);
	gotoxy(73,6);
	printf("%3d",Level);
	gotoxy(73,8);
	printf("%3d",Snake_Len);
	gotoxy(73,10);
	printf("0.%3ds",Wait_Time/10);
	gotoxy(73,12);
	printf("%d",Apple_Num);

}

void Lev_Sys()
{
	if(((Apple_Num-1)/10)==Level)
	{
		++Level;
		if(Wait_Time>50)  Wait_Time-=50;
		else
		if(Wait_Time>10)  Wait_Time-=10;
        else Wait_Time-=1;
    }
}

int main(void)
{
	Hide_Cursor();
	SetColor(0xe);
	srand((unsigned)time(NULL));
	Now_Time=clock();
	int speed1=1000,speed2,a;
	printf("\n");
	printf("Please input the speed you want\n");
	scanf("%d",&speed2);
	Level=1;
	Wait_Time=speed1-speed2;
	printf("Please input the amount of apples you want\n");
	scanf("%d",&a);
	system("cls");
	Init();
	while(a--)
	    Rand_Apple();
	while(1)
	{
		if(Eat_Apple)
		{
			++Apple_Num;
			Rand_Apple();
			Lev_Sys();
			Pri_News();
		}
		Get_Input();
		Sleep(10);
	}
	return 0;
}
