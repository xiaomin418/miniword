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
/***�ļ����棬�༭����****/ 
unsigned __stdcall getInput(void* pArguments);//
//���߳����ڴ�ӡ���� 
 
int W=640;
int H=480; 

 
int main()
{
   	HANDLE hThread1;       //�̵߳ķ��ʾ��
   	unsigned ThreadID=1;   
   	initgraph(W,H);//��ʼ������
   	setbkcolor(EGERGB(0xFC,0xFC,0xFC));
   	long int  key;
	key=getch();
	if(key==1)
	xyprintf(W / 100, H / 100+10, "ctrl+\'a\'");
	else if(key=='1')
	xyprintf(W / 100, H / 100+10, "\'a\'");
   	init();//��ʼ������ 
	initface(); //��ʼ������ 
	hThread1=(HANDLE*)_beginthreadex(NULL,0, getInput,NULL,0, &ThreadID); 
	//CreateProcess(); 
	xyprintf(W / 100, H / 100, "main process!");
	while(!exitn())
	{
	    ;
	}
	WaitForSingleObject(hThread1,INFINITE);//�ȴ��߳̽���
   	CloseHandle(hThread1);//��������߳�ʱɾ���˾�����ɷ�ֹ�ں˶���й¶��
	getch();
	closegraph(); 
	return 0;
}
unsigned __stdcall getInput(void* pArguments)
//�̺߳����ķ���ֵ��ָ�����ͣ��β�Ҳֻ����һ��
{

	//while(!exitn())

     	_endthreadex(0);//�߳����ʱҪ����_endthread
	return 0;
}
