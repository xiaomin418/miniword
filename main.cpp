#define _CRT_SECURE_NO_WARNINGS
#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0)
#include<process.h>
#include<windows.h>
#include<Cstring>
#include<opencv2/opencv.hpp>
#include <cstdio>
#include<conio.h>
#include"CvxText.h"
#include"function.h"
#include"print.h"
#include"block.h"
#include"file.h"
int row_sum;//总行数
int word_sum;//总字数
int para_sum = 0;
int pagestart = 0;
int pageend = SH;//打印页的开始与结尾
int Mode;//当前模式
int sys;//系统是否运行
int po = 0;
int pre_mode;
int menukey;// 1为复制 2为粘贴 3为剪贴 4为全选
			//解释：在线程1中copy()到剪贴板了之后为了防止还未进行任何操作时不断的进行copy()；lock=1,可以copy()
Rowlist *head;
Location start;
Location fin;
Location cur;//鼠标的开始，结束和当前位置
extern Location location[Max];
Mat image;
Mat menu;
Mat mergemat;
Mat image1;
Mat menu1;
Mat mergemat1;

struct Font font1(3, Scalar(0, 0, 0), CV_FONT_HERSHEY_SIMPLEX);
struct Font font2(3, Scalar(0, 215, 255), FONT_HERSHEY_COMPLEX);
double aa = 80.0, bb = 0.5, cc = 0.0, dd = 0;
CvScalar *size1 = new CvScalar(aa, bb, cc, dd);//中文字体格式
string a = "A";//行间距的demo
double demo = 1.3 * getTextSize(a, font1.fontt, font1.size, 1, font1.baseline).height;//设置行间距
																					  //int keydown;//按键信息
