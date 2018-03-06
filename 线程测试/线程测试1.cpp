#include<windows.h>   //创建线程函数需要操作系统函数
#include<process.h>   //创建线程函数头文件
#include<stdio.h>

unsigned __stdcall getInput(void* pArguments)
//线程函数的返回值是指定类型，形参也只能有一个
{
	printf("hThreadl is running\n");//自定义的函数体

     	_endthreadex(0);//线程完成时要调用_endthread
	return 0;
}

main(){
   HANDLE hThread1;       //线程的访问句柄
   unsigned ThreadID=1;   
    //线程标识号,不用变量赋值，则只能为NULL
   hThread1=(HANDLE)_beginthreadex(NULL,0,getInput,NULL,0,&ThreadID); 
    /*创建一个对应于getInput函数的线程 */
   printf("main thread is running\n"); //自定义的主函数体
   WaitForSingleObject(hThread1,INFINITE);//等待线程结束
   CloseHandle(hThread1);//无须控制线程时删除此句柄，可防止内核对象泄露。
}




