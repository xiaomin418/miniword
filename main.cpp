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
int row_sum;//������
int word_sum;//������
int para_sum = 0;
int pagestart = 0;
int pageend = SH;//��ӡҳ�Ŀ�ʼ���β
int Mode;//��ǰģʽ
int sys;//ϵͳ�Ƿ�����
int po = 0;
int pre_mode;
int menukey;// 1Ϊ���� 2Ϊճ�� 3Ϊ���� 4Ϊȫѡ
			//���ͣ����߳�1��copy()����������֮��Ϊ�˷�ֹ��δ�����κβ���ʱ���ϵĽ���copy()��lock=1,����copy()
Rowlist *head;
Location start;
Location fin;
Location cur;//���Ŀ�ʼ�������͵�ǰλ��
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
CvScalar *size1 = new CvScalar(aa, bb, cc, dd);//���������ʽ
string a = "A";//�м���demo
double demo = 1.3 * getTextSize(a, font1.fontt, font1.size, 1, font1.baseline).height;//�����м��
																					  //int keydown;//������Ϣ
char keydown;//������Ϣ
char arf[Namelen];//�ļ���
char temp[Namelen];//��ʱ�ļ���
extern vector<char>rclip;
char replacing[RPlen];
unsigned __stdcall getInput(void* pArguments);//���߳����ڽ��ռ���(�����)��Ϣ 
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
		keydown = waitKey(0);//ϵͳ�˳�
		if (Mode == INP)//�½��ļ������ļ���ģʽ
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
		else if (Mode == INPN)//�����ļ������ļ���
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
				//�˴��ǵü���
				Mode = EDI;
			}
		}
		else if (Mode == INPL)//��ȡ�ļ�����·��
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
					arf[po + k] = temp[k];//�ó��ļ�����·��
				if (save())
					MessageBox(NULL, TEXT("FILE"), TEXT("Save successfully!"), 0);
				else
					MessageBox(NULL, TEXT("Warning"), TEXT("Fail!"), 0);
				Mode = FIL;
				cout << "saveas" << endl;//����
				Mode = FIL;
			}
		}
		else if (Mode == EDI)//�༭��ģʽ
		{
			if (keydown == 27)//ϵͳ�˳�
			{
				Mode = SAV;
			}
			else if (keydown > 31 && keydown < 127 || keydown == 13)//����ֱ�������ַ���ʱ��
			{
				//inp = keydown;
				//cout << inp << endl;//���ڲ���ʹ��
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
					cout << inp << endl;//���ڲ���ʹ��
										//cout << keydown << endl;//���ڲ���ʹ��
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
					cout << keydown << endl;//���ڲ���ʹ��
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
				cout << keydown << endl;//���ڲ���
				cout << "else" << endl;
				if (block_fun(keydown))//�����
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
			cout << "�кܶ�ܶ�bug4" << endl;
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
					if (pre_mode != 1)//���Ǵ��滻����
					{
						Mode = EDI;
						pre_mode = 0;
					}
					else if (pre_mode == 1)//���滻����
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
	WaitForSingleObject(hThread1, INFINITE);//�ȴ��߳̽���
	CloseHandle(hThread1);//��������߳�ʱɾ���˾�����ɷ�ֹ�ں˶���й¶��
}
unsigned __stdcall getInput(void* pArguments)
{
	while (sys)
	{
		if (start.rowplace != fin.rowplace || start.heapplace != fin.heapplace)
		{
			copy();
		}
		if (Mode == FIL)//��ӭ���˳�������
			welcome();
		else if (Mode == INP)//���ļ�
			openfile();
		else if (Mode == INPN)//�½��ļ�
			newfile();
		else if (Mode == INPL)
			route();
		else if (Mode == EDI)//�༭����
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