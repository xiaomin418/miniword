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
unsigned __stdcall getInput(void* pArguments);//
//另开线程用于打印界面 
 
int W=640;
int H=480; 

 
int main()
{
   	HANDLE hThread1;       //线程的访问句柄
   	unsigned ThreadID=1;   
   	initgraph(W,H);//初始化变量
   	setbkcolor(EGERGB(0xFC,0xFC,0xFC));
   	long int  key;
	key=getch();
	if(key==1)
	xyprintf(W / 100, H / 100+10, "ctrl+\'a\'");
	else if(key=='1')
	xyprintf(W / 100, H / 100+10, "\'a\'");
   	init();//初始化变量 
	initface(); //初始化界面 
	hThread1=(HANDLE*)_beginthreadex(NULL,0, getInput,NULL,0, &ThreadID); 
	//CreateProcess(); 
	xyprintf(W / 100, H / 100, "main process!");
	while(!exitn())
	{
	    ;
	}
	WaitForSingleObject(hThread1,INFINITE);//等待线程结束
   	CloseHandle(hThread1);//无须控制线程时删除此句柄，可防止内核对象泄露。
	getch();
	closegraph(); 
	return 0;
}
unsigned __stdcall getInput(void* pArguments)
//线程函数的返回值是指定类型，形参也只能有一个
{

	//while(!exitn())

     	_endthreadex(0);//线程完成时要调用_endthread
	return 0;
}
