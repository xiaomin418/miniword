#include<windows.h>   //�����̺߳�����Ҫ����ϵͳ����
#include<process.h>   //�����̺߳���ͷ�ļ�
#include<stdio.h>

unsigned __stdcall getInput(void* pArguments)
//�̺߳����ķ���ֵ��ָ�����ͣ��β�Ҳֻ����һ��
{
	printf("hThreadl is running\n");//�Զ���ĺ�����

     	_endthreadex(0);//�߳����ʱҪ����_endthread
	return 0;
}

main(){
   HANDLE hThread1;       //�̵߳ķ��ʾ��
   unsigned ThreadID=1;   
    //�̱߳�ʶ��,���ñ�����ֵ����ֻ��ΪNULL
   hThread1=(HANDLE)_beginthreadex(NULL,0,getInput,NULL,0,&ThreadID); 
    /*����һ����Ӧ��getInput�������߳� */
   printf("main thread is running\n"); //�Զ������������
   WaitForSingleObject(hThread1,INFINITE);//�ȴ��߳̽���
   CloseHandle(hThread1);//��������߳�ʱɾ���˾�����ɷ�ֹ�ں˶���й¶��
}




