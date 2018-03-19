/**************编程人员须知************** 
/* 
1 .在线程1中的sleep()函数，由于头文件的不同，函数略微有差别：sleep(1)代表1秒或者0.001秒
请自行处理*/ 

#include<stdio.h>
#include<windows.h>
#include <unistd.h>
#include<process.h>
#include<windows.h>
#include"init.h"
#include"exit.h"
#include"print.h"
#include<ege.h>
#include<graphics.h>
#include<string.h> 
#include<iostream>
using namespace std;
/***文件界面，编辑界面****/ 
unsigned __stdcall print(void* pArguments);//另开线程用于打印界面 
unsigned __stdcall getInput(void* pArguments);//另开线程用于接收键盘(或鼠标)消息 
 
int W=1300;
int H=700; 

 
int main()
{
   	HANDLE hThread1;       //线程的访问句柄
   	HANDLE hThread2;  
   	unsigned ThreadID_1=1;   
   	unsigned ThreadID_2=1;  
   	initgraph(W,H);//初始化变量
   	setbkcolor(EGERGB(0xFC,0xFC,0xFC));
   	xyprintf(W / 100, H / 100, "main process!");
   	long int  key;
   	int count=1;
   	mouse_msg  msg;
	int mx,my;
	hThread1=(HANDLE*)_beginthreadex(NULL,0, print,NULL,0, &ThreadID_1); 
	hThread2=(HANDLE*)_beginthreadex(NULL,0, getInput,NULL,0, &ThreadID_2); 
	while(1)
	{
		
		//mousepos(&mx, &my);
		//for(int i=0;i<10;i++)
		if(mousemsg())
		{
			msg = getmouse();
			if(msg.is_up())
			printf("mouse\n");
			 
		}
	}
//	char s[10];
//	scanf("%s",&s);
//	xyprintf(W / 100, H / 100+100, "%s",s);
   	init();//初始化变量 
	initface(); //初始化界面 
	//CreateProcess(); 
	while(!exitn())
	{
	    ;
	}
	WaitForSingleObject(hThread1,INFINITE);//等待线程结束
	WaitForSingleObject(hThread2,INFINITE);//等待线程结束
   	CloseHandle(hThread1);//无须控制线程时删除此句柄，可防止内核对象泄露。
   	CloseHandle(hThread2);//无须控制线程时删除此句柄，可防止内核对象泄露。
	getch();
	closegraph(); 
	return 0;
}
unsigned __stdcall print(void* pArguments)
//线程函数的返回值是指定类型，形参也只能有一个
{

	while(1)
	{
		printf("hthread1 print\n");
		sleep(1);//注意：此处由于电脑版本的不同,这里1代表1秒；有些是1000代表1秒 
	}

     	_endthreadex(0);//线程完成时要调用_endthread
	return 0;
}
unsigned __stdcall getInput(void* pArguments)
//线程函数的返回值是指定类型，形参也只能有一个
{
	long int num;
	while(1)
    	{
    	num=getch();	
	if(num!=2)
	printf("keyboard\n");
	}

     	_endthreadex(0);//线程完成时要调用_endthread
	return 0;
}

