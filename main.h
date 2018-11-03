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
#define H  10000//��Ļ��С
#define SH 1200
#define Max 100
#define X 100    //
#define C 2000    //�����ļ���
#define K 1200    //�����ļ����

#define Namelen  50    //�����ļ������ֳ�������
#define RPlen    20
/*********����״̬******/
#define FIL   1        //�ļ��򿪽��棨���ļ������½��ļ������˳���
#define INP   2        //��ȡ�ļ������棨���ļ���
#define INPN  3        //��ȡ�ļ����֣��½��ļ���
#define INPL  4        //��ȡ�����ļ�·��
#define EDI   5        //�༭����
#define SAV   6        //�ļ��������
#define EXI   7        //�˳�ϵͳģʽ
#define RPL   8        //�滻ģʽ����
#define FIN   9        //����Ҫ��������
/***************data structure***************/
typedef struct heaplist {//�ѵĽṹ��
	char *heap;//ÿ�η���100��
	heaplist *next;
};
typedef struct Rowlist {//������ 
	int No;//��N������
	int loca[Max];
	int width;
	Rowlist *next;
	heaplist *first;//�ѵ�ͷ�ڵ�
	int heaplen;//��ǰ����
	int maxlen;//���ĳ���
	int count;//��¼һ���ж����� 
	char *heap;//��¼���ҵ��ַ���
}Rowlist;

typedef struct location {  //����ַ�λ�õ�����
	Rowlist* rowplace;//�ַ����������λ�ã�
	int heapplace;//�ַ��ڶѵ�λ�ã�
	int length;//�ַ��ĳ���
}Location;

struct Font {//Ӣ������
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