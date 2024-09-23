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


	int i,flag=0;
	int DI_data,DO_data,tempDI=255;
	int DI[8]={0};
	int DO[8] = {0};
	int load = 0;

	cout << "Press any key to quit!" << endl;
	while(!kbhit())
	{
		DI_data = _inp(BASE_ADDRESS + iPort);
		creat_DI(DI,DI_data);
		if(DI[0] == 0)
		{
			DO[2] = 1;
			DO_data=creat_DO(DO);
			_outp(BASE_ADDRESS + iPort,DO_data);
			Sleep(200);
			DO[1] = 1;
			DO_data=creat_DO(DO);
			_outp(BASE_ADDRESS + iPort,DO_data);
			Sleep(200);
			DO[0] = 1;
			DO_data=creat_DO(DO);
			_outp(BASE_ADDRESS + iPort,DO_data);
			Sleep(100);
			DO[4] = 1;
			flag = 1;
			DO_data=creat_DO(DO);
			_outp(BASE_ADDRESS + iPort,DO_data);
		}
		if(DI[1] == 0)
		{
			DO[0] = 0;
			DO_data=creat_DO(DO);
			_outp(BASE_ADDRESS + iPort,DO_data);
			Sleep(200);
			DO[1] = 0;
			DO_data=creat_DO(DO);
			_outp(BASE_ADDRESS + iPort,DO_data);
			Sleep(200);
			DO[2] = 0;
			DO_data=creat_DO(DO);
			_outp(BASE_ADDRESS + iPort,DO_data);
			Sleep(100);
			DO[4] = 0;
			flag = 0;
			system("cls");
		}
		if(DI[2] == 0 && DI[3] == 0 && DI[4] == 0 && DI[5] == 0) load = 18;
		if(DI[2] == 0 && DI[3] == 0 && DI[4] == 0 && DI[5] == 1) load = 12;
		if(DI[2] == 0 && DI[3] == 0 && DI[4] == 1 && DI[5] == 0) load = 13;
		if(DI[2] == 0 && DI[3] == 0 && DI[4] == 1 && DI[5] == 1) load = 7;
		if(DI[2] == 0 && DI[3] == 1 && DI[4] == 0 && DI[5] == 0) load = 14;
		if(DI[2] == 0 && DI[3] == 1 && DI[4] == 0 && DI[5] == 1) load = 10;
		if(DI[2] == 0 && DI[3] == 1 && DI[4] == 1 && DI[5] == 0) load = 9;
		if(DI[2] == 0 && DI[3] == 1 && DI[4] == 1 && DI[5] == 1) load = 4;
		if(DI[2] == 1 && DI[3] == 0 && DI[4] == 0 && DI[5] == 0) load = 14;
		if(DI[2] == 1 && DI[3] == 0 && DI[4] == 0 && DI[5] == 1) load = 9;
		if(DI[2] == 1 && DI[3] == 0 && DI[4] == 1 && DI[5] == 0) load = 10;
		if(DI[2] == 1 && DI[3] == 0 && DI[4] == 1 && DI[5] == 1) load = 4;
		if(DI[2] == 1 && DI[3] == 1 && DI[4] == 0 && DI[5] == 0) load = 11;
		if(DI[2] == 1 && DI[3] == 1 && DI[4] == 0 && DI[5] == 1) load = 5;
		if(DI[2] == 1 && DI[3] == 1 && DI[4] == 1 && DI[5] == 0) load = 6;
		if(DI[2] == 1 && DI[3] == 1 && DI[4] == 1 && DI[5] == 1) load = 0;

		if(load <= 10 && flag == 1)
		{
			DO[4] = 1;
			DO[5] = 0;
			system("cls");
			cout << "Working!" << endl;
		}
		else if(load <= 13 && flag == 1)
		{
			DO[4] = 0;
			DO[5] = 1;
			system("cls");
			cout << "Warning：OverLoaded!" << endl;
		}
		else if(flag == 1)
		{
			DO[5] = 0;
			DO[6] = 1;
			system("cls");
			cout << "Error Warning：OverLoaded!" << endl;
			Sleep(3000);
			DO[4] = 0;
			DO[5] = 0;
			DO[6] = 1;
			flag = 0;
			DO_data=creat_DO(DO);
			_outp(BASE_ADDRESS + iPort,DO_data);
			cout << "Waring: qiut after three seconds!" << endl;
			Beep(1760, 500);
			Beep(147, 500);
			Beep(494, 500);
			Beep(1760, 500);
			Beep(147, 500);
			Beep(494, 500);
			for(int j = 0;j < 8;j++) DO[j] = 0;
			DO_data=creat_DO(DO);
			_outp(BASE_ADDRESS + iPort,DO_data);
			continue;
		}
		if(DI[7] == 0)
		{
			DO[4] = 0;
			DO[5] = 0;
			DO[6] = 1;
			flag = 0;
			DO_data=creat_DO(DO);
			_outp(BASE_ADDRESS + iPort,DO_data);
			cout << "Waring: qiut after three seconds!" << endl;
			Beep(1760, 500);
			Beep(147, 500);
			Beep(494, 500);
			Beep(1760, 500);
			Beep(147, 500);
			Beep(494, 500);
			for(int j = 0;j < 8;j++) DO[j] = 0;
			DO_data=creat_DO(DO);
			_outp(BASE_ADDRESS + iPort,DO_data);
			continue;
		}
	
		DO_data=creat_DO(DO);
		_outp(BASE_ADDRESS + iPort,DO_data);
	}
	for(int j = 0;j < 8;j++) DO[j] = 0;
	DO_data=creat_DO(DO);
	_outp(BASE_ADDRESS + iPort,DO_data);

    ShutdownWinIo();								
}