#pragma once
#ifndef __PRINT__H__
#define __PRINT__H__
#include"main.h"
void init_rowlist(Rowlist *A);
void init_loca(Location &A);
void rowlist1();
Location GetLocation(int mx, int my);
void print();
void on_MouseHandle(int event, int x, int y, int flags, void *param);
Mat mergeRows(Mat& A, Mat& B);
#endif
