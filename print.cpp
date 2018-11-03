#define _CRT_SECURE_NO_WARNINGS
#include<opencv2/opencv.hpp>
#include <cstdio>
#include<Windows.h>
#include"CvxText.h"
#include"function.h"
#include"print.h"
#include"file.h"
using namespace std;
using namespace cv;

extern int row_sum;//总行数
extern int word_sum;//总字数
extern int para_sum;
extern int pagestart;
extern int pageend;//打印页的开始与结尾
extern Rowlist *head;
extern Location location[Max];
extern Location start;
extern Location fin;
extern Location cur;//鼠标的开始，结束和当前位置
extern Mat image;
extern Mat menu;
extern Mat mergemat;
//==========Attention：新加入的
extern int Mode;
extern int opf;
extern char arf[Namelen];
extern char temp[Namelen];//临时文件名
extern int po;
extern int sys;
extern int menukey;
extern vector<char>rclip;
//==========
extern struct Font font1;
extern struct Font font2;
extern double aa, bb, cc, dd;
extern CvScalar *size1;//中文字体格式??????
extern string a;//行间距的demo
extern double demo;//设置行间距

void init_rowlist(Rowlist *A) {//链表节点的初始化
	A->No = A->count = A->heaplen = 0;
	A->width = X;
	A->maxlen = 100;
	A->next = NULL;
	A->heap = NULL;
	for (int i = 0; i < Max; i++) {
		A->loca[i] = 0;
	}
	A->count = 1;
}
void init_loca(Location &A) {//位置的初始化
	A.heapplace = 0;
	A.rowplace = NULL;
}

