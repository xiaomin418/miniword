/******************�����****************/ 
#include"main.h"
#include"block.h"
/****�õ���Ա���Ӻ��� *****/

/************�ж��Ƿ��ǽ����˿���� **********/

bool copy(void)
{
  	mouse_msg  msg;
  	int row;//ר����������������ڼ��� 
  	int i;//����ѭ�� 
  	int len;//����ͳ���ַ��ĳ���
	len=0; 
  	struct Location start;//��꿪ʼ�߼�λ��
  	struct Location end;//�������߼�λ��
  	struct Location temp;
  	struct Rowlist *current;
  	struct Rowlist *head;
  	start=get_location();//��λ�����߼�λ�� 
	if (mousemsg())
	{
	    msg = getmouse();
	    if(msg.is_up())
	    {
	       end =get_location();	
	    }
	     
	}
	if(start.rowplace==end.rowplace&&start.heapplace==end.heapplace)
	//��δ���п����
	return false; 
	else 
	{
	if(start.rowplace>end.rowplace||
	start.rowplace==end.rowplace&&start.heapplace>end.heapplace)
	//˵���������ʼλ���ڽ���λ��ǰ��
	temp=start;
	start=end;
	end=temp;
	
	current=head->next;
	row=1;
	/***�����ҵ�start��ʼ����������currentָ����****/ 
	  while(current!=NULL)
	  {
	    if(start.rowplace==row)
	    break;
	    else 
	    {
                 current=current->next;
	       row++; 
  	    }
	  }
	/******�ض�λstartָ��ӿ�ʼ���Ƶ�ch��ʼ*****/
	if(current->heap[start.heapplace]=='\n'
	&&start.heapplace==current->maxlen)
	{
	   current=current->next;
	   row++;
	 } 
	 
	while(current!=NULL&&row<=end.rowplace)
	{
	    if(row==end.rowplace)//start��endͬ�� 
	    for(i=start.heapplace;i<=end.heapplace;i++)
	    {
	       clip.push_back(current->heap[i]);
	       len++;
	    }
	    
	    else//start��end��ͬ�� 
	    {
	       if(row==start.rowplace)
	        //��ζ�Ŵ˶δ�start.heapplace��ʼ���Ƶ�β
	       for(i=start.heapplace;i<=current->heaplen-1;i++)
	       {
	       clip.push_back(current->heap[i]);
	       len++;
	       }
	       
	       else if(row!=start.heapplace&&row!=end.heapplace)
	       //��ζ�Ŵ˶δ�0��ʼ���Ƶ�β
	       for(i=0;i<=current->heaplen-1;i++)
	       {
	       clip.push_back(current->heap[i]);
	       len++;
	       }
	       else if(row==end.rowplace)
	       //��ζ�Ŵ˶δ�0��ʼ���Ƶ�end.heapplace
	       for(i=0;i<=end.heapplace;i++)
	       {
	       clip.push_back(current->heap[i]);
	       len++;
	       }
	    }//start��end��ͬ�� 
	    current=current->next;
	    row++;
	}
	start.length=len;
	color.push_back(start);//��������� 
	return true;
    } 
}

bool block_fun(void)//���������
{
    /******��������ܼ�˵��*****/
    /*
    'a' and 'A' for Check all;
    'c' and 'C' for copy;
    'v' and 'V' for paste;
    'x' and 'X' for cut;
    'f' and 'F' for find;
    'z' and 'Z' for cancel;
    'n' and 'N' for create a new file;
    */
    /****�����жϿ�������ȡ��*****/
    if(!func())//����δѡ�й��ܼ�����ռ����� 
    {
    	color.clear();//���color 
	clip.clear(); //�������
	return false; 
    } 
}

void hotkey(void)//�ȼ�����
{
    ;
}
char func(void)
//������������ж�����Ƿ�ѡ���˹��ܼ�
//����ֵ��һ�����ܵ��ַ������û��ѡ�й��ܣ��򷵻�'\0' 
{
	char ch;
	return ch;
 } 
struct Location get_location(void)//��λ����߼�λ��
{
	struct Location a;
	return a;
}

