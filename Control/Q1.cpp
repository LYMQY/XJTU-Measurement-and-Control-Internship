// ��������������.
#include <windows.h>
#include <iostream>
#include <conio.h>
#include "winio.h"


#pragma comment(lib,"winio.lib")
using namespace std;


int creat_DI(int (&DI_bit)[8], int num)
{
  	int i=0;
  	for(i=0;i<8;i++)
   	DI_bit[i]=(num>>i)&0x0001;
  	return 0;
}

int creat_DO(int (&DI_bit)[8],int judge)
{
  	int temp=0;
	for(int i=0;i<7;i++)
	{
		temp=2*(DI_bit[i]+temp);
	}
	temp=temp+DI_bit[7];
	if(!judge)
		return temp;
	else
		return ~temp;
}


void main(void)
{
	char c;
	unsigned short BASE_ADDRESS = 0xE880;
	int iPort=16;
	


	// ��ʼ��WinIO 
	
	if (!InitializeWinIo())
	{
		cout<<"Error In InitializeWinIo!"<<endl;
		exit(1);
	}


	//����������


	int i,judge=0;
	int DI_data,DO_data,tempDI=255;
	int DI[8]={0};
	cout<<"��ǰģʽ��ͬ��"<<endl;
   while(1)
   {
	DI_data = _inp(BASE_ADDRESS + iPort);
	if(tempDI!=DI_data)
		system("cls");
	
	creat_DI(DI,DI_data);
	DO_data=creat_DO(DI,judge);
	_outp(BASE_ADDRESS + iPort,DO_data);
	Sleep(10);
	if(tempDI!=DI_data)
	{
  		for(i=0;i<8;i++)
		{
			cout<<"DI_"<<i+1<<"="<<DI[i]<<endl;
		}
		if(!judge)
			cout<<"��ǰģʽ��ͬ��"<<endl;
		else
			cout<<"��ǰģʽ������"<<endl;
  		cout<<"��P�˳�����R�л�ģʽ"<<endl;
	}
	tempDI=DI_data;
  	if(kbhit())
	{
		c=getch();
		if(c=='r'||c=='R')
		{
			judge=1-judge;
			system("cls");  //�л�ģʽ
		for(i=0;i<8;i++)
		{
			cout<<"DI_"<<i+1<<"="<<DI[i]<<endl;
		}
			if(!judge)
			cout<<"��ǰģʽ��ͬ��"<<endl;
		else
			cout<<"��ǰģʽ������"<<endl;
		cout<<"��P�˳�����R�л�ģʽ"<<endl;
		}
		else if(c=='p'||c=='P')
		{
			_outp(BASE_ADDRESS + iPort,0);
			break;
		}
	}
  	
	   
   
   }
    ShutdownWinIo();		//�ر�WinIO							
}