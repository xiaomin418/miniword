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
	//initface(); //��ʼ������ 
	hThread1=(HANDLE*)_beginthreadex(NULL,0, getInput,NULL,0, &ThreadID); 
	xyprintf(W / 100, H / 100, "WELCOME!");
          while(!exit())
          {
            //�������к��Ĳ��� 
	}
	WaitForSingleObject(hThread1,INFINITE);//�ȴ��߳̽���
   	CloseHandle(hThread1);//��������߳�ʱɾ���˾�����ɷ�ֹ�ں˶���й¶��
	//system("pause"); 
	getch();
	closegraph(); 
	return 0;
}
unsigned __stdcall getInput(void* pArguments)
//�̺߳����ķ���ֵ��ָ�����ͣ��β�Ҳֻ����һ��
{

	xyprintf(W / 100+20, H / 100+20, "hello!");

     	_endthreadex(0);//�߳����ʱҪ����_endthread
	return 0;
}
