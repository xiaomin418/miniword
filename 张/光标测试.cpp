#include<stdio.h>  
#include<windows.h>  
//获取光标位置 
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
//设置光标的位置  
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
    printf(" 学生C语言成绩管理系统");  
    gotoxy(15,8);  
    printf("*********************主菜单*********************");  
    gotoxy(15,9);  
    printf("* 1 输入 2 删除 *");  
    gotoxy(15,10);  
    printf("* 3 查找 4 修改 *");  
    gotoxy(15,11);  
    printf("* 5 插入 6 统计 *");  
    gotoxy(15,12);  
    printf("* 7 排序 8 保存 *");  
    gotoxy(15,13);  
    printf("* 9 显示 0 退出 *");  
    gotoxy(15,14);  
    printf("************************************************");  
    gotoxy(15,15);  
    printf("请输入你的选择(0-9):[ ]");  
    x=wherex();  
    y=wherey();  
    gotoxy(x-2,y);  
    scanf("%d",&select);  
    return 0;  
}   
