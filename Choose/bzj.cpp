// 包装机
#include <windows.h>
#include <iostream>
#include <conio.h>
#include "winio.h"

unsigned short BASE_ADDRESS = 0xE880;
int iPort=16;
int DI[8]={0},DO[8]={0};

#pragma comment(lib,"winio.lib")
using namespace std;

int temp0=1;
int DI_data;
int count=0;
void mode2();

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

void packing()
{
	unsigned short BASE_ADDRESS = 0xE880;
	for(int j=0;j<=7;j++)
			DO[j]=0;
	for(int i=0;i<=7;i++)
	{
		DI_data = _inp(BASE_ADDRESS + iPort);
  		creat_DI(DI_data);
		if(DI[0]<temp0)
		{
			system("cls");
			count++;
			cout<<"Current number:"<<count;
			Sleep(200);
		}
		DO[i]=1;//st
		_outp(BASE_ADDRESS + iPort,creat_DO());
		Sleep(200);//stp
		DI_data = _inp(BASE_ADDRESS + iPort);
  		creat_DI(DI_data);
		if(DI[0]<temp0)
		{
			system("cls");
			count++;
			cout<<"Current number:"<<count;
			Sleep(200);
		}
		if(kbhit())
		{
			char c=getch();
			if(c=='p'||c=='P')
			{
				exit(0);
				ShutdownWinIo();
			}
		}
	}
	
	for(j=0;j<=7;j++)
			DO[j]=0;
	_outp(BASE_ADDRESS + iPort,creat_DO());
}

void main()
{
	char c;
	


	// ��ʼ��WinIO 
	
	if (!InitializeWinIo())
	{
		cout<<"Error In InitializeWinIo!"<<endl;
		exit(1);
	}


	//����������

	

	while(1)
	{
		DI_data = _inp(BASE_ADDRESS + iPort);
  		creat_DI(DI_data);
		if(DI[0]<temp0)
		{
			count++;
			Sleep(200);
		}
		cout<<"current number:"<<count<<endl;
		if(count%10==0 && count >= 10)
		{
			packing();
			count-=10;
		}
		Sleep(100);
  		system("cls");
  		cout<<"��P�˳�"<<endl;
	}
 	//�ر�WinIO							
}