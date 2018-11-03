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
extern Location cur;//鼠标的开始，结束和当前位置
extern Location location[Max];
extern int menukey;// 1为复制 2为粘贴 3为剪贴 4为全选
extern int po;
vector <char> clip;//剪贴板（该剪贴板是确实已经复制的内容）
vector<char>rclip;//剪贴板（该剪贴板是未复制的内容）
int jud_del = 0;
extern int Mode;
extern char replacing[RPlen];
bool copy(void)
{
	int i;//用于循环 
	int len;//用于统计字符的长度
	len = 0;
	Location temp;
	Location start_1;
	Location fin_1;
	Rowlist *current;
	Rowlist *prev;
	current = head->next;
	prev = NULL;
	/********使得start为起始，fin为结束位置************/
	start_1 = start;
	fin_1 = fin;
	rclip.clear();//首先清空容器
				  //cout << "1" << endl;
				  //即未进行块操作
				  //cout << "1起始：" << start_1.heapplace << "结束：" << fin_1.heapplace << endl;
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
	prev = current;//prev此时为开始
	if (start.rowplace != fin_1.rowplace)//若start fin不同行
		while (prev->next != fin_1.rowplace)//遍历fin的前一行
		{
			prev = prev->next;
		}

	//cout << "2" << endl;
	//cout << "2起始：" << start_1.heapplace << "结束：" << fin_1.heapplace << endl;
	/******重定位start指向从开始复制的ch开始*****/
	if (current->heap[start_1.heapplace] == '\n'
		&&start_1.heapplace == current->heaplen - 1)
	{
		current = current->next;
		start_1.rowplace = start_1.rowplace->next;
		start_1.heapplace = 0;//指向下一行第一个 
	}
	//cout << "3起始：" << start_1.heapplace << "结束：" << fin_1.heapplace << endl;
	/*******重定位fin_1的位置为fin的前一个********/
	if (fin_1.heapplace == 0)
	{
		fin_1.rowplace = prev;
		fin_1.heapplace = prev->heaplen - 1;//fin_1定位为上一行最后一个
	}
	else
	{
		//cout <<"结束位置的列位置"<< fin_1.heapplace  << endl;
		if ((unsigned char)fin_1.rowplace->heap[fin_1.heapplace - 1] > 0x7F)//倘若定位为中文
		{
			fin_1.heapplace = fin_1.heapplace - 2;
			//cout << "结束：" << fin_1.heapplace;
		}
		else
		{
			fin_1.heapplace = fin_1.heapplace - 1;
			//cout << "结束：" << fin_1.heapplace;
		}
	}
	//cout << "3" << endl;
	while (current != NULL && current != fin_1.rowplace->next)
	{
		//cout << "circle" << endl;
		if (start_1.rowplace == fin_1.rowplace)//start和end同行 
		{
			for (i = start_1.heapplace; i <= fin_1.heapplace; i++)
			{
				rclip.push_back(current->heap[i]);
			}
			if ((unsigned char)fin_1.rowplace->heap[fin_1.heapplace]> 0x7F)
				rclip.push_back(fin_1.rowplace->heap[fin_1.heapplace + 1]);
			break;
		}
		else//start和end非同行 
		{
			if (current == start_1.rowplace)
				//意味着此段从start.heapplace开始复制到尾
				for (i = start_1.heapplace; i <= current->heaplen - 1; i++)
				{
					rclip.push_back(current->heap[i]);
				}

			else if (current != start_1.rowplace&&current != fin_1.rowplace)
				//意味着此段从0开始复制到尾
				for (i = 0; i <= current->heaplen - 1; i++)
				{
					rclip.push_back(current->heap[i]);
				}
			else if (current == fin_1.rowplace)
				//意味着此段从0开始复制到end.heapplace
			{
				for (i = 0; i <= fin_1.heapplace; i++)
				{
					rclip.push_back(current->heap[i]);
				}
				if ((unsigned char)fin_1.rowplace->heap[fin_1.heapplace]> 0x7F)
					rclip.push_back(fin_1.rowplace->heap[fin_1.heapplace + 1]);
			}
		}//start和end非同行 
		current = current->next;
	}
	return true;
}
bool block_fun(int key)//块操作功能
{
	/******块操作功能键说明*****/
	/*
	ctrl+A for check all;
	ctrl+C for copy;
	ctrl+V for paste;
	ctrl+D for delete;
	ctrl+X for cut;
	ctrl+F for find;
	ctrl+Z for cancel;
	ctrl+N for create a new file;
	下面是热键的ASKII码：
	Backspace->8;
	Enter->13;
	Esc->27;
	*/
	/****首先判断块操作会否取消*****/
	Location temp;
	Location start_1;
	Location fin_1;
	Rowlist *current;
	Rowlist *curprev;
	Rowlist *prev;
	Location sdel;//要删除的位置
	int i, j, k;
	current = head->next;
	prev = NULL;
	start_1 = start;
	fin_1 = fin;
	if (key == 0)//表明未选中功能键，清空剪贴板 
	{
		return true;
	}

	//******************************************************************************************************************
	if (key == 1)//全选
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
	if (key == 3) //块选时已经复制到了剪贴板 复制(剪切时也要用到这一功能)
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
		clip.clear();//清空剪贴板
		for (i = 0; i < rclip.size(); i++)
			clip.push_back(rclip[i]);//将临时剪贴板的内容粘贴过来
		start = fin;
		cprintest();//测试使用
		rclip.clear();//清空剪贴板
		printest();//测试
		menukey = 0;
	}

	//***************************************************************************************************************
	if (key == 4)//删除(剪切时也要用到这一功能)
	{
		//cout << "24" << endl;
		if (start.heapplace == fin.heapplace&&start.rowplace == fin.rowplace)//没有选中任何东西
			return false;
		//======================重定位了start,fin（如下）==============================================
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
				if (start_1.rowplace == current)//先遍历到start
					break;
				else if (fin_1.rowplace == current)//先遍历到fin，就替换
				{
					temp = start_1;
					start_1 = fin_1;
					fin_1 = temp;
					break;
				}
				current = current->next;
			}
		}
		prev = current;//prev此时为开始
		if (start_1.rowplace != fin_1.rowplace)//若start fin不同行
			while (prev->next != fin_1.rowplace)//遍历fin的前一行，目的是为了防止fin出现的位置是下一行的开始
			{
				prev = prev->next;
			}

		//cout << "2" << endl;

		/*******重定位fin_1的位置为fin的前一个********/
		if (fin_1.heapplace == 0)
		{
			//fin_1.rowplace = prev;
			//fin_1.heapplace = prev->heaplen - 1;//fin_1定位为上一行最后一个
			;
		}
		else
		{

			if ((unsigned char)fin_1.rowplace->heap[fin_1.heapplace - 1]> 0x7F)//倘若定位为中文
				fin_1.heapplace = fin_1.heapplace - 2;
			else
				fin_1.heapplace = fin_1.heapplace - 1;
		}
		//========================重定位start,fin（如上）=====================================================
		//jud_del = 1;//删除功能开始

		//jud_del = 0;//删除功能结束
		//fin = start;//更新起始和结束位置


		prev = head;
		current = head->next;
		while (current != NULL && current != start_1.rowplace)
		{
			prev = current;
			current = current->next;
		}                          //保存下start_1的前一个
		current = start_1.rowplace;
		int restlen;
		int breslen;
		while (current != NULL && current != fin_1.rowplace->next)
		{
			if (start_1.rowplace == fin_1.rowplace)//start和end同行 
			{
				i = start_1.heapplace;
				j = fin_1.heapplace;
				breslen = j - i;
				cout << "i:" << i << " " << "j:" << j << endl;
				restlen = current->heaplen;//用于存储行长度变化之前的长度
				cout << "reslen" << restlen << endl;
				if ((unsigned char)current->heap[j] > 0x7F)//中文字符
				{
					for (k = j + 2; k < current->heaplen; k++)//从结尾后2个开始往前移
					{
						current->heap[i] = current->heap[k];
						i++;
					}
					current->heaplen = current->heaplen - (breslen + 2);
				}
				else
				{
					for (k = j + 1; k < current->heaplen; k++)//从结尾后1个开始往前移
					{
						current->heap[i] = current->heap[k];
						cout << "i:" << i << " " << "k:" << k << endl;
						i++;
					}
					current->heaplen = current->heaplen - (breslen + 1);
					cout << "删减长度：" << breslen + 1 << endl;//测试
					cout << "现在长度：" << current->heaplen;//测试
				}
				for (k = i; k < restlen; k++)
				{
					current->heap[i] = 0;//置空
					cout << "k(置空):" << k << endl;
				}
				current = current->next;//遍历下一行，目的：退出循环
			}
			else
			{
				if (current == start_1.rowplace)
					//意味着此段从start.heapplace开始删除到尾
				{
					if (start_1.heapplace == 0)//要删掉start的行链表
					{//current不变，此时current是要删除的会在下面else if进行删除
						start_1.rowplace = prev;
						start_1.rowplace->next = fin_1.rowplace->next;//先就连接起来
																	  //free(start_1.rowplace);//删除行链表
																	  //start_1.rowplace = NULL;
					}
					else//
					{
						i = start_1.heapplace;
						current = current->next;//current置为下一个
						start_1.rowplace->next = fin_1.rowplace->next;//先将它连接起来
						cout << "start 长度:" << i << endl;
						start_1.rowplace->heap[i] = '\n';
						start_1.rowplace->heaplen = i + 1;//改变长度
					}
				}
				else if (current != start_1.rowplace&&current != fin_1.rowplace)
					//意味着此段从0开始删除到尾
				{
					curprev = current;
					current = current->next;
					cout << "删除链表" << endl;
					free(curprev);
					curprev = NULL;
				}
				else if (current == fin_1.rowplace)
					//意味着此段从0开始删除到end.heapplace
				{
					i = start_1.rowplace->heaplen - 1;//start_1长度：-1是因为‘\n’要去掉
					j = fin_1.heapplace;
					restlen = current->heaplen;
					cout << "删除fin" << endl;
					/*
					if ((unsigned char)current->heap[j] > 0x7F)//中文字符
					{
					for (k = j + 2; k < current->heaplen; k++)//从结尾后2个开始往前移
					{
					current->heap[i] = current->heap[k];
					i++;
					}
					current->heaplen = current->heaplen - (j + 2);//删除后的行长
					}
					else
					{
					for (k = j + 1; k < current->heaplen; k++)//从结尾后1个开始往前移
					{
					current->heap[i] = current->heap[k];
					i++;
					}
					current->heaplen = current->heaplen - (j + 1);//删除后的行长
					}
					*/
					if ((unsigned char)current->heap[j] > 0x7F)//中文字符
					{
						for (k = j + 2; k < restlen; k++)
						{
							start_1.rowplace->heap[i] = current->heap[k];
							cout << "填充：" << i << endl;
							i++;
						}
						j = j + 2;//删去的长度
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
								cout << "填充：" << i << endl;
								i++;
							}
						}
						j = j + 1;//删去的长度
					}
					start_1.rowplace->heaplen = i;
					free(current);
					current = NULL;//遍历下一行，目的：退出循环

				}
			}
		}
		fin = start_1;
		start = start_1;//更新起始和结束位置
		cout << "Delete:" << endl;//测试使用
		cprintest();//测试使用
		rclip.clear();//临时剪贴板置清空
	}

	//***************************************************************************************************************
	else if (key == 22)//粘贴
	{
		//clipinput = 1;
		clipinput = 1;
		insert(start);
		clipinput = 0;
		menukey = 0;
	}  //复制时内容已经存在clip里面了，具体实现操作请看function.cpp的insert函数  

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

		clip.clear();//清空剪贴板
		for (i = 0; i < rclip.size(); i++)
			clip.push_back(rclip[i]);//将临时剪贴板的内容粘贴过来
									 //start = fin;
		cprintest();//测试使用
		rclip.clear();//清空剪贴板
		printest();//测试
				   //cout << "24" << endl;
		if (start.heapplace == fin.heapplace&&start.rowplace == fin.rowplace)//没有选中任何东西
			return false;
		//======================重定位了start,fin（如下）==============================================
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
				if (start_1.rowplace == current)//先遍历到start
					break;
				else if (fin_1.rowplace == current)//先遍历到fin，就替换
				{
					temp = start_1;
					start_1 = fin_1;
					fin_1 = temp;
					break;
				}
				current = current->next;
			}
		}
		prev = current;//prev此时为开始
		if (start_1.rowplace != fin_1.rowplace)//若start fin不同行
			while (prev->next != fin_1.rowplace)//遍历fin的前一行，目的是为了防止fin出现的位置是下一行的开始
			{
				prev = prev->next;
			}

		//cout << "2" << endl;

		/*******重定位fin_1的位置为fin的前一个********/
		if (fin_1.heapplace == 0)
		{
			//fin_1.rowplace = prev;
			//fin_1.heapplace = prev->heaplen - 1;//fin_1定位为上一行最后一个
			;
		}
		else
		{

			if ((unsigned char)fin_1.rowplace->heap[fin_1.heapplace - 1]> 0x7F)//倘若定位为中文
				fin_1.heapplace = fin_1.heapplace - 2;
			else
				fin_1.heapplace = fin_1.heapplace - 1;
		}
		//========================重定位start,fin（如上）=====================================================
		//jud_del = 1;//删除功能开始

		//jud_del = 0;//删除功能结束
		//fin = start;//更新起始和结束位置


		prev = head;
		current = head->next;
		while (current != NULL && current != start_1.rowplace)
		{
			prev = current;
			current = current->next;
		}                          //保存下start_1的前一个
		current = start_1.rowplace;
		int restlen;
		int breslen;
		while (current != NULL && current != fin_1.rowplace->next)
		{
			if (start_1.rowplace == fin_1.rowplace)//start和end同行 
			{
				i = start_1.heapplace;
				j = fin_1.heapplace;
				breslen = j - i;
				cout << "i:" << i << " " << "j:" << j << endl;
				restlen = current->heaplen;//用于存储行长度变化之前的长度
				cout << "reslen" << restlen << endl;
				if ((unsigned char)current->heap[j] > 0x7F)//中文字符
				{
					for (k = j + 2; k < current->heaplen; k++)//从结尾后2个开始往前移
					{
						current->heap[i] = current->heap[k];
						i++;
					}
					current->heaplen = current->heaplen - (breslen + 2);
				}
				else
				{
					for (k = j + 1; k < current->heaplen; k++)//从结尾后1个开始往前移
					{
						current->heap[i] = current->heap[k];
						cout << "i:" << i << " " << "k:" << k << endl;
						i++;
					}
					current->heaplen = current->heaplen - (breslen + 1);
					cout << "删减长度：" << breslen + 1 << endl;//测试
					cout << "现在长度：" << current->heaplen;//测试
				}
				for (k = i; k < restlen; k++)
				{
					current->heap[i] = 0;//置空
					cout << "k(置空):" << k << endl;
				}
				current = current->next;//遍历下一行，目的：退出循环
			}
			else
			{
				if (current == start_1.rowplace)
					//意味着此段从start.heapplace开始删除到尾
				{
					if (start_1.heapplace == 0)//要删掉start的行链表
					{//current不变，此时current是要删除的会在下面else if进行删除
						start_1.rowplace = prev;
						start_1.rowplace->next = fin_1.rowplace->next;//先就连接起来
																	  //free(start_1.rowplace);//删除行链表
																	  //start_1.rowplace = NULL;
					}
					else//
					{
						i = start_1.heapplace;
						current = current->next;//current置为下一个
						start_1.rowplace->next = fin_1.rowplace->next;//先将它连接起来
						cout << "start 长度:" << i << endl;
						start_1.rowplace->heap[i] = '\n';
						start_1.rowplace->heaplen = i + 1;//改变长度
					}
				}
				else if (current != start_1.rowplace&&current != fin_1.rowplace)
					//意味着此段从0开始删除到尾
				{
					curprev = current;
					current = current->next;
					cout << "删除链表" << endl;
					free(curprev);
					curprev = NULL;
				}
				else if (current == fin_1.rowplace)
					//意味着此段从0开始删除到end.heapplace
				{
					i = start_1.rowplace->heaplen - 1;//start_1长度：-1是因为‘\n’要去掉
					j = fin_1.heapplace;
					restlen = current->heaplen;
					cout << "删除fin" << endl;

					if ((unsigned char)current->heap[j] > 0x7F)//中文字符
					{
						for (k = j + 2; k < restlen; k++)
						{
							start_1.rowplace->heap[i] = current->heap[k];
							cout << "填充：" << i << endl;
							i++;
						}
						j = j + 2;//删去的长度
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
								cout << "填充：" << i << endl;
								i++;
							}
						}
						j = j + 1;//删去的长度
					}
					start_1.rowplace->heaplen = i;
					free(current);
					current = NULL;//遍历下一行，目的：退出循环

				}
			}
		}
		fin = start_1;
		start = start_1;//更新起始和结束位置
		cout << "Delete:" << endl;//测试使用
		cprintest();//测试使用
		rclip.clear();//临时剪贴板置清空
		menukey = 0;
	}


	//****************************************************************************************************************

	else if (key == 6)//查找
	{
		//！！！！有块选，查找快选内容，无快选，输入内容！！！！！
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
			cout << "有很多很多bug1";
			for (int opcv = 0; opcv < rclip.size(); opcv++)
				cout << rclip[opcv];
			cout << "==";
			if (search(rclip))//查找rclip
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

		//！！！！有块选，查找快选内容，无快选，输入内容！！！！！
		if (rclip.size() != 0) {
			if (search(rclip))//查找rclip
			{

				//for (i = 0; location[i].rowplace != NULL; i++)
				//	clip.push_back(location[i].rowplace->heap[location[i].heapplace]);//用于function功能

				memset(replacing, 0, RPlen);
				po = 0;
				Mode = RPL;
				cout << "RPL" << endl;
				for (int tt = 0; tt < rclip.size(); tt++)
					cout << rclip[tt];//测试
				cout << endl;//测试
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
			//弹框，输入要查找的内容 放在rclip中

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
void printest2(void)//打印每一行以及开始的字符
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
void printest3(void)//打印每一行以及开始的字符
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