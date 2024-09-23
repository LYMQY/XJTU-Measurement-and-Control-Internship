#include <windows.h>
#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include "winio.h"
#pragma comment(lib,"winio.lib")
using namespace std;

unsigned short BASE_ADDRESS = 0xE880;
int iPort=16,i,st,stp,temp2=1;
int DI[8]={0},DO[8]={0};
int flag=0;

void open(int flag);
void call1();
void call2();


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

void call1()
{
	for(int j=0;j<=7;j++)
		DO[j]=0;
	DO[3]=1;
	DO[0]=1;
	_outp(BASE_ADDRESS + iPort,creat_DO());
	int temp1=1;
	while(1)
	{
		//cout<<"2 to 1"<<endl;
		DO[5]=1;//ground1
		_outp(BASE_ADDRESS + iPort,creat_DO());//down
		Sleep(50);
		DO[5]=0;
		_outp(BASE_ADDRESS + iPort,creat_DO());
		Sleep(50);
		
		system("cls");
		int DI_data = _inp(BASE_ADDRESS + iPort);
  		creat_DI(DI_data);
		//cout<<"arrive1"<<endl;
		if(DI[3]<temp1)break;//dao da
	}//down

	for( j=0;j<=7;j++)
		DO[j]=0;
	DO[0]=1;
	DO[3]=1;
	int DI_data = _inp(BASE_ADDRESS + iPort);
  	creat_DI(DI_data);
	_outp(BASE_ADDRESS + iPort,creat_DO());

	while(1)
	{
	    int DI_data = _inp(BASE_ADDRESS + iPort);
  		creat_DI(DI_data);
		if(DI[5]<temp1)break;
		if(DI[1]<temp1)call2();
	}
	flag=0;
	open(flag);//open

	int timebegin=clock();
	int timeover;
	for(j=0;j<=7;j++)
		DO[j]=0;
	DO[3]=1;//opened
	while(timeover-timebegin<5000)
	{	
		_outp(BASE_ADDRESS + iPort,creat_DO());
		timeover=clock();
		int DI_data = _inp(BASE_ADDRESS + iPort);
  		creat_DI(DI_data);
		if(DI[4]<temp1)break;
	}
	for(j=0;j<=7;j++)
		DO[j]=0;
	DO[3]=1;
	while(1)
	{
		DO[4]=1;
		_outp(BASE_ADDRESS + iPort,creat_DO());
		Sleep(50);
		DO[4]=0;
		_outp(BASE_ADDRESS + iPort,creat_DO());
		Sleep(50);
		int DI_data = _inp(BASE_ADDRESS + iPort);
  		creat_DI(DI_data);
		if(DI[3]<temp1)break;
	}
	for(j=0;j<=7;j++)
		DO[j]=0;
	DO[3]=1;
	DO[1]=1;
	_outp(BASE_ADDRESS + iPort,creat_DO());
}

void call2()
{
	for(int j=0;j<=7;j++)
		DO[j]=0;
	DO[3]=1;
	DO[1]=1;
	_outp(BASE_ADDRESS + iPort,creat_DO());
	int temp=1;
	while(1)
	{
		DO[4]=1;
		_outp(BASE_ADDRESS + iPort,creat_DO());
		Sleep(50);
		DO[4]=0;
		_outp(BASE_ADDRESS + iPort,creat_DO());
		Sleep(50);
		int DI_data = _inp(BASE_ADDRESS + iPort);
  		creat_DI(DI_data);
		if(DI[2]<temp)break;
	}//down
	for( j=0;j<=7;j++)
		DO[j]=0;
	DO[1]=1;
	DO[3]=1;
	_outp(BASE_ADDRESS + iPort,creat_DO());

	while(1)
	{
	    int DI_data = _inp(BASE_ADDRESS + iPort);
  		creat_DI(DI_data);
		if(DI[5]<temp)break;
		if(DI[0]<temp)call1();
	}
	flag=1;
	open(flag);

	int timebegin=clock();
	int timeover;
	for(j=0;j<=7;j++)
		DO[j]=0;
	DO[3]=1;
	while(timeover-timebegin<5000)
	{	
		_outp(BASE_ADDRESS + iPort,creat_DO());
		timeover=clock();
		int DI_data = _inp(BASE_ADDRESS + iPort);
  		creat_DI(DI_data);
		if(DI[4]<temp)break;
	}
	for(j=0;j<=7;j++)
		DO[j]=0;
	DO[3]=1;
	while(1)
	{
		DO[5]=1;//down
		_outp(BASE_ADDRESS + iPort,creat_DO());
		Sleep(50);
		DO[5]=0;
		_outp(BASE_ADDRESS + iPort,creat_DO());
		Sleep(50);
		int DI_data = _inp(BASE_ADDRESS + iPort);
  		creat_DI(DI_data);
		if(DI[2]<temp)break;//arrived
	}
	for(j=0;j<=7;j++)
		DO[j]=0;
	DO[1]=1;
	DO[3]=1;
	_outp(BASE_ADDRESS + iPort,creat_DO());
}

void open(int flag)
{
	int st = clock();
	while(stp - st < 2500){
		for(int j=0;j<=7;j++)DO[j]=0;
		DO[2]=1;
		DO[flag]=1;
		_outp(BASE_ADDRESS + iPort,creat_DO());
		int DI_data = _inp(BASE_ADDRESS + iPort);
  		creat_DI(DI_data);
		if(DI[4]<1)break;
	}
	if(flag == 0)
	{
		call2();
	}else
	{
		call1();
	}
}


void main(void)
{

	cout<<"按P退出"<<endl;
// 初始化WinIO 
	
	if (!InitializeWinIo())
	{
		cout<<"Error In InitializeWinIo!"<<endl;
		exit(1);
	}


//数字量输入


	int DI_data,temp=1;

   while(1)
   {
	   DI_data = _inp(BASE_ADDRESS + iPort);
	   creat_DI(DI_data);
	   for(int j=0;j<=7;j++)
			DO[j]=0;
	   DO[3]=1;
	   DO[flag]=1;
	   _outp(BASE_ADDRESS + iPort,creat_DO());	
	   if(DI[0]<temp&&flag)call1();
	   if(DI[1]<temp&&!flag)call2();
	   if(DI[5]<temp)open(flag);
		if(kbhit())
		{
			char c=getch();
			if(c=='p'||c=='P')
			{exit(0);
			ShutdownWinIo();}
		}
    }		//关闭WinIO							
}