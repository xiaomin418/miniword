#ifndef __MAIN__H_
#define __MAIN__H_
#include<iostream>
#include <malloc.h>
#include <cstdio>
#include<opencv2/opencv.hpp>
#include<vector>
#include<malloc.h>
//#include <windows.h>
using namespace std;
using namespace cv;
/**********#define*********/
#define W  2000
#define H  10000//屏幕大小
#define SH 1200
#define Max 100
#define X 100    //
#define C 2000    //输入文件框长
#define K 1200    //输入文件框宽

#define Namelen  50    //输入文件的名字长度上限
#define RPlen    20
/*********界面状态******/
#define FIL   1        //文件打开界面（打开文件或者新建文件或者退出）
#define INP   2        //获取文件名界面（打开文件）
#define INPN  3        //获取文件名字（新建文件）
#define INPL  4        //获取保存文件路径
#define EDI   5        //编辑界面
#define SAV   6        //文件保存界面
#define EXI   7        //退出系统模式
#define RPL   8        //替换模式输入
#define FIN   9        //输入要查找内容
/***************data structure***************/
typedef struct heaplist {//堆的结构体
	char *heap;//每次分配100个
	heaplist *next;
};
typedef struct Rowlist {//行链表 
	int No;//第N个链表
	int loca[Max];
	int width;
	Rowlist *next;
	heaplist *first;//堆的头节点
	int heaplen;//当前长度
	int maxlen;//最大的长度
	int count;//记录一共有多少行 
	char *heap;//记录查找的字符串
}Rowlist;

typedef struct location {  //存放字符位置的数组
	Rowlist* rowplace;//字符在行链表的位置；
	int heapplace;//字符在堆的位置；
	int length;//字符的长度
}Location;

struct Font {//英文字体
	double size;
	Scalar color;
	int *baseline;
	int fontt;
	Font(double a, Scalar b, int c) {
		size = a;
		color = b;
		fontt = c;
	}
};

/***********variable***********/
#endif