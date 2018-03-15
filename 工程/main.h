#ifndef __MAIN_H_
#define __MAIN_H_

/*********用于存放各种结构体定义********/ 
#include<ege.h>
#include<graphics.h>
#include<iostream>
#include<vector>

using namespace std;

#define B 10

typedef struct Rowlist{  //行链表 
    int No;//第N个链表
    int loca[B]; 
    int Cnum;//中文字符
    int Onum;//其他字符 
    int weight; 
    Rowlist *next;
    char *heap;
    int heaplen;  
    int maxlen;//一行多少个字符 
    int count;//记录一共有多少段 
}Rowlist;

typedef struct Location{  //存放字符位置的数组
    int rowplace;//字符在行链表的位置；
    int heapplace;//字符在堆的位置；
    int length;//字符长度 
}Location;


int mx;//鼠标横坐标x
int my;//鼠标纵坐标y
vector<char>clip;//剪贴板 
struct Rowlist *head;//文档内存的头指针 
vector<struct Location>color;//

#endif
