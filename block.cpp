#include<windows.h>
#include"main.h"
#include"function.h"
#include"print.h"
#include"block.h"
using namespace std;
extern Rowlist *head;
int clipinput = 0;
extern Location start;
extern Location fin;
extern int pre_mode;
extern Location cur;//���Ŀ�ʼ�������͵�ǰλ��
extern Location location[Max];
extern int menukey;// 1Ϊ���� 2Ϊճ�� 3Ϊ���� 4Ϊȫѡ
extern int po;
vector <char> clip;//�����壨�ü�������ȷʵ�Ѿ����Ƶ����ݣ�
vector<char>rclip;//�����壨�ü�������δ���Ƶ����ݣ�
int jud_del = 0;
extern int Mode;
extern char replacing[RPlen];
bool copy(void)
{
	int i;//����ѭ�� 
	int len;//����ͳ���ַ��ĳ���
	len = 0;
	Location temp;
	Location start_1;
	Location fin_1;
	Rowlist *current;
	Rowlist *prev;
	current = head->next;
	prev = NULL;
	/********ʹ��startΪ��ʼ��finΪ����λ��************/
	start_1 = start;
	fin_1 = fin;
	rclip.clear();//�����������
				  //cout << "1" << endl;
				  //��δ���п����
				  //cout << "1��ʼ��" << start_1.heapplace << "������" << fin_1.heapplace << endl;
	if (start.rowplace == fin.rowplace&& start.heapplace == fin.heapplace)
		return false;
	cout << start.rowplace << endl;
	cout << start.heapplace << endl;
	cout << fin.rowplace << endl;
	cout << fin.heapplace << endl;
	if (start_1.rowplace == fin_1.rowplace&&start_1.heapplace > fin_1.heapplace)
	{
		temp = start_1;
		start_1 = fin_1;
		fin_1 = temp;
		current = start_1.rowplace;
		//cout << "1.1" << endl;
	}
	else
	{
		//cout << "1.2" << endl;
		while (current != NULL)
		{
			//cout << "1.3" << endl;
			if (start_1.rowplace == current)
				break;
			else if (fin_1.rowplace == current)
			{
				temp = start_1;
				start_1 = fin_1;
				fin_1 = temp;
				break;
			}
			current = current->next;
		}
	}
	prev = current;//prev��ʱΪ��ʼ
	if (start.rowplace != fin_1.rowplace)//��start fin��ͬ��
		while (prev->next != fin_1.rowplace)//����fin��ǰһ��
		{
			prev = prev->next;
		}

	//cout << "2" << endl;
	//cout << "2��ʼ��" << start_1.heapplace << "������" << fin_1.heapplace << endl;
	/******�ض�λstartָ��ӿ�ʼ���Ƶ�ch��ʼ*****/
	if (current->heap[start_1.heapplace] == '\n'
		&&start_1.heapplace == current->heaplen - 1)
	{
		current = current->next;
		start_1.rowplace = start_1.rowplace->next;
		start_1.heapplace = 0;//ָ����һ�е�һ�� 
	}
	//cout << "3��ʼ��" << start_1.heapplace << "������" << fin_1.heapplace << endl;
	/*******�ض�λfin_1��λ��Ϊfin��ǰһ��********/
	if (fin_1.heapplace == 0)
	{
		fin_1.rowplace = prev;
		fin_1.heapplace = prev->heaplen - 1;//fin_1��λΪ��һ�����һ��
	}
	else
	{
		//cout <<"����λ�õ���λ��"<< fin_1.heapplace  << endl;
		if ((unsigned char)fin_1.rowplace->heap[fin_1.heapplace - 1] > 0x7F)//������λΪ����
		{
			fin_1.heapplace = fin_1.heapplace - 2;
			//cout << "������" << fin_1.heapplace;
		}
		else
		{
			fin_1.heapplace = fin_1.heapplace - 1;
			//cout << "������" << fin_1.heapplace;
		}
	}
	//cout << "3" << endl;
	while (current != NULL && current != fin_1.rowplace->next)
	{
		//cout << "circle" << endl;
		if (start_1.rowplace == fin_1.rowplace)//start��endͬ�� 
		{
			for (i = start_1.heapplace; i <= fin_1.heapplace; i++)
			{
				rclip.push_back(current->heap[i]);
			}
			if ((unsigned char)fin_1.rowplace->heap[fin_1.heapplace]> 0x7F)
				rclip.push_back(fin_1.rowplace->heap[fin_1.heapplace + 1]);
			break;
		}
		else//start��end��ͬ�� 
		{
			if (current == start_1.rowplace)
				//��ζ�Ŵ˶δ�start.heapplace��ʼ���Ƶ�β
				for (i = start_1.heapplace; i <= current->heaplen - 1; i++)
				{
					rclip.push_back(current->heap[i]);
				}

			else if (current != start_1.rowplace&&current != fin_1.rowplace)
				//��ζ�Ŵ˶δ�0��ʼ���Ƶ�β
				for (i = 0; i <= current->heaplen - 1; i++)
				{
					rclip.push_back(current->heap[i]);
				}
			else if (current == fin_1.rowplace)
				//��ζ�Ŵ˶δ�0��ʼ���Ƶ�end.heapplace
			{
				for (i = 0; i <= fin_1.heapplace; i++)
				{
					rclip.push_back(current->heap[i]);
				}
				if ((unsigned char)fin_1.rowplace->heap[fin_1.heapplace]> 0x7F)
					rclip.push_back(fin_1.rowplace->heap[fin_1.heapplace + 1]);
			}
		}//start��end��ͬ�� 
		current = current->next;
	}
	return true;
}
bool block_fun(int key)//���������
{
	/******��������ܼ�˵��*****/
	/*
	ctrl+A for check all;
	ctrl+C for copy;
	ctrl+V for paste;
	ctrl+D for delete;
	ctrl+X for cut;
	ctrl+F for find;
	ctrl+Z for cancel;
	ctrl+N for create a new file;
	�������ȼ���ASKII�룺
	Backspace->8;
	Enter->13;
	Esc->27;
	*/
	/****�����жϿ�������ȡ��*****/
	Location temp;
	Location start_1;
	Location fin_1;
	Rowlist *current;
	Rowlist *curprev;
	Rowlist *prev;
	Location sdel;//Ҫɾ����λ��
	int i, j, k;
	current = head->next;
	prev = NULL;
	start_1 = start;
	fin_1 = fin;
	if (key == 0)//����δѡ�й��ܼ�����ռ����� 
	{
		return true;
	}

	//******************************************************************************************************************
	if (key == 1)//ȫѡ
	{
		start.rowplace = head->next;
		start.heapplace = 0;
		current = head->next;
		while (current->next != NULL)
			current = current->next;
		fin.rowplace = current;
		fin.heapplace = current->heaplen;
		menukey = 0;
	}

	//***************************************************************************************************************
	if (key == 3) //��ѡʱ�Ѿ����Ƶ��˼����� ����(����ʱҲҪ�õ���һ����)
	{
		int cc = 0;
		if (location[0].rowplace)
		{
			while (cc < Max)
			{
				location[cc].rowplace = NULL;
				cc++;
			}
		}
		int i;
		clip.clear();//��ռ�����
		for (i = 0; i < rclip.size(); i++)
			clip.push_back(rclip[i]);//����ʱ�����������ճ������
		start = fin;
		cprintest();//����ʹ��
		rclip.clear();//��ռ�����
		printest();//����
		menukey = 0;
	}

	//***************************************************************************************************************
	if (key == 4)//ɾ��(����ʱҲҪ�õ���һ����)
	{
		//cout << "24" << endl;
		if (start.heapplace == fin.heapplace&&start.rowplace == fin.rowplace)//û��ѡ���κζ���
			return false;
		//======================�ض�λ��start,fin�����£�==============================================
		if (start_1.rowplace == fin_1.rowplace&&start_1.heapplace > fin_1.heapplace)
		{
			temp = start_1;
			start_1 = fin_1;
			fin_1 = temp;
			current = start_1.rowplace;
			//cout << "1.1" << endl;
		}
		else
		{
			//cout << "1.2" << endl;
			while (current != NULL)
			{
				//cout << "1.3" << endl;
				if (start_1.rowplace == current)//�ȱ�����start
					break;
				else if (fin_1.rowplace == current)//�ȱ�����fin�����滻
				{
					temp = start_1;
					start_1 = fin_1;
					fin_1 = temp;
					break;
				}
				current = current->next;
			}
		}
		prev = current;//prev��ʱΪ��ʼ
		if (start_1.rowplace != fin_1.rowplace)//��start fin��ͬ��
			while (prev->next != fin_1.rowplace)//����fin��ǰһ�У�Ŀ����Ϊ�˷�ֹfin���ֵ�λ������һ�еĿ�ʼ
			{
				prev = prev->next;
			}

		//cout << "2" << endl;

		/*******�ض�λfin_1��λ��Ϊfin��ǰһ��********/
		if (fin_1.heapplace == 0)
		{
			//fin_1.rowplace = prev;
			//fin_1.heapplace = prev->heaplen - 1;//fin_1��λΪ��һ�����һ��
			;
		}
		else
		{

			if ((unsigned char)fin_1.rowplace->heap[fin_1.heapplace - 1]> 0x7F)//������λΪ����
				fin_1.heapplace = fin_1.heapplace - 2;
			else
				fin_1.heapplace = fin_1.heapplace - 1;
		}
		//========================�ض�λstart,fin�����ϣ�=====================================================
		//jud_del = 1;//ɾ�����ܿ�ʼ

		//jud_del = 0;//ɾ�����ܽ���
		//fin = start;//������ʼ�ͽ���λ��


		prev = head;
		current = head->next;
		while (current != NULL && current != start_1.rowplace)
		{
			prev = current;
			current = current->next;
		}                          //������start_1��ǰһ��
		current = start_1.rowplace;
		int restlen;
		int breslen;
		while (current != NULL && current != fin_1.rowplace->next)
		{
			if (start_1.rowplace == fin_1.rowplace)//start��endͬ�� 
			{
				i = start_1.heapplace;
				j = fin_1.heapplace;
				breslen = j - i;
				cout << "i:" << i << " " << "j:" << j << endl;
				restlen = current->heaplen;//���ڴ洢�г��ȱ仯֮ǰ�ĳ���
				cout << "reslen" << restlen << endl;
				if ((unsigned char)current->heap[j] > 0x7F)//�����ַ�
				{
					for (k = j + 2; k < current->heaplen; k++)//�ӽ�β��2����ʼ��ǰ��
					{
						current->heap[i] = current->heap[k];
						i++;
					}
					current->heaplen = current->heaplen - (breslen + 2);
				}
				else
				{
					for (k = j + 1; k < current->heaplen; k++)//�ӽ�β��1����ʼ��ǰ��
					{
						current->heap[i] = current->heap[k];
						cout << "i:" << i << " " << "k:" << k << endl;
						i++;
					}
					current->heaplen = current->heaplen - (breslen + 1);
					cout << "ɾ�����ȣ�" << breslen + 1 << endl;//����
					cout << "���ڳ��ȣ�" << current->heaplen;//����
				}
				for (k = i; k < restlen; k++)
				{
					current->heap[i] = 0;//�ÿ�
					cout << "k(�ÿ�):" << k << endl;
				}
				current = current->next;//������һ�У�Ŀ�ģ��˳�ѭ��
			}
			else
			{
				if (current == start_1.rowplace)
					//��ζ�Ŵ˶δ�start.heapplace��ʼɾ����β
				{
					if (start_1.heapplace == 0)//Ҫɾ��start��������
					{//current���䣬��ʱcurrent��Ҫɾ���Ļ�������else if����ɾ��
						start_1.rowplace = prev;
						start_1.rowplace->next = fin_1.rowplace->next;//�Ⱦ���������
																	  //free(start_1.rowplace);//ɾ��������
																	  //start_1.rowplace = NULL;
					}
					else//
					{
						i = start_1.heapplace;
						current = current->next;//current��Ϊ��һ��
						start_1.rowplace->next = fin_1.rowplace->next;//�Ƚ�����������
						cout << "start ����:" << i << endl;
						start_1.rowplace->heap[i] = '\n';
						start_1.rowplace->heaplen = i + 1;//�ı䳤��
					}
				}
				else if (current != start_1.rowplace&&current != fin_1.rowplace)
					//��ζ�Ŵ˶δ�0��ʼɾ����β
				{
					curprev = current;
					current = current->next;
					cout << "ɾ������" << endl;
					free(curprev);
					curprev = NULL;
				}
				else if (current == fin_1.rowplace)
					//��ζ�Ŵ˶δ�0��ʼɾ����end.heapplace
				{
					i = start_1.rowplace->heaplen - 1;//start_1���ȣ�-1����Ϊ��\n��Ҫȥ��
					j = fin_1.heapplace;
					restlen = current->heaplen;
					cout << "ɾ��fin" << endl;
					/*
					if ((unsigned char)current->heap[j] > 0x7F)//�����ַ�
					{
					for (k = j + 2; k < current->heaplen; k++)//�ӽ�β��2����ʼ��ǰ��
					{
					current->heap[i] = current->heap[k];
					i++;
					}
					current->heaplen = current->heaplen - (j + 2);//ɾ������г�
					}
					else
					{
					for (k = j + 1; k < current->heaplen; k++)//�ӽ�β��1����ʼ��ǰ��
					{
					current->heap[i] = current->heap[k];
					i++;
					}
					current->heaplen = current->heaplen - (j + 1);//ɾ������г�
					}
					*/
					if ((unsigned char)current->heap[j] > 0x7F)//�����ַ�
					{
						for (k = j + 2; k < restlen; k++)
						{
							start_1.rowplace->heap[i] = current->heap[k];
							cout << "��䣺" << i << endl;
							i++;
						}
						j = j + 2;//ɾȥ�ĳ���
					}
					else
					{
						if (fin_1.rowplace->heap[0] == '\n')
						{
							start_1.rowplace->heap[i] = '\n';
							i++;
						}
						else
						{
							for (k = j + 1; k < restlen; k++)
							{
								start_1.rowplace->heap[i] = current->heap[k];
								cout << "��䣺" << i << endl;
								i++;
							}
						}
						j = j + 1;//ɾȥ�ĳ���
					}
					start_1.rowplace->heaplen = i;
					free(current);
					current = NULL;//������һ�У�Ŀ�ģ��˳�ѭ��

				}
			}
		}
		fin = start_1;
		start = start_1;//������ʼ�ͽ���λ��
		cout << "Delete:" << endl;//����ʹ��
		cprintest();//����ʹ��
		rclip.clear();//��ʱ�����������
	}

	//***************************************************************************************************************
	else if (key == 22)//ճ��
	{
		//clipinput = 1;
		clipinput = 1;
		insert(start);
		clipinput = 0;
		menukey = 0;
	}  //����ʱ�����Ѿ�����clip�����ˣ�����ʵ�ֲ����뿴function.cpp��insert����  

	   //**************************************************************************************************************
	else if (key == 24)
	{
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

		clip.clear();//��ռ�����
		for (i = 0; i < rclip.size(); i++)
			clip.push_back(rclip[i]);//����ʱ�����������ճ������
									 //start = fin;
		cprintest();//����ʹ��
		rclip.clear();//��ռ�����
		printest();//����
				   //cout << "24" << endl;
		if (start.heapplace == fin.heapplace&&start.rowplace == fin.rowplace)//û��ѡ���κζ���
			return false;
		//======================�ض�λ��start,fin�����£�==============================================
		if (start_1.rowplace == fin_1.rowplace&&start_1.heapplace > fin_1.heapplace)
		{
			temp = start_1;
			start_1 = fin_1;
			fin_1 = temp;
			current = start_1.rowplace;
			//cout << "1.1" << endl;
		}
		else
		{
			//cout << "1.2" << endl;
			while (current != NULL)
			{
				//cout << "1.3" << endl;
				if (start_1.rowplace == current)//�ȱ�����start
					break;
				else if (fin_1.rowplace == current)//�ȱ�����fin�����滻
				{
					temp = start_1;
					start_1 = fin_1;
					fin_1 = temp;
					break;
				}
				current = current->next;
			}
		}
		prev = current;//prev��ʱΪ��ʼ
		if (start_1.rowplace != fin_1.rowplace)//��start fin��ͬ��
			while (prev->next != fin_1.rowplace)//����fin��ǰһ�У�Ŀ����Ϊ�˷�ֹfin���ֵ�λ������һ�еĿ�ʼ
			{
				prev = prev->next;
			}

		//cout << "2" << endl;

		/*******�ض�λfin_1��λ��Ϊfin��ǰһ��********/
		if (fin_1.heapplace == 0)
		{
			//fin_1.rowplace = prev;
			//fin_1.heapplace = prev->heaplen - 1;//fin_1��λΪ��һ�����һ��
			;
		}
		else
		{

			if ((unsigned char)fin_1.rowplace->heap[fin_1.heapplace - 1]> 0x7F)//������λΪ����
				fin_1.heapplace = fin_1.heapplace - 2;
			else
				fin_1.heapplace = fin_1.heapplace - 1;
		}
		//========================�ض�λstart,fin�����ϣ�=====================================================
		//jud_del = 1;//ɾ�����ܿ�ʼ

		//jud_del = 0;//ɾ�����ܽ���
		//fin = start;//������ʼ�ͽ���λ��


		prev = head;
		current = head->next;
		while (current != NULL && current != start_1.rowplace)
		{
			prev = current;
			current = current->next;
		}                          //������start_1��ǰһ��
		current = start_1.rowplace;
		int restlen;
		int breslen;
		while (current != NULL && current != fin_1.rowplace->next)
		{
			if (start_1.rowplace == fin_1.rowplace)//start��endͬ�� 
			{
				i = start_1.heapplace;
				j = fin_1.heapplace;
				breslen = j - i;
				cout << "i:" << i << " " << "j:" << j << endl;
				restlen = current->heaplen;//���ڴ洢�г��ȱ仯֮ǰ�ĳ���
				cout << "reslen" << restlen << endl;
				if ((unsigned char)current->heap[j] > 0x7F)//�����ַ�
				{
					for (k = j + 2; k < current->heaplen; k++)//�ӽ�β��2����ʼ��ǰ��
					{
						current->heap[i] = current->heap[k];
						i++;
					}
					current->heaplen = current->heaplen - (breslen + 2);
				}
				else
				{
					for (k = j + 1; k < current->heaplen; k++)//�ӽ�β��1����ʼ��ǰ��
					{
						current->heap[i] = current->heap[k];
						cout << "i:" << i << " " << "k:" << k << endl;
						i++;
					}
					current->heaplen = current->heaplen - (breslen + 1);
					cout << "ɾ�����ȣ�" << breslen + 1 << endl;//����
					cout << "���ڳ��ȣ�" << current->heaplen;//����
				}
				for (k = i; k < restlen; k++)
				{
					current->heap[i] = 0;//�ÿ�
					cout << "k(�ÿ�):" << k << endl;
				}
				current = current->next;//������һ�У�Ŀ�ģ��˳�ѭ��
			}
			else
			{
				if (current == start_1.rowplace)
					//��ζ�Ŵ˶δ�start.heapplace��ʼɾ����β
				{
					if (start_1.heapplace == 0)//Ҫɾ��start��������
					{//current���䣬��ʱcurrent��Ҫɾ���Ļ�������else if����ɾ��
						start_1.rowplace = prev;
						start_1.rowplace->next = fin_1.rowplace->next;//�Ⱦ���������
																	  //free(start_1.rowplace);//ɾ��������
																	  //start_1.rowplace = NULL;
					}
					else//
					{
						i = start_1.heapplace;
						current = current->next;//current��Ϊ��һ��
						start_1.rowplace->next = fin_1.rowplace->next;//�Ƚ�����������
						cout << "start ����:" << i << endl;
						start_1.rowplace->heap[i] = '\n';
						start_1.rowplace->heaplen = i + 1;//�ı䳤��
					}
				}
				else if (current != start_1.rowplace&&current != fin_1.rowplace)
					//��ζ�Ŵ˶δ�0��ʼɾ����β
				{
					curprev = current;
					current = current->next;
					cout << "ɾ������" << endl;
					free(curprev);
					curprev = NULL;
				}
				else if (current == fin_1.rowplace)
					//��ζ�Ŵ˶δ�0��ʼɾ����end.heapplace
				{
					i = start_1.rowplace->heaplen - 1;//start_1���ȣ�-1����Ϊ��\n��Ҫȥ��
					j = fin_1.heapplace;
					restlen = current->heaplen;
					cout << "ɾ��fin" << endl;

					if ((unsigned char)current->heap[j] > 0x7F)//�����ַ�
					{
						for (k = j + 2; k < restlen; k++)
						{
							start_1.rowplace->heap[i] = current->heap[k];
							cout << "��䣺" << i << endl;
							i++;
						}
						j = j + 2;//ɾȥ�ĳ���
					}
					else
					{
						if (fin_1.rowplace->heap[0] == '\n')
						{
							start_1.rowplace->heap[i] = '\n';
							i++;
						}
						else
						{
							for (k = j + 1; k < restlen; k++)
							{
								start_1.rowplace->heap[i] = current->heap[k];
								cout << "��䣺" << i << endl;
								i++;
							}
						}
						j = j + 1;//ɾȥ�ĳ���
					}
					start_1.rowplace->heaplen = i;
					free(current);
					current = NULL;//������һ�У�Ŀ�ģ��˳�ѭ��

				}
			}
		}
		fin = start_1;
		start = start_1;//������ʼ�ͽ���λ��
		cout << "Delete:" << endl;//����ʹ��
		cprintest();//����ʹ��
		rclip.clear();//��ʱ�����������
		menukey = 0;
	}


	//****************************************************************************************************************

	else if (key == 6)//����
	{
		//���������п�ѡ�����ҿ�ѡ���ݣ��޿�ѡ���������ݣ���������
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
		if (rclip.size() != 0) {
			cout << "�кܶ�ܶ�bug1";
			for (int opcv = 0; opcv < rclip.size(); opcv++)
				cout << rclip[opcv];
			cout << "==";
			if (search(rclip))//����rclip
			{
				rclip.clear();
				Mode = EDI;
				//for (i = 0; location[i].rowplace != NULL; i++)
				//	clip.push_back(location[i].rowplace->heap[location[i].heapplace]);

				return true;
			}
			else
			{
				rclip.clear();
				return false;
			}
		}
		else {
			Mode = FIN;
			po = 0;
			memset(replacing, 0, RPlen);
			cout << "FIN" << endl;
		}
	}


	//***********************************************************************************************************

	else if (key == 26) {

		//���������п�ѡ�����ҿ�ѡ���ݣ��޿�ѡ���������ݣ���������
		if (rclip.size() != 0) {
			if (search(rclip))//����rclip
			{

				//for (i = 0; location[i].rowplace != NULL; i++)
				//	clip.push_back(location[i].rowplace->heap[location[i].heapplace]);//����function����

				memset(replacing, 0, RPlen);
				po = 0;
				Mode = RPL;
				cout << "RPL" << endl;
				for (int tt = 0; tt < rclip.size(); tt++)
					cout << rclip[tt];//����
				cout << endl;//����
				rclip.clear();
				return true;
			}
			else
			{
				rclip.clear();
				MessageBox(NULL, TEXT("Warning"), TEXT("Not found!"), 0);
				return false;
			}
			rclip.clear();
		}
		else {
			pre_mode = 1;
			Mode = FIN;
			po = 0;
			memset(replacing, 0, RPlen);
			cout << "FIN" << endl;
			//��������Ҫ���ҵ����� ����rclip��

		}

		menukey = 0;
		//rclip.clear();
	}

	//***********************************************************************************************************
	else
	{
		rclip.clear();
		return false;
	}
}
void cprintest(void)
{
	int i;
	int size;
	Rowlist *current;
	current = head;
	current = current->next;
	i = 0;
	size = rclip.size();
	cout << "rclip:" << endl;
	while (i <= size - 1)
	{
		cout << rclip[i];
		i++;
	}
	cout << endl;
	//clip.clear();
}
void printest(void)
{
	int i;
	int size;
	Rowlist *current;
	current = head;
	current = current->next;
	i = 0;
	size = clip.size();
	cout << "clip:" << endl;
	while (i <= size - 1)
	{
		cout << clip[i];
		i++;
	}
	cout << endl;
	//clip.clear();
}
void printest2(void)//��ӡÿһ���Լ���ʼ���ַ�
{
	Rowlist *current;
	int i, j;
	int count = 0;
	current = head->next;
	while (current != NULL && count<15)
	{
		for (i = 0; i < current->heaplen; i++)
		{

			cout << current->heap[i];
		}
		cout << endl;
		current = current->next;
		count++;
	}
}
void printest3(void)//��ӡÿһ���Լ���ʼ���ַ�
{
	Rowlist *current;
	int i, j;
	int count = 0;
	current = head->next;
	while (current != NULL && count<15)
	{
		for (i = 0; i < current->heaplen&&i<6; i++)
		{
			if (i == 5)
			{
				cout << current->heap[i];
				for (j = i + 1; j < current->heaplen && (unsigned char)current->heap[j] > 0x7F; j++)
					cout << current->heap[j];
			}
			else
				cout << current->heap[i];
		}
		cout << "        " << current->heaplen << endl;
		current = current->next;
		count++;
	}
}
void printest4(void)
{
	Rowlist *current;
	int i, j;
	int count = 0;
	current = head->next;
	while (current != NULL && count<15)
	{
		cout << current << endl;
		current = current->next;
		count++;
	}
}