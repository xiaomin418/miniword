/**************�����Ա��֪************** 
/* 
1 .���߳�1�е�sleep()����������ͷ�ļ��Ĳ�ͬ��������΢�в��sleep(1)����1�����0.001��
�����д���*/ 

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
unsigned __stdcall print(void* pArguments);//���߳����ڴ�ӡ���� 
unsigned __stdcall getInput(void* pArguments);//���߳����ڽ��ռ���(�����)��Ϣ 
 
int W=1300;
int H=700; 

 
int main()
{
   	HANDLE hThread1;       //�̵߳ķ��ʾ��
   	HANDLE hThread2;  
   	unsigned ThreadID_1=1;   
   	unsigned ThreadID_2=1;  
   	initgraph(W,H);//��ʼ������
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
   	init();//��ʼ������ 
	initface(); //��ʼ������ 
	//CreateProcess(); 
	while(!exitn())
	{
	    ;
	}
	WaitForSingleObject(hThread1,INFINITE);//�ȴ��߳̽���
	WaitForSingleObject(hThread2,INFINITE);//�ȴ��߳̽���
   	CloseHandle(hThread1);//��������߳�ʱɾ���˾�����ɷ�ֹ�ں˶���й¶��
   	CloseHandle(hThread2);//��������߳�ʱɾ���˾�����ɷ�ֹ�ں˶���й¶��
	getch();
	closegraph(); 
	return 0;
}
unsigned __stdcall print(void* pArguments)
//�̺߳����ķ���ֵ��ָ�����ͣ��β�Ҳֻ����һ��
{

	while(1)
	{
		printf("hthread1 print\n");
		sleep(1);//ע�⣺�˴����ڵ��԰汾�Ĳ�ͬ,����1����1�룻��Щ��1000����1�� 
	}

     	_endthreadex(0);//�߳����ʱҪ����_endthread
	return 0;
}
unsigned __stdcall getInput(void* pArguments)
//�̺߳����ķ���ֵ��ָ�����ͣ��β�Ҳֻ����һ��
{
	long int num;
	while(1)
    	{
    	num=getch();	
	if(num!=2)
	printf("keyboard\n");
	}

     	_endthreadex(0);//�߳����ʱҪ����_endthread
	return 0;
}