void rowlist1() {
	Rowlist *last;
	head = (Rowlist*)malloc(sizeof(Rowlist));
	last = head->next = (Rowlist*)malloc(sizeof(Rowlist));
	init_rowlist(last);

	FILE *fptr;
	if ((fptr = fopen(arf, "r")) == NULL) {
		printf("error\n");
		exit(0);
	}
	char s[2];
	fread(&s, sizeof(char), 1, fptr);

	while (!feof(fptr)) {
		if (last->heap == NULL) {
			last->heap = (char*)malloc(sizeof(char) * 100);
		}
		if (last->heaplen == last->maxlen) {
			last->maxlen = last->maxlen + 100;
			char *newch = (char*)malloc(sizeof(char)*(last->maxlen));
			for (int i = 0; i <last->heaplen; i++) { 
				newch[i] = last->heap[i];
			}
			last->heap = (char*)malloc(sizeof(char) * (last->maxlen));
			for (int i = 0; i <last->heaplen; i++) {
				last->heap[i] = newch[i];
			}
		}
		if (s[0] == '\n') {//遇到换行符新建链表节点
			last->heap[last->heaplen++] = s[0];
			para_sum++;
			last = last->next = (Rowlist*)malloc(sizeof(Rowlist));
			init_rowlist(last);
		}
		else last->heap[last->heaplen++] = s[0];
		fread(&s, sizeof(char), 1, fptr);
	}
	fclose(fptr);
}
//void renewlist(Rowlist *last) 
Location GetLocation(int mx, int my) {
	int rowcount = (my - 0.15 * SH + pagestart) / demo + 1;//鼠标位置在当前页的第几行
	int sum = 0;
	Rowlist *last;
	for (last = head->next; last->next != NULL; last = last->next) {
		if (sum < rowcount && (last->count + sum) >= rowcount) {
			rowcount = rowcount - sum;
			break;
		}
		sum += last->count;
	}
	Location loca;
	init_loca(loca);
	loca.rowplace = last;
	int locawidth = X;
	int prelocawidth = X;
	int flag = 0;
	int iend = last->loca[rowcount + 1];
	if (iend == 0) iend = last->heaplen;
	for (int i = last->loca[rowcount]; i < iend; i++) {
		prelocawidth = locawidth;
		if ((unsigned char)last->heap[i] > 0x7F) {
			locawidth += size1->val[0];
			i++;
			flag = 1;
		}
		else if (last->heap[i] < 0x7F) {
			flag = 0;
			string str;
			if (last->heap[i] == '\t') {
				str = "    ";
			}
			else str = { last->heap[i] };
			Size size = getTextSize(str, font1.fontt, font1.size, 1, font1.baseline);
			locawidth += size.width;
		}
		if (mx >= prelocawidth && mx < (locawidth + prelocawidth) / 2 && my > 0.15 *SH) {
			if (flag == 1) i--;
			loca.heapplace = i;
			return loca;
		}
		else if (mx < locawidth && mx >= (locawidth + prelocawidth) / 2 && my > 0.15 *SH) {
			loca.heapplace = i + 1;
			return loca;
		}

	}
	if (my > 0.15 * SH) {
		loca.heapplace = last->heaplen - 1;
		return loca;
	}
	loca.heapplace = -1;
	return loca;

}
void printmenu() {
	putText(menu, arf, cvPoint(5, SH *0.06), font1.fontt, 2, CvScalar(255, 255, 255), 1.5);
	putText(menu, "Exit", cvPoint(5, SH * 0.13), font1.fontt, 2, CvScalar(255, 255, 255), 1.5);
	if (opf == 1)
		rectangle(menu, cvPoint(5, SH * 0.08), cvPoint(W * 1 / 10, SH * 0.14), cvScalar(205, 148, 79), 2);
	putText(menu, "Save", cvPoint(W * 1 / 10 + 5, SH * 0.13), font1.fontt, 2.5, CvScalar(255, 255, 255), 1.5);
	if (opf == 2)
		rectangle(menu, cvPoint(W * 1 / 10, SH * 0.08), cvPoint(W * 2 / 10 - 5, SH * 0.14), cvScalar(205, 148, 79), 2);
	putText(menu, "Saveas", cvPoint(W * 2 / 10, SH * 0.13), font1.fontt, 2, CvScalar(255, 255, 255), 1.5);
	if (opf == 3)
		rectangle(menu, cvPoint(W * 2 / 10, SH * 0.08), cvPoint(W * 3 / 10 - 5, SH * 0.14), cvScalar(205, 148, 79), 2);
	putText(menu, "Copy", cvPoint(W * 3 / 10 + 5, SH * 0.13), font1.fontt, 2, CvScalar(255, 255, 255), 1.5);
	if (opf == 4)
		rectangle(menu, cvPoint(W * 3 / 10, SH * 0.08), cvPoint(W * 4 / 10 - 5, SH * 0.14), cvScalar(205, 148, 79), 2);
	putText(menu, "Shear", cvPoint(W * 4 / 10 + 5, SH * 0.13), font1.fontt, 2, CvScalar(255, 255, 255), 1.5);
	if (opf == 5)
		rectangle(menu, cvPoint(W * 4 / 10, SH * 0.08), cvPoint(W * 5 / 10 - 5, SH * 0.14), cvScalar(205, 148, 79), 2);
	putText(menu, "Paste", cvPoint(W * 5 / 10 + 5, SH * 0.13), font1.fontt, 2, CvScalar(255, 255, 255), 1.5);
	if (opf == 6)
		rectangle(menu, cvPoint(W * 5 / 10, SH * 0.08), cvPoint(W * 6 / 10 - 5, SH * 0.14), cvScalar(205, 148, 79), 2);
	putText(menu, "Selall", cvPoint(W * 6 / 10 + 5, SH * 0.13), font1.fontt, 2, CvScalar(255, 255, 255), 1.5);
	if (opf == 7)
		rectangle(menu, cvPoint(W * 6 / 10, SH * 0.08), cvPoint(W * 7 / 10 - 5, SH * 0.14), cvScalar(205, 148, 79), 2);
	putText(menu, "Find", cvPoint(W * 7 / 10 + 5, SH * 0.13), font1.fontt, 2, CvScalar(255, 255, 255), 1.5);
	if (opf == 8)
		rectangle(menu, cvPoint(W * 7 / 10, SH * 0.08), cvPoint(W * 8 / 10 - 5, SH * 0.14), cvScalar(205, 148, 79), 2);
	putText(menu, "change", cvPoint(W * 8 / 10 + 5, SH * 0.13), font1.fontt, 2, CvScalar(255, 255, 255), 1.5);
	if (opf == 9)
		rectangle(menu, cvPoint(W * 8 / 10, SH * 0.08), cvPoint(W * 9 / 10, SH * 0.14), cvScalar(205, 148, 79), 2);
}

