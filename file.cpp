#define _CRT_SECURE_NO_WARNINGS
#include<opencv2/opencv.hpp>
#include <cstdio>
#include"CvxText.h"
#include"main.h"
#include"print.h"
using namespace std;
using namespace cv;
extern Mat image1;
extern Mat menu1;
extern Mat mergemat1;
extern char keydown;
int opf = 0;//表明哪个框变色；1->new;2->open;3->exit
extern char arf[Namelen];//文件名
extern Rowlist *head;
extern int Mode;
extern vector<char>rclip;
extern char replacing[RPlen];
void openfile(void)//打开文件
{
	Mat image2 = Mat(Size(C, K), CV_8UC3, Scalar(255, 255, 255));
	rectangle(image2, cvPoint(C / 10, 4 * K / 10), cvPoint(6 * C / 10, 5 * K / 10), cvScalar(0, 0, 0), 2);
	putText(image2, "Open File", cvPoint(2 * C / 20, 10 * K / 20 - 200), FONT_HERSHEY_SIMPLEX | FONT_ITALIC, 3, (0, 0, 0), 2);
	putText(image2, arf, cvPoint(2 * C / 20, 10 * K / 20), FONT_HERSHEY_SIMPLEX | FONT_ITALIC, 3, (0, 0, 0), 2);
	imshow("hello", image2);
}
void route(void)//新建文件
{
	Mat image2 = Mat(Size(C, K), CV_8UC3, Scalar(255, 255, 255));
	rectangle(image2, cvPoint(C / 10, 4 * K / 10), cvPoint(6 * C / 10, 5 * K / 10), cvScalar(0, 0, 0), 2);
	putText(image2, "New File (Such as:)", cvPoint(2 * C / 20, 10 * K / 20 - 100), FONT_HERSHEY_SIMPLEX | FONT_ITALIC, 3, (0, 0, 0), 2);
	putText(image2, "C:\\\\Users\\\\use_name\\\\desktop",
		cvPoint(2 * C / 20, 10 * K / 20 - 50), FONT_HERSHEY_SIMPLEX | FONT_ITALIC, 3, (0, 0, 0), 1);
	putText(image2, arf, cvPoint(2 * C / 20, 10 * K / 20), FONT_HERSHEY_SIMPLEX | FONT_ITALIC, 3, (0, 0, 0), 1);
	imshow("hello", image2);
}
void repl(void)//待替换字符
{

	Mat image2 = Mat(Size(C, K), CV_8UC3, Scalar(255, 255, 255));
	rectangle(image2, cvPoint(C / 10, 4 * K / 10), cvPoint(6 * C / 10, 5 * K / 10), cvScalar(0, 0, 0), 2);
	putText(image2, "Enter your replacing:", cvPoint(2 * C / 20, 10 * K / 20 - 100), FONT_HERSHEY_SIMPLEX | FONT_ITALIC, 3, (0, 0, 0), 2);
	putText(image2, replacing, cvPoint(2 * C / 20, 10 * K / 20), FONT_HERSHEY_SIMPLEX | FONT_ITALIC, 3, (0, 0, 0), 2);
	imshow("hello", image2);
}
void searc(void)//待替换字符
{

	Mat image2 = Mat(Size(C, K), CV_8UC3, Scalar(255, 255, 255));
	rectangle(image2, cvPoint(C / 10, 4 * K / 10), cvPoint(6 * C / 10, 5 * K / 10), cvScalar(0, 0, 0), 2);
	putText(image2, "Enter your searching:", cvPoint(2 * C / 20, 10 * K / 20 - 100), FONT_HERSHEY_SIMPLEX | FONT_ITALIC, 3, (0, 0, 0), 2);
	putText(image2, replacing, cvPoint(2 * C / 20, 10 * K / 20), FONT_HERSHEY_SIMPLEX | FONT_ITALIC, 3, (0, 0, 0), 2);
	imshow("hello", image2);
}
void newfile(void)//保存文件路径
{
	Mat image2 = Mat(Size(C, K), CV_8UC3, Scalar(255, 255, 255));
	rectangle(image2, cvPoint(C / 10, 4 * K / 10), cvPoint(6 * C / 10, 5 * K / 10), cvScalar(255, 255, 255), -1);
	putText(image2, "File Route", cvPoint(2 * C / 20, 10 * K / 20 - 100), FONT_HERSHEY_SIMPLEX | FONT_ITALIC, 3, (0, 0, 0), 2);
	putText(image2, arf, cvPoint(2 * C / 20, 10 * K / 20), FONT_HERSHEY_SIMPLEX | FONT_ITALIC, 3, (0, 0, 0), 2);
	imshow("hello", image2);
}
void welcome(void)
{
	//CvFont font;
	image1 = Mat(Size(C, K), CV_8UC3, Scalar(255, 255, 255));
	//cvInitFont(&font, FONT_HERSHEY_SIMPLEX | FONT_ITALIC, 1.0, 1,0, 0, 1);
	if (opf != 1)
		rectangle(image1, cvPoint(C / 10, 4 * K / 10), cvPoint(3 * C / 10, 6 * K / 10), cvScalar(0, 0, 0), 2);
	else if (opf == 1)
		rectangle(image1, cvPoint(C / 10, 4 * K / 10), cvPoint(3 * C / 10, 6 * K / 10), cvScalar(226, 161, 27), 3);
	putText(image1, "NewFile", cvPoint(2 * C / 20 + 2, 10 * K / 20), FONT_HERSHEY_SIMPLEX | FONT_ITALIC, 3, (255, 255, 0), 2);

	if (opf != 2)
		rectangle(image1, cvPoint(4 * C / 10, 4 * K / 10), cvPoint(6 * C / 10 + 5, 6 * K / 10), (0, 0, 0), 2);
	else if (opf == 2)
		rectangle(image1, cvPoint(4 * C / 10, 4 * K / 10), cvPoint(6 * C / 10 + 5, 6 * K / 10), cvScalar(226, 161, 27), 3);
	putText(image1, "OpenFile", cvPoint(4 * C / 10, 10 * K / 20), FONT_HERSHEY_SIMPLEX | FONT_ITALIC, 3, (255, 255, 0), 2);

	if (opf != 3)
		rectangle(image1, cvPoint(7 * C / 10, 4 * K / 10), cvPoint(9 * C / 10, 6 * K / 10), cvScalar(0, 0, 0), 2);
	else if (opf == 3)
		rectangle(image1, cvPoint(7 * C / 10, 4 * K / 10), cvPoint(9 * C / 10, 6 * K / 10), cvScalar(226, 161, 27), 3);
	putText(image1, " Exit ", cvPoint(7 * C / 10, 10 * K / 20), FONT_HERSHEY_SIMPLEX | FONT_ITALIC, 3, (255, 255, 0), 2);

	imshow("hello", image1);
}
void savefile(void)
{
	//CvFont font;
	image1 = Mat(Size(C, K), CV_8UC3, Scalar(255, 255, 255));
	//cvInitFont(&font, FONT_HERSHEY_SIMPLEX | FONT_ITALIC, 1.0, 1,0, 0, 1);
	if (opf != 1)
		rectangle(image1, cvPoint(C / 4, K / 13), cvPoint(3 * C / 4, 3 * K / 13), cvScalar(0, 0, 0), 2);
	else if (opf == 1)	
		rectangle(image1, cvPoint(C / 4, K / 13), cvPoint(3 * C / 4, 3 * K / 13), cvScalar(226, 161, 27), 2);
	putText(image1, "Save Revise", cvPoint(C / 4, 2 * K / 13), FONT_HERSHEY_SIMPLEX | FONT_ITALIC, 3, (255, 255, 0), 2);

	if (opf != 2)
		rectangle(image1, cvPoint(C / 4, 4 * K / 13), cvPoint(3 * C / 4, 6 * K / 13), cvScalar(0, 0, 0), 2);
	else if (opf == 2)
		rectangle(image1, cvPoint(C / 4, 4 * K / 13), cvPoint(3 * C / 4, 6 * K / 13), cvScalar(226, 161, 27), 2);
	putText(image1, "Save As", cvPoint(C / 4, 5 * K / 13), FONT_HERSHEY_SIMPLEX | FONT_ITALIC, 3, (255, 255, 0), 2);

	if (opf != 3)
		rectangle(image1, cvPoint(C / 4, 7 * K / 13), cvPoint(3 * C / 4, 9 * K / 13), cvScalar(0, 0, 0), 2);
	else if (opf == 3)
		rectangle(image1, cvPoint(C / 4, 7 * K / 13), cvPoint(3 * C / 4, 9 * K / 13), cvScalar(226, 161, 27), 2);
	putText(image1, "Don't Save Revise", cvPoint(C / 4, 8 * K / 13), FONT_HERSHEY_SIMPLEX | FONT_ITALIC, 3, (255, 255, 0), 2);

	if (opf != 4)
		rectangle(image1, cvPoint(C / 4, 10 * K / 13), cvPoint(3 * C / 4, 12 * K / 13), cvScalar(0, 0, 0), 2);
	else if (opf == 4)
		rectangle(image1, cvPoint(C / 4, 10 * K / 13), cvPoint(3 * C / 4, 12 * K / 13), cvScalar(226, 161, 27), 2);
	putText(image1, "Back Main Surface", cvPoint(C / 4, 11 * K / 13), FONT_HERSHEY_SIMPLEX | FONT_ITALIC, 3, (255, 255, 0), 2);

	imshow("hello", image1);
}
bool exitn(void)
{
	return true;
}
bool mouseopen(int x, int y)
{
	if (x > C / 10 && x < 3 * C / 10 && y>4 * K / 10 && y < 6 * K / 10)
		return true;
	else
		return false;
}
bool mousenew(int x, int y)
{
	if (x > 4 * C / 10 && x < 6 * C / 10 + 5 && y> 4 * K / 10 && y < 6 * K / 10)
		return true;
	else
		return false;
}
bool mouseexit(int x, int y)
{
	if (x >7 * C / 10 && x <9 * C / 10 && y>4 * K / 10 && y < 6 * K / 10)
		return true;
	else
		return false;
}
bool mousesave(int x, int y)
{
	if (x > C / 3 && x<2 * C / 3 && y>K / 13 && y < 3 * K / 13)
		return true;
	else
		return false;
}
bool mousesaveas(int x, int y)
{
	if (x > C / 3 && x<2 * C / 3 && y>4 * K / 13 && y < 6 * K / 13)
		return true;
	else
		return false;
}
bool mousenotsave(int x, int y)
{
	if (x > C / 3 && x<2 * C / 3 && y>7 * K / 13 && y < 9 * K / 13)
		return true;
	else
		return false;
}
bool backmain(int x, int y)
{
	if (x > C / 3 && x<2 * C / 3 && y>10 * K / 13 && y < 12 * K / 13)
		return true;
	else
		return false;
}
bool save(void)
{
	int i;
	FILE *fp = fopen(arf, "w");
	if (fp == NULL)
		return false;
	Rowlist *current;
	current = head->next;

	while (current != NULL)
	{
		for (i = 0; i < current->heaplen; i++)
		{

			putc(current->heap[i], fp);
		}
		current = current->next;
	}
	cout << "Success" << endl;
	fclose(fp);
	Mode = FIL;
	return true;
}