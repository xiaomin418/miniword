#ifndef __MAIN_H_
#define __MAIN_H_

/*********���ڴ�Ÿ��ֽṹ�嶨��********/ 
#include<ege.h>
#include<graphics.h>
#include<iostream>
#include<vector>

using namespace std;

#define B 10

typedef struct Rowlist{  //������ 
    int No;//��N������
    int loca[B]; 
    int Cnum;//�����ַ�
    int Onum;//�����ַ� 
    int weight; 
    Rowlist *next;
    char *heap;
    int heaplen;  
    int maxlen;//һ�ж��ٸ��ַ� 
    int count;//��¼һ���ж��ٶ� 
}Rowlist;

typedef struct Location{  //����ַ�λ�õ�����
    int rowplace;//�ַ����������λ�ã�
    int heapplace;//�ַ��ڶѵ�λ�ã�
    int length;//�ַ����� 
}Location;


int mx;//��������x
int my;//���������y
vector<char>clip;//������ 
struct Rowlist *head;//�ĵ��ڴ��ͷָ�� 
vector<struct Location>color;//

#endif
