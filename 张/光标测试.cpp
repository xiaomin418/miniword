#include<stdio.h>  
#include<windows.h>  
//��ȡ���λ�� 
int wherex()  
{  
    CONSOLE_SCREEN_BUFFER_INFO pBuffer;  
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &pBuffer);  
    return (pBuffer.dwCursorPosition.X+1);  
}  
int wherey()  
{  
    CONSOLE_SCREEN_BUFFER_INFO pBuffer;  
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &pBuffer);  
    return (pBuffer.dwCursorPosition.Y+1);  
}  
//���ù���λ��  
void gotoxy(int x,int y)   
{  
    COORD c;  
    c.X=x-1;  
    c.Y=y-1;  
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);  
}   
int main()  
{  
    int x, y;  
    int select;  
    gotoxy(28,5);  
    printf(" ѧ��C���Գɼ�����ϵͳ");  
    gotoxy(15,8);  
    printf("*********************���˵�*********************");  
    gotoxy(15,9);  
    printf("* 1 ���� 2 ɾ�� *");  
    gotoxy(15,10);  
    printf("* 3 ���� 4 �޸� *");  
    gotoxy(15,11);  
    printf("* 5 ���� 6 ͳ�� *");  
    gotoxy(15,12);  
    printf("* 7 ���� 8 ���� *");  
    gotoxy(15,13);  
    printf("* 9 ��ʾ 0 �˳� *");  
    gotoxy(15,14);  
    printf("************************************************");  
    gotoxy(15,15);  
    printf("���������ѡ��(0-9):[ ]");  
    x=wherex();  
    y=wherey();  
    gotoxy(x-2,y);  
    scanf("%d",&select);  
    return 0;  
}   
