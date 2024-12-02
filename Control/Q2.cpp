#include <windows.h>
#include <iostream>
#include <conio.h>
#include "winio.h"
int max=99;
int count=50;

#pragma comment(lib,"winio.lib")
using namespace std;

int creat_DI(int (&DI_bit)[8], int num)
{
  	int i=0;
  	for(i=0;i<8;i++)
   	DI_bit[i]=(num>>i)&0x0001;
  	return 0;
}

int creat_DO(int count)
{
  	int a2,a1;
	a2=count/10;
	a1=count%10;
	return a2*16+a1;
}


void main(void)
{
	unsigned short BASE_ADDRESS = 0xE880;
	int iPort=16;
	


// 初始化WinIO 
	
	if (!InitializeWinIo())
	{
		cout<<"Error In InitializeWinIo!"<<endl;
		exit(1);
	}


//数字量输出


	int DO[8]={0};

	int DI_data;
	int DI[8]={0};
	
	cout<<"Current parking space occupied:"<<count<<endl;
	cout<<"Press P to quit!"<<endl;
	
	int temp=count;
   while(1)
   {
	if(count!=temp)
	{
		system("cls");
		cout<<"Current parking space occupied:"<<count<<endl;
		cout<<"Press P to quit!"<<endl;
	}
	temp=count;
	int tempin=DI[0],tempout=DI[7];
	DI_data = _inp(BASE_ADDRESS + iPort);
  	creat_DI(DI,DI_data);
	Sleep(100);
	if(DI[0]<tempin)
	{
		if(count<99)
		count++;
	}
	if(DI[7]<tempout)
	{
		if(count>0)
		count--;
	}
	int out=creat_DO(max-count);
	_outp(BASE_ADDRESS + iPort,out);
	if(kbhit())
	{
		char c=getch();
		if(c=='p'||c=='P')
			break;
	}
   }

   ShutdownWinIo();		//关闭WinIO							
}