char keydown;//按键信息
char arf[Namelen];//文件名
char temp[Namelen];//临时文件名
extern vector<char>rclip;
char replacing[RPlen];
unsigned __stdcall getInput(void* pArguments);//另开线程用于接收键盘(或鼠标)消息 
int main()
{
	HANDLE hThread1;
	unsigned ThreadID_1 = 1;
	keydown = -1;
	sys = 1;
	menukey = 0;
	char inp;
	Mode = FIL;
	memset(arf, 0, Namelen);
	Rowlist *current;
	namedWindow("hello");
	setMouseCallback("hello", on_MouseHandle);
	hThread1 = (HANDLE*)_beginthreadex(NULL, 0, getInput, NULL, 0, &ThreadID_1);
	for (; sys != 0;)
	{
		keydown = waitKey(0);//系统退出
		if (Mode == INP)//新建文件输入文件名模式
		{
			if (keydown > 31 && keydown < 127)
			{
				cout << keydown << endl;
				arf[po] = keydown;
				po++;
			}
			else if (keydown == 8)
			{
				cout << keydown << endl;
				po = po - 1;
				arf[po] = 0;
			}
			else if (keydown == 13)
			{
				rowlist1();
				init_loca(start);
				init_loca(fin);
				init_loca(cur);
				Mode = EDI;
			}
		}
		else if (Mode == INPN)//保存文件输入文件名
		{
			if (keydown > 31 && keydown < 127)
			{
				cout << keydown << endl;
				arf[po] = keydown;
				po++;
			}
			else if (keydown == 8)
			{
				cout << keydown << endl;
				po = po - 1;
				arf[po] = 0;
			}
			else if (keydown == 13)
			{
				FILE *fp = fopen(arf, "w");
				cout << "Success" << endl;
				fclose(fp);
				//此处记得加入
				Mode = EDI;
			}
		}
		else if (Mode == INPL)//获取文件保存路径
		{
			if (keydown > 31 && keydown < 127)
			{
				cout << keydown << endl;
				arf[po] = keydown;
				po++;
			}
			else if (keydown == 8)
			{
				cout << keydown << endl;
				po = po - 1;
				arf[po] = 0;
			}
			else if (keydown == 13)
			{
				arf[po] = '\\'; po++;
				arf[po] = '\\'; po++;
				for (int k = 0; temp[k] != 0; k++)
					arf[po + k] = temp[k];//得出文件绝对路径
				if (save())
					MessageBox(NULL, TEXT("FILE"), TEXT("Save successfully!"), 0);
				else
					MessageBox(NULL, TEXT("Warning"), TEXT("Fail!"), 0);
				Mode = FIL;
				cout << "saveas" << endl;//测试
				Mode = FIL;
			}
		}
		else if (Mode == EDI)//编辑框模式
		{
			if (keydown == 27)//系统退出
			{
				Mode = SAV;
			}
			else if (keydown > 31 && keydown < 127 || keydown == 13)//表明直接输入字符的时候
			{
				//inp = keydown;
				//cout << inp << endl;//用于测试使用
				//insert(inp);
				//keydown = -1;
				int cc = 0;
				if (location[0].rowplace) {
					while (cc < Max) {
						location[cc].rowplace = NULL;
						cc++;
					}
				}
				if ((keydown != 32) && (keydown != 13)) {
					inp = keydown;
					cout << inp << endl;//用于测试使用
										//cout << keydown << endl;//用于测试使用
				}
				else {
					//inp = keydown;
					/*
					if (keydown == 32)
					{
					printest2();
					printest3();
					printest4();
					}*/
					cout << keydown << endl;//用于测试使用
				}
				//if(keydown!=32)
				insert(start);
				keydown = -1;
			}
			else if (keydown == 8)
			{
				int cc = 0;
				if (location[0].rowplace) {
					while (cc < Max) {
						location[cc].rowplace = NULL;
						cc++;
					}
				}
				//cout << keydown << endl;
				del(start);
				cout << keydown << endl;
				keydown = -1;
				//del(start);
			}
			else if (KEY_DOWN(VK_HOME)) {
				fin.heapplace = start.heapplace = 0;
				fin.rowplace = start.rowplace = head->next;
				pagestart = 0;
				pageend = SH;

			}
			else if (KEY_DOWN(VK_END)) {
				Rowlist *last;
				double num = 0;
				for (last = head->next; last->next != NULL; last = last->next) {
					num += (double)last->count;
				};
				fin.heapplace = start.heapplace = last->heaplen - 2;
				fin.rowplace = start.rowplace = last;
				pageend = (double)(demo) * (num + 10);
				pagestart = pageend - SH;
			}
			else if (KEY_DOWN(VK_NEXT)) {
				pageend += SH;
				pagestart += SH;
			}
			else if (KEY_DOWN(VK_PRIOR)) {
				if (pagestart - SH > 0) {
					pageend -= SH;
					pagestart -= SH;
				}
				else {
					pagestart = 0;
					pageend = SH;
				}

			}
			else if (KEY_DOWN(VK_DELETE))
			{
				int cc = 0;
				if (location[0].rowplace) {
					while (cc < Max) {
						location[cc].rowplace = NULL;
						cc++;
					}
				}
				del(start);
				cout << "delete" << endl;
				keydown = -1;
			}
			else if (KEY_DOWN(VK_RIGHT)) {
				Rowlist* last;
				for (last = head->next; last->next != NULL; last = last->next);
				if(start.heapplace ==last->heaplen-1 && fin.heapplace == last->heaplen-1&& start.rowplace == last && fin.rowplace == last){}
				else {
					if (start.heapplace == fin.heapplace && start.rowplace == fin.rowplace) {
						int flag = 0;
						for (int i = 0; i < start.rowplace->count; i++) {
							if (start.rowplace->loca[i] == start.heapplace + 1) {
								break;
								flag = 1;
							}
						}
						if (flag == 0) {
							if (start.heapplace != start.rowplace->heaplen - 1) {
								fin.heapplace = start.heapplace += 1;
							}
							else {
								fin.rowplace = start.rowplace = start.rowplace->next;
								fin.heapplace = start.heapplace = 0;
							}
						}
						else {
							fin.heapplace = start.heapplace += 1;
						}
					}
					else
					{
						start.heapplace = fin.heapplace;
						start.rowplace = fin.rowplace;
					}
				}
				
			}

			else if (KEY_DOWN(VK_LEFT)) {
				if (start.heapplace == 0 && fin.heapplace == 0 && start.rowplace == head->next&& fin.rowplace == head->next) {}
				else {
					if (start.heapplace == fin.heapplace && start.rowplace == fin.rowplace) {
						int flag = 0;
						for (int i = 0; i < start.rowplace->count; i++) {
							if (start.rowplace->loca[i] == start.heapplace) {
								break;
								flag = 1;
							}
						}
						if (flag == 0) {
							if (start.heapplace != 0) {
								start.heapplace = fin.heapplace -= 1;
							}
							else {
								Rowlist * prelast = head->next;
								for (Rowlist *last = head->next; last->next != NULL; last = last->next) {
									if (last == start.rowplace)break;
									prelast = last;
								}
								start.rowplace = fin.rowplace = prelast;
								start.heapplace = fin.heapplace = prelast->heaplen - 1;
							}
						}
						else {
							fin.heapplace = start.heapplace -= 1;
						}
					}
					else {
						fin.rowplace = start.rowplace;
						fin.heapplace = start.heapplace;

					}

				}

			}

			else
			{
				cout << keydown << endl;//用于测试
				cout << "else" << endl;
				if (block_fun(keydown))//块操作
				{
					int jj = 0;
					while (location[jj].rowplace)
					{
						cout << location[jj].heapplace << endl;
						jj++;
					}
				}

				keydown = -1;
			}


		}
		else if (Mode == RPL)
		{
			if (keydown > 31 && keydown < 127)
			{
				cout << keydown << endl;
				replacing[po] = keydown;
				po++;
			}
			else if (keydown == 8)
			{
				cout << keydown << endl;
				po = po - 1;
				replacing[po] = 0;
			}
			else if (keydown == 13)
			{
				vector<char>rep;
				for (int vv = 0; vv < po; vv++)
					rep.push_back(replacing[vv]);
				replace(rep);
				Mode = EDI;
			}
			rclip.clear();
			cout << "有很多很多bug4" << endl;
			for (int opcv = 0; opcv < rclip.size(); opcv++)
				cout << rclip[opcv];
			cout << "==";

		}
		else if (Mode == FIN)
		{
			if (keydown > 31 && keydown < 127)
			{
				cout << keydown << endl;
				replacing[po] = keydown;
				po++;
			}
			else if (keydown == 8)
			{
				cout << keydown << endl;
				po = po - 1;
				replacing[po] = 0;
			}
			else if (keydown == 13)
			{
				vector<char>Shi;
				Shi.clear();
				for (int vv = 0; vv < po; vv++)
					Shi.push_back(replacing[vv]);
				int cc = 0;
				int i;
				if (location[0].rowplace)
				{
					while (cc < Max)
					{
						location[cc].rowplace = NULL;
						cc++;
					}
				}
				if (search(Shi))
				{
					if (pre_mode != 1)//不是从替换进入
					{
						Mode = EDI;
						pre_mode = 0;
					}
					else if (pre_mode == 1)//从替换进入
					{
						Mode = RPL;
						po = 0;
						memset(replacing, 0, RPlen);
						pre_mode = 0;
					}
				}
				else
				{
					Mode = EDI;
					MessageBox(NULL, TEXT("Warning"), TEXT("Not found!"), 0);
				}
				menukey = 0;
			}

		}

	}
	WaitForSingleObject(hThread1, INFINITE);//等待线程结束
	CloseHandle(hThread1);//无须控制线程时删除此句柄，可防止内核对象泄露。
}
unsigned __stdcall getInput(void* pArguments)
{
	while (sys)
	{
		if (start.rowplace != fin.rowplace || start.heapplace != fin.heapplace)
		{
			copy();
		}
		if (Mode == FIL)//欢迎（退出）界面
			welcome();
		else if (Mode == INP)//打开文件
			openfile();
		else if (Mode == INPN)//新建文件
			newfile();
		else if (Mode == INPL)
			route();
		else if (Mode == EDI)//编辑界面
			print();
		else if (Mode == SAV)
			savefile();
		else if (Mode == RPL)
			repl();
		else if (Mode == FIN)
			searc();
		waitKey(10);
		if (menukey != 0)
		{
			if (menukey == 1)
				block_fun(3);
			else if (menukey == 2)
				block_fun(22);
			else if (menukey == 3)
				block_fun(24);
			else if (menukey == 4)
				block_fun(1);
			else if (menukey == 5)
				block_fun(6);
			else if (menukey == 6)
				block_fun(26);
			menukey = 0;
			rclip.clear();
		}
	}
	return 0;
}