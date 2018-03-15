#include<stdio.h>
/*
#include<process.h>
#include<windows.h>
#include"init.h"
#include"exit.h"
#include"print.h"
/***文件界面，编辑界面****/ 
//unsigned __stdcall getInput(void* pArguments);*/
int main()
{
	/*HANDLE hThread1;       //线程的访问句柄
   	unsigned ThreadID=1;   
   	init();//初始化变量
	initface(); //初始化界面 
	hThread1=(HANDLE*)_beginthreadex(NULL,0, getInput,NULL,0, &ThreadID); 
*/	printf("hello");
	//WaitForSingleObject(hThread1,INFINITE);//等待线程结束
   	//CloseHandle(hThread1);//无须控制线程时删除此句柄，可防止内核对象泄露。
	//system("pause"); 
	return 0;
}/*
unsigned __stdcall getInput(void* pArguments)
//线程函数的返回值是指定类型，形参也只能有一个
{
	for(int j=0;j<=10;j++)
	{
		printf("j=%d\n",j);
	}

     	_endthreadex(0);//线程完成时要调用_endthread
	return 0;
}*/
