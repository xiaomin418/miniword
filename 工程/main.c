#include<stdio.h>
/*
#include<process.h>
#include<windows.h>
#include"init.h"
#include"exit.h"
#include"print.h"
/***�ļ����棬�༭����****/ 
//unsigned __stdcall getInput(void* pArguments);*/
int main()
{
	/*HANDLE hThread1;       //�̵߳ķ��ʾ��
   	unsigned ThreadID=1;   
   	init();//��ʼ������
	initface(); //��ʼ������ 
	hThread1=(HANDLE*)_beginthreadex(NULL,0, getInput,NULL,0, &ThreadID); 
*/	printf("hello");
	//WaitForSingleObject(hThread1,INFINITE);//�ȴ��߳̽���
   	//CloseHandle(hThread1);//��������߳�ʱɾ���˾�����ɷ�ֹ�ں˶���й¶��
	//system("pause"); 
	return 0;
}/*
unsigned __stdcall getInput(void* pArguments)
//�̺߳����ķ���ֵ��ָ�����ͣ��β�Ҳֻ����һ��
{
	for(int j=0;j<=10;j++)
	{
		printf("j=%d\n",j);
	}

     	_endthreadex(0);//�߳����ʱҪ����_endthread
	return 0;
}*/
