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
int zhushui=3000,jinpao=5000,paishui=3000,xidi=15000,tuoshui=13000,piaoxi=14000,wancheng=5000,stop = 1000;




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

void d1()
{
	for(i=0;i<8;i++)
	{
		DO[i]=0;
	}
	while(1)
	{
		DO[0]=1;
		_outp(BASE_ADDRESS + iPort,creat_DO());
		Sleep(50);
		DO[0]=0;
		_outp(BASE_ADDRESS + iPort,creat_DO());
		Sleep(50);
		int DI_data = _inp(BASE_ADDRESS + iPort);
  		creat_DI(DI_data);
		if(DI[2]<temp2)
		{
			break;
		}
		if(DI[1]<temp2)
		{
			cout <<"ÔÝÍ£"<< endl;
			st=clock();
			while(1)
			{
				_outp(BASE_ADDRESS + iPort,creat_DO());	
				DI_data = _inp(BASE_ADDRESS + iPort);
				creat_DI(DI_data);
				stp=clock();
				if(DI[1]<temp2 && stp - st > stop)
				{
					cout <<"¼ÌÐø"<< endl;
					break;
				}

			}	
		}
		temp2=DI[1];
	}
	for(i=0;i<8;i++)
	{
		DO[i]=0;
	}
	_outp(BASE_ADDRESS + iPort,creat_DO());
}

void d2()
{
	for(i=0;i<8;i++)
	{
		DO[i]=0;
	}
	st=clock();
	while(stp-st<=jinpao)
	{
		DO[1]=1;
		_outp(BASE_ADDRESS + iPort,creat_DO());
		Sleep(50);
		DO[1]=0;
		_outp(BASE_ADDRESS + iPort,creat_DO());
		Sleep(50);
		stp=clock();
		int DI_data = _inp(BASE_ADDRESS + iPort);
  		creat_DI(DI_data);
		if(DI[1]<temp2)
		{
			cout <<"ÔÝÍ£"<< endl;
			st=clock();
			while(1)
			{
				_outp(BASE_ADDRESS + iPort,creat_DO());	
				DI_data = _inp(BASE_ADDRESS + iPort);
				creat_DI(DI_data);
				stp=clock();
				if(DI[1]<temp2 && stp - st > stop)
				{
					cout <<"¼ÌÐø"<< endl;
					break;
				}

			}	
		}
		temp2=DI[1];
	}
	for(i=0;i<8;i++)
	{
		DO[i]=0;
	}
	_outp(BASE_ADDRESS + iPort,creat_DO());
}

void d3()
{
	for(i=0;i<8;i++)
	{
		DO[i]=0;
	}
	while(1)
	{
		DO[2]=1;
		_outp(BASE_ADDRESS + iPort,creat_DO());
		Sleep(50);
		DO[2]=0;
		_outp(BASE_ADDRESS + iPort,creat_DO());
		Sleep(50);
		int DI_data = _inp(BASE_ADDRESS + iPort);
  		creat_DI(DI_data);
		if(DI[2]<temp2)
		{
			break;
		}
		if(DI[1]<temp2)
		{
			cout <<"ÔÝÍ£"<< endl;
			st=clock();
			while(1)
			{
				_outp(BASE_ADDRESS + iPort,creat_DO());	
				DI_data = _inp(BASE_ADDRESS + iPort);
				creat_DI(DI_data);
				stp=clock();
				if(DI[1]<temp2 && stp - st > stop)
				{
					cout <<"¼ÌÐø"<< endl;
					break;
				}

			}	
		}
		temp2=DI[1];
	}
	for(i=0;i<8;i++)
	{
		DO[i]=0;
	}
	_outp(BASE_ADDRESS + iPort,creat_DO());
}

void d6()
{
	for(i=0;i<8;i++)
	{
		DO[i]=0;
	}
	st=clock();
	while(stp-st<=wancheng)
	{
		DO[5]=1;
		_outp(BASE_ADDRESS + iPort,creat_DO());
		Sleep(50);
		DO[5]=0;
		_outp(BASE_ADDRESS + iPort,creat_DO());
		Sleep(50);
		stp=clock();
		int DI_data = _inp(BASE_ADDRESS + iPort);
  		creat_DI(DI_data);
		if(DI[1]<temp2)
		{
			cout <<"ÔÝÍ£"<< endl;
			st=clock();
			while(1)
			{
				_outp(BASE_ADDRESS + iPort,creat_DO());	
				DI_data = _inp(BASE_ADDRESS + iPort);
				creat_DI(DI_data);
				stp=clock();
				if(DI[1]<temp2 && stp - st > stop)
				{
					cout <<"¼ÌÐø"<< endl;
					break;
				}

			}	
		}
		temp2=DI[1];
	}
	for(i=0;i<8;i++)
	{
		DO[i]=0;
	}
	_outp(BASE_ADDRESS + iPort,creat_DO());
}

void shan(int num,int fre)
{
	st=clock();
	while(stp-st<=num)
	{
		for(int i=0;i<=7;i++)
		{
			for(int j=0;j<=7;j++)//st
				DO[j]=0;
			DO[i]=1;
			_outp(BASE_ADDRESS + iPort,creat_DO());
			Sleep(fre);//stp
			stp=clock();
			if(kbhit())
			{
				char c=getch();
				if(c=='p'||c=='P')
				{exit(0);
				ShutdownWinIo();}
			}
		int DI_data = _inp(BASE_ADDRESS + iPort);
  		creat_DI(DI_data);
		if(DI[1]<temp2)
		{
			cout <<"ÔÝÍ£"<< endl;
			st=clock();
			while(1)
			{
				_outp(BASE_ADDRESS + iPort,creat_DO());	
				DI_data = _inp(BASE_ADDRESS + iPort);
				creat_DI(DI_data);
				stp=clock();
				if(DI[1]<temp2 && stp - st > stop)
				{
					cout <<"¼ÌÐø"<< endl;
					break;
				}

			}		
		}
		temp2=DI[1];
			//temp2=DI[1];
		}
		
	}
}


void main(void)
{

	cout<<"°´PÍË³ö"<<endl;
// ³õÊ¼»¯WinIO 
	
	if (!InitializeWinIo())
	{
		cout<<"Error In InitializeWinIo!"<<endl;
		exit(1);
	}


//Êý×ÖÁ¿ÊäÈë


	int DI_data,temp1=1,temp2=1,temp3=1;

   while(1)
   {
	DI_data = _inp(BASE_ADDRESS + iPort);
  	creat_DI(DI_data);
	if(DI[0]<temp1)
	{
		cout <<"×¢Ë®"<< endl;
		d1();
		cout <<"½þÅÝ"<< endl;
		d2();
		cout << "Ï´µÓ" << endl;
		shan(xidi,30);
		for(i=0;i<2;i++)
		{
			cout << "ÅÅË®" << endl;
			d3();
			cout << "ÍÑË®" << endl;
			shan(tuoshui,10);
			cout << "×¢Ë®" << endl;
			d1();
			cout << "Æ¯Ï´" << endl;
			shan(xidi,30);
		}
		cout << "ÅÅË®" << endl;
		d3();
		cout << "ÍÑË®" << endl;
		shan(tuoshui,10);
		cout << "Íê³É" << endl;
		d6();
	}
	temp1=DI[0];
   
   if(kbhit())
		{
			char c=getch();
			if(c=='p'||c=='P')
			{exit(0);
			ShutdownWinIo();}
		}
    }		//¹Ø±ÕWinIO							
}