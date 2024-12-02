// 数字量输入例程.


#include <windows.h>
#include <iostream>
#include <conio.h>
#include "winio.h"
#include<time.h>

#pragma comment(lib,"winio.lib")
using namespace std;


int creat_DI(int (&DI_bit)[8], int num)
{
  	int i=0;
  	for(i=0;i<8;i++)
   	DI_bit[i]=(num>>i)&0x0001;
  	return 0;
}

int creat_DO(int (&DI_bit)[8])
{
  	int temp=0;
	for(int i=0;i<7;i++)
	{
		temp=2*(DI_bit[i]+temp);
	}
	temp=temp+DI_bit[7];
	return temp;
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


//数字量输入


	int flag=0;
	int temp=1;
	int DI_data,DO_data,tempDI=255;
	int light_time = 4000;
	
	int DI[8]={0};
	int DO[8] = {0};
	cout << "请按任意键退出" << endl;
    while(!kbhit())
    {
		DI_data = _inp(BASE_ADDRESS + iPort);
		creat_DI(DI,DI_data);
		clock_t start0, start1, start2, start3, start4, start5;
		if(DI[0] < temp)
		{
		
			start0 = clock();
			DO[0] = 1;
		}
		if(DI[1] < temp)
		{
			start1 = clock();
			DO[1] = 1;
		}
		if(DI[2]  < temp)
		{
			start2 = clock();
			DO[2] = 1;
		}
		if(DI[3]  < temp)
		{
			start3 = clock();
			DO[3] = 1;
		}
		if(DI[4]  < temp)
		{
			start4 = clock();
			DO[4] = 1;
		}
		if(DI[5]  < temp)
		{
			start5 = clock();
			DO[5] = 1;
		}
		clock_t end;
		end = clock();
		if(end - start0 == light_time) DO[0] = 0;
		if(end - start1 == light_time) DO[1] = 0;
		if(end - start2 == light_time) DO[2] = 0;
		if(end - start3 == light_time) DO[3] = 0;
		if(end - start4 == light_time) DO[4] = 0;
		if(end - start5 == light_time) DO[5] = 0;
		DO_data=creat_DO(DO);
		_outp(BASE_ADDRESS + iPort,DO_data);
	}
	for(int j = 0;j < 8;j++) DO[j] = 0;
	DO_data=creat_DO(DO);
	_outp(BASE_ADDRESS + iPort,DO_data);

    ShutdownWinIo();								
}