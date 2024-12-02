#include <windows.h>
#include <iostream>
#include <conio.h>
#include "winio.h"

unsigned short BASE_ADDRESS = 0xE880;
int iPort=16;
int DI[8]={0},DO[8]={0};

#pragma comment(lib,"winio.lib")
using namespace std;


void mode1();
void mode2();
void mode3();
void mode4();

int creat_DI(int num)
{
  	int i=0;
  	for(i=0;i<8;i++)
   	DI[i]=(num>>i)&0x0001;
  	return 0;
}

int creat_DO()
{
  	int temp=0;
    int i=0;
	for(i=7;i>0;i--)
	{
		temp=(temp+DO[i])*2;
	}
	return temp+DO[0];
}



void mode1()
{
	unsigned short BASE_ADDRESS = 0xE880;
	while(1)
	{
		for(int i=0;i<=7;i++)
		{
			int temp0=DI[0];
			int temp1=DI[1];
			int temp2=DI[2];
			int temp3=DI[3];
			for(int j=0;j<=7;j++)//st
				DO[j]=0;
			DO[i]=1;
			_outp(BASE_ADDRESS + iPort,creat_DO());
			Sleep(500);//stp
			
			if(kbhit())
			{
				char c=getch();
				if(c=='p'||c=='P')
				{exit(0);
				ShutdownWinIo();}
			}
			int DI_data = _inp(BASE_ADDRESS + iPort);
  			creat_DI(DI_data);
			if(DI[0]<temp0)
				mode1();
			if(DI[1]<temp1)
				mode2();
			if(DI[2]<temp2)
				mode3();
			if(DI[3]<temp3)
				mode4();
		}
			
	}
	
}

void mode2()
{
	unsigned short BASE_ADDRESS = 0xE880;
	while(1)
	{
		for(int j=0;j<=7;j++)
				DO[j]=0;
		for(int i=0;i<=15;i++)
		{
			int temp0=DI[0];
			int temp1=DI[1];
			int temp2=DI[2];
			int temp3=DI[3];
			if(i<8)
			DO[i]=!DO[i];//st
			else if(i>7)
			DO[15-i]=!DO[15-i];
			_outp(BASE_ADDRESS + iPort,creat_DO());
			Sleep(500);//stp
			
			if(kbhit())
			{
				char c=getch();
				if(c=='p'||c=='P')
					{exit(0);
				ShutdownWinIo();}

			}
			int DI_data = _inp(BASE_ADDRESS + iPort);
  			creat_DI(DI_data);
			if(DI[0]<temp0)
				mode1();
			if(DI[1]<temp1)
				mode2();
			if(DI[2]<temp2)
				mode3();
			if(DI[3]<temp3)
				mode4();
		}
	}
}

void mode3()
{
	unsigned short BASE_ADDRESS = 0xE880;
	while(1)
	{
		for(int i=0;i<=3;i++)
		{
			int temp0=DI[0];
			int temp1=DI[1];
			int temp2=DI[2];
			int temp3=DI[3];
			for(int j=0;j<=7;j++)//st
				DO[j]=0;
			if(i==0)
			{DO[0]=1;
			Beep(392,100);
			}
			else if(i==1)
			{DO[2]=1;Beep(296,100);}
			else if(i==2)
			{DO[1]=1;Beep(349,100);}
			else if(i==3)
			{DO[2]=1;Beep(296,100);}
			_outp(BASE_ADDRESS + iPort,creat_DO());
			Sleep(500);//stp
			
			if(kbhit())
			{
				char c=getch();
				if(c=='p'||c=='P')
				{exit(0);
				ShutdownWinIo();}
			}
			int DI_data = _inp(BASE_ADDRESS + iPort);
  			creat_DI(DI_data);
			if(DI[0]<temp0)
				mode1();
			if(DI[1]<temp1)
				mode2();
			if(DI[2]<temp2)
				mode3();
			if(DI[3]<temp3)
				mode4();
		}
			
	}
}

void mode4()
{
	unsigned short BASE_ADDRESS = 0xE880;
	while(1)
	{
		for(int i=0;i<=14;i++)
		{
			int temp0=DI[0];
			int temp1=DI[1];
			int temp2=DI[2];
			int temp3=DI[3];
			for(int j=0;j<=7;j++)//st
				DO[j]=0;
			if(i==0)
			{DO[0]=1;
			Beep(392,100);
			}
			else if(i==1)
			{DO[1]=1;Beep(400,100);}
			else if(i==2)
			{DO[2]=1;Beep(523,100);}
			else if(i==3)
			{DO[3]=1;Beep(523,100);}
			else if(i==4)
			{DO[4]=1;Beep(400,100);}
			else if(i==5)
			{DO[5]=1;Beep(784,200);}
			else if(i==6)
			{DO[6]=1;Beep(659,200);}
			else if(i==7)
			{DO[7]=1;Beep(659,400);}
			else if(i==8)
			{DO[6]=1;Beep(440,100);}
			else if(i==9)
			{DO[5]=1;Beep(440,100);}
			else if(i==10)
			{DO[4]=1;Beep(440,100);}
			else if(i==11)
			{DO[3]=1;Beep(440,100);}
			else if(i==12)
			{DO[2]=1;Beep(440,200);}
			else if(i==13)
			{DO[1]=1;Beep(392,200);}
			else if(i==14)
			{DO[0]=1;Beep(392,200);}
			_outp(BASE_ADDRESS + iPort,creat_DO());
			Sleep(100);//stp
			
			if(kbhit())
			{
				char c=getch();
				if(c=='p'||c=='P')
				{exit(0);
				ShutdownWinIo();}
			}
			int DI_data = _inp(BASE_ADDRESS + iPort);
  			creat_DI(DI_data);
			if(DI[0]<temp0)
				mode1();
			if(DI[1]<temp1)
				mode2();
			if(DI[2]<temp2)
				mode3();
			if(DI[3]<temp3)
				mode4();
		}
	}
}


void main()
{
	char c;
	


// 初始化WinIO 
	
	if (!InitializeWinIo())
	{
		cout<<"Error In InitializeWinIo!"<<endl;
		exit(1);
	}


//数字量输入


	int temp0=1,temp1=1,temp2=1,temp3=1;
	int DI_data;
	while(1)
	{
	DI_data = _inp(BASE_ADDRESS + iPort);
  	creat_DI(DI_data);
	if(DI[0]<temp0)
	{
		mode1();
	}
	if(DI[1]<temp1)
	{
		mode2();
	}
	if(DI[2]<temp2)
	{
		mode3();
	}
	if(DI[3]<temp3)
	{
		mode4();
	}
	Sleep(100);
  	system("cls");
  	cout<<"按P退出"<<endl;
	}
 		//关闭WinIO							
}