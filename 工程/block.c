/******************�����****************/ 
#include"main.h"
#include"block.h"
#include"insert.h"
#include"file.h"

/****�õ���Ա���Ӻ��� *****/

/************�ж��Ƿ��ǽ����˿���� **********/

bool copy(void)
{
  	mouse_msg  msg;
  	int i;//����ѭ�� 
  	int len;//����ͳ���ַ��ĳ���
	len=0; 
  	struct Location start;//��꿪ʼ�߼�λ��
  	struct Location end;//�������߼�λ��
  	struct Location temp;
  	struct Rowlist *current;
  	struct Rowlist *head;
  	start=get_location();//��λ�����߼�λ�� 
	while (!mousemsg())
	{
	    end=get_location();
	    live_blk(start,end);
	}
	msg = getmouse();
	if(msg.is_up())
	{
	  end =get_location();	
	}
	if(start.rowplace==end.rowplace&&start.heapplace==end.heapplace)
	//��δ���п����
	return false; 
	else 
	{
	if(start.rowplace>end.rowplace||
	start.rowplace==end.rowplace&&start.heapplace>end.heapplace)
	//˵���������ʼλ���ڽ���λ��ǰ��
	{
	temp=start;
	start=end;
	end=temp;
          }
	current=head->next;
	/***�����ҵ�start��ʼ����������currentָ����****/ 
	  while(current!=NULL)
	  {
	    if(start.rowplace==current->No)
	    break;
	    else 
	    {
                 current=current->next;
  	    }
	  }
	/******�ض�λstartָ��ӿ�ʼ���Ƶ�ch��ʼ*****/
	if(current->heap[start.heapplace]=='\n'
	&&start.heapplace==current->heaplen-1)
	{
	   current=current->next;
	   start.rowplace= start.rowplace+1;
	   start.heapplace=0;//ָ����һ�е�һ�� 
	 }
	 else
	 {
	 	start.heapplace=start.heapplace+1;//ָ��start����һ�� 
	  } 
	  
	while(current!=NULL&&current->No<=current->No)
	{
	    if(current->No==end.rowplace)//start��endͬ�� 
	    for(i=start.heapplace;i<=end.heapplace;i++)
	    {
	       clip.push_back(current->heap[i]);
	    }
	    
	    else//start��end��ͬ�� 
	    {
	       if(current->No==start.rowplace)
	        //��ζ�Ŵ˶δ�start.heapplace��ʼ���Ƶ�β
	       for(i=start.heapplace;i<=current->heaplen-1;i++)
	       {
	       clip.push_back(current->heap[i]);
	       }
	       
	       else if(current->No!=start.heapplace&&current->No!=end.heapplace)
	       //��ζ�Ŵ˶δ�0��ʼ���Ƶ�β
	       for(i=0;i<=current->heaplen-1;i++)
	       {
	       clip.push_back(current->heap[i]);
	       }
	       else if(current->No==end.rowplace)
	       //��ζ�Ŵ˶δ�0��ʼ���Ƶ�end.heapplace
	       for(i=0;i<=end.heapplace;i++)
	       {
	       clip.push_back(current->heap[i]);
	       }
	    }//start��end��ͬ�� 
	    current=current->next;
	}
	return true;
    } 
}
bool live_blk(struct Location start,struct Location end)//ʵʱ��λ��ѡ������print��ɫ 
{
	int sum; 
	struct Location temp;
	Rowlist *current;
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
	/***�����ҵ�start��ʼ����������currentָ����****/ 
	  while(current!=NULL)
	  {
	    if(start.rowplace==current->No)
	    break;
	    else 
	    {
                 current=current->next;
  	    }
	  }
	/******�ض�λstartָ��ӿ�ʼ���Ƶ�ch��ʼ*****/
	if(current->heap[start.heapplace]=='\n'
	&&start.heapplace==current->heaplen-1)
	{
	   current=current->next;
	   start.rowplace= start.rowplace+1;
	   start.heapplace=0;//ָ����һ�е�һ�� 
	 }
	 else
	 {
	 	start.heapplace=start.heapplace+1;//ָ��start����һ�� 
	  } 
	  
	 sum=0;
	 if(start.rowplace==end.rowplace)
	 sum=end.heapplace-start. heapplace+1;
	 else
	 {
	 	sum=current->heaplen-start.heapplace;
	 	current=current->next;
		 while(current!=NULL&&current->No<end.rowplace)
	 	{
	 		sum=sum+current->heaplen;
		 }
		 if(current!=NULL)
		 sum=sum+end.heapplace+1; 
	 }
	color.push_back(start);//�����ɫ�� 
           }  
           return true; 
}
bool block_fun(char sign)//���������
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
	mouse_msg  msg;//�����Ϣ 
	struct Location inser;//����λ�� 
    /****�����жϿ�������ȡ��*****/
	if (sign == '\0')//����δѡ�й��ܼ�����ռ����� 
	{
		color.clear();//���color 
		//clip.clear(); //�������
		return false;
	}
	else if (sign == 'c' || sign == 'C') //��ѡʱ�Ѿ����Ƶ��˼����� 
	{
	   color.clear();//���color,	ȡ������ 
	   return  true; 
	 } 
	else if(sign=='v'||sign=='V')
	{
		if(!clip.empty())//�����жϼ������Ƿ�������
		return false;
		else
		{
		   inser=get_location();//inser�ǵ�ǰ�������λ�� 
		   insert(inser); 
		}
		return true;
	}
	else if(sign=='d'||sign=='D')
	{
	         if(!clip.empty())//�����жϼ������Ƿ�������
		return false;
		else
		{
		   inser=get_location();//inser�ǵ�ǰ�������λ�� 
		   del(inser); 
		   clip.clear();//��ռ����� 
		} 
		return true;  
	} 
	else if(sign=='x'||sign=='X')
	{
		if(!clip.empty())//�����жϼ������Ƿ�������
		return false;
		else
		{
		   inser=get_location();//inser�ǵ�ǰ�������λ�� 
		   del(inser); 
		} 
		return true; 
	}
	else if(sign=='f'||sign=='F') 
	{
		
		if(search(clip))//����string
		return true;
		else 
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