void print() {//复杂功能还没加,打印颜色
	menu = Mat(Size(W, 0.15*SH), CV_8UC3, Scalar(154, 87, 42));
	image = Mat(Size(W, H), CV_8UC3, Scalar(255, 255, 255));
	printmenu();
	Rowlist *last = head->next;
	//location[1].rowplace = last;
	//location[1].heapplace = 35;

	//cout << head->next->heap[0] << endl;

	Point origin(X, demo);//打印位置
	int chosen = 0;
	for (Rowlist *list = head->next; list != NULL; list = list->next) {//每一帧的初始化
		list->count = 1;
		list->width = X;
		for (int i = 0; i < Max; i++) {
			list->loca[i] = 0;
		}
	}
	last = head->next;
	//cout << last;
	int j = 0;
	while (last != NULL) {

		for (int i = 0; i < last->heaplen; i++) {
			//用于存放查找位置
			if (start.rowplace == last && i == start.heapplace)
				chosen = 1 - chosen;
			if (fin.rowplace == last && i == fin.heapplace)//判断是否被选中
				chosen = 1 - chosen;
			float p = 1.0;

			if ((unsigned char)last->heap[i] > 0x7F) {//中文处理
				char buffer[3] = { 0 };
				for (int j = 0; j <= 1; j++) {
					buffer[j] = last->heap[i++];
				}
				i--;
				origin.x = last->width;
				
				if ((origin.x + size1->val[0]) > W - X) {
					last->count++;
					last->loca[last->count] = i;
					origin.y += demo;
					origin.x = X;
					last->width = X;
				}
				last->width += size1->val[0];
				CvxText text("simhei.ttf");
				const char *msg = buffer;

				text.setFont(NULL, size1, NULL, &p);
				IplImage *qwq = &IplImage(image);
				if (i - 1 == fin.heapplace && last == fin.rowplace) {//光标
					line(image, Point(origin.x, origin.y + 5),
						Point(origin.x, origin.y - demo + 5), CvScalar(144, 128, 112), 5);//灰色
				}
				if (chosen) {//快操作的打印
					rectangle(image, Point(origin.x, origin.y + 5),
						Point(origin.x + size1->val[0], origin.y - size1->val[0] + 5), CvScalar(250, 206, 135), CV_FILLED);//蓝色
				}
				if (i == location[j].heapplace && last == location[j].rowplace) {//查找
					text.putText(qwq, msg, cvPoint(origin.x, 0.1* size1->val[0] + origin.y), CV_RGB(255, 215, 0));
					j++;
				}
				else
					text.putText(qwq, msg, cvPoint(origin.x, 0.1* size1->val[0] + origin.y), CV_RGB(0, 0, 0));
			}

			else if (last->heap[i] == '\n') {
				origin.x = last->width;
				if (i == fin.heapplace && last == fin.rowplace) {//光标
					line(image, Point(origin.x, origin.y + 5),
						Point(origin.x, origin.y - demo + 5), CvScalar(144, 128, 112), 5);//灰色
				}
				origin.y += demo;
				origin.x = X;
				last->width = X;
			}
			else if (last->heap[i] < 0x7F) {

				string str;
				if (last->heap[i] == '\t') {
					str = "    ";
				}
				else str = { last->heap[i] };
				Size size = getTextSize(str, font1.fontt, font1.size, 1, font1.baseline);
				origin.x = last->width;
				//cout << str;
				if ((origin.x + size.width) > W - X) {
					last->count++;
					last->loca[last->count] = i;
					origin.y += demo;
					origin.x = X;
					last->width = X;
				}
				last->width += size.width;
				if (chosen) {//快操作
					rectangle(image, Point(origin.x, origin.y + 5),
						Point(origin.x + size.width, origin.y - demo + 5), CvScalar(250, 206, 135), CV_FILLED);//黑色
				}
				//Mat qwq = cvarrToMat(image);
				if (i == location[j].heapplace && last == location[j].rowplace) {//查找
					putText(image, str, origin, font2.fontt, font2.size, font2.color, 2, 8, false);
					j++;
				}
				else
					putText(image, str, origin, font1.fontt, font1.size, font1.color, 2, 8, false);
				if (i == fin.heapplace && last == fin.rowplace) {//光标
					line(image, Point(origin.x, origin.y + 5),
						Point(origin.x, origin.y - demo + 5), CvScalar(144, 128, 112), 5);//灰色
				}
			}


			//cout << last->heap[i];
			//cout << last->count;
		}

		last = last->next;
	}
	Mat image0 = image.rowRange(pagestart, pageend);
	mergemat = mergeRows(menu, image0);
	imshow("hello", mergemat);
}
bool menuexit(int x, int y) {
	if (X>5 && x<W * 1 / 10 && y > SH*0.06 && y < SH*0.14)
		return true;
	return false;
}
bool menusave(int x, int y) {
	if (x<W * 2 / 10 && y > SH*0.06 && y < SH*0.14)
		return true;
	return false;
}
bool menucopy(int x, int y) {//1
	if (x<W * 4 / 10 && y > SH*0.06 && y < SH*0.14)
		return true;
	return false;
}
bool menusaveas(int x, int y) {
	if (x<W * 3 / 10 && y > SH*0.06 && y < SH*0.14)
		return true;
	return false;
}
bool menushear(int x, int y) {
	if (x<W * 5 / 10 && y > SH*0.06 && y < SH*0.14)
		return true;
	return false;
}
bool menupaste(int x, int y) {//2
	if (x<W * 6 / 10 && y > SH*0.06 && y < SH*0.14)
		return true;
	return false;
}
bool menuselall(int x, int y) {
	if (x<W * 7 / 10 && y > SH*0.06 && y < SH*0.14)
		return true;
	return false;
}
bool menufind(int x, int y) {
	if (x<W * 8 / 10 && y > SH*0.06 && y < SH*0.14)
		return true;
	return false;
}
bool menuexchange(int x, int y) {
	if (x<W * 9 / 10 && y > SH*0.06 && y < SH*0.14)
		return true;
	return false;
}
void on_MouseHandle(int event, int x, int y, int flags, void *param) {

	switch (Mode)
	{
	case EDI:
		if (event == EVENT_LBUTTONDOWN) {

			if (menuexit(x, y))//退出系统
			{
				sys = 0;
				menukey = 0;
			}
			else if (menusave(x, y)) {
				if (save())
					MessageBox(NULL, TEXT("FILE"), TEXT("Save successfully!"), 0);
				else
					MessageBox(NULL, TEXT("Warning"), TEXT("Fail!"), 0);
				Mode = FIL;
				menukey = 0;
			}
			else if (menusaveas(x, y)) {
				po = 0;
				memset(temp, 0, Namelen);//清空暂存
				for (int k = 0; arf[k] != 0; k++)
					temp[k] = arf[k];//先将文件名暂时存储在temp里面
				memset(arf, 0, Namelen);//清空arf
				Mode = INPL;
				menukey = 0;
				cout << "saveas" << endl;//测试
			}
			else if (menucopy(x, y)) {
				menukey = 1;
			}
			else if (menushear(x, y)) {
				menukey = 3;
			}
			else if (menupaste(x, y)) {
				menukey = 2;
			}
			else if (menuselall(x, y)) {
				menukey = 4;
			}
			else if (menufind(x, y)) {
				menukey = 5;
			}
			else if (menuexchange(x, y))
			{
				menukey = 6;
			}
			Location a = GetLocation(x, y);
			if(a.heapplace != -1)
				fin = start = GetLocation(x, y);
			//cout << fin.heapplace;
		}
		if (event == EVENT_MOUSEMOVE && flags == EVENT_FLAG_LBUTTON || event == EVENT_LBUTTONUP) {
			cur = fin = GetLocation(x, y);
			rclip.clear();
			//cout << fin.heapplace;
		}
		if (event == EVENT_MOUSEMOVE) {//滚动页面
			int inc = 8;
			if (y > SH * 0.95) {
				if (pageend + inc > H) inc = H - pageend;
				pagestart += inc;
				pageend += inc;
			}
			if (y < SH * 0.15) {
				if (pagestart - inc < 0) inc = pagestart;
				pagestart -= inc;
				pageend -= inc;
			}
		}opf = 0;
		if (menuexit(x, y))
			opf = 1;
		else if (menusave(x, y))
			opf = 2;
		else if (menusaveas(x, y))
			opf = 3;
		else if (menucopy(x, y))
			opf = 4;
		else if (menushear(x, y))
			opf = 5;
		else if (menupaste(x, y))
			opf = 6;
		else if (menuselall(x, y))
			opf = 7;
		else if (menufind(x, y))
			opf = 8;
		else if (menuexchange(x, y))
			opf = 9;
		else
			opf = 0;
		//menukey = 0;
		break;
	case FIL:
		if (mouseopen(x, y))
			opf = 1;
		else if (mousenew(x, y))
			opf = 2;
		else if (mouseexit(x, y))
			opf = 3;
		else
			opf = 0;
		if (event == EVENT_LBUTTONDOWN)
		{
			if (mouseopen(x, y))
			{
				Mode = INPN;
				memset(arf, 0, Namelen);
				po = 0;                 //要新输入文件时更新文件名
				cout << "new" << endl;//测试
			}
			if (mousenew(x, y))
			{
				Mode = INP;
				memset(arf, 0, Namelen);
				po = 0;                  //要新输入文件时更新文件名
				cout << "open" << endl;//测试
			}
			if (mouseexit(x, y))
			{
				sys = 0;//退出系统
				cout << "exit" << endl;//测试
			}

		}
		break;
	case SAV:
		opf = 0;
		if (mousesave(x, y))
			opf = 1;
		else if (mousesaveas(x, y))
			opf = 2;
		else if (mousenotsave(x, y))
			opf = 3;
		else if (backmain(x, y))
			opf = 4;
		else
			opf = 0;
		if (event == EVENT_LBUTTONDOWN)
		{
			if (mousesave(x, y))
			{
				if (save())
					MessageBox(NULL, TEXT("FILE"), TEXT("Save successfully!"), 0);
				else
					MessageBox(NULL, TEXT("Warning"), TEXT("Fail!"), 0);
				Mode = FIL;
				cout << "save" << endl;//测试
			}
			else if (mousesaveas(x, y))
			{
				po = 0;
				memset(temp, 0, Namelen);//清空暂存
				for (int k = 0; arf[k] != 0; k++)
					temp[k] = arf[k];//先将文件名暂时存储在temp里面
				memset(arf, 0, Namelen);//清空arf
				Mode = INPL;
				cout << "saveas" << endl;//测试
			}
			else if (mousenotsave(x, y))
			{
				//sys = 0;
				Mode = FIL;
				cout << "notsave" << endl;//测试
			}
			else if (backmain(x, y))
			{
				Mode = FIL;
				cout << "Main surface" << endl;//测试
			}
		}
	}
}
Mat mergeRows(Mat& A, Mat& B)//拼接矩阵
{
	//CV_ASSERT(A.cols == B.cols&&A.type() == B.type());
	int totalRows = A.rows + B.rows;

	Mat mergedDescriptors(totalRows, A.cols, A.type());
	Mat submat = mergedDescriptors.rowRange(0, A.rows);
	A.copyTo(submat);
	submat = mergedDescriptors.rowRange(A.rows, totalRows);
	B.copyTo(submat);
	return mergedDescriptors;
}