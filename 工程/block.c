/******************块操作****************/ 
#include"main.h"
#include"block.h"
/****用到组员的子函数 *****/

/************判断是否是进行了块操作 **********/

bool copy(void)
{
  	mouse_msg  msg;
  	int row;//专门用来计数行链表第几行 
  	int i;//用于循环 
  	int len;//用于统计字符的长度
	len=0; 
  	struct Location start;//鼠标开始逻辑位置
  	struct Location end;//鼠标结束逻辑位置
  	struct Location temp;
  	struct Rowlist *current;
  	struct Rowlist *head;
  	start=get_location();//定位光标的逻辑位置 
	if (mousemsg())
	{
	    msg = getmouse();
	    if(msg.is_up())
	    {
	       end =get_location();	
	    }
	     
	}
	if(start.rowplace==end.rowplace&&start.heapplace==end.heapplace)
	//即未进行块操作
	return false; 
	else 
	{
	if(start.rowplace>end.rowplace||
	start.rowplace==end.rowplace&&start.heapplace>end.heapplace)
	//说明块操作起始位置在结束位置前面
	temp=start;
	start=end;
	end=temp;
	
	current=head->next;
	row=1;
	/***首先找到start开始的行链表，用current指向它****/ 
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
	/******重定位start指向从开始复制的ch开始*****/
	if(current->heap[start.heapplace]=='\n'
	&&start.heapplace==current->maxlen)
	{
	   current=current->next;
	   row++;
	 } 
	 
	while(current!=NULL&&row<=end.rowplace)
	{
	    if(row==end.rowplace)//start和end同行 
	    for(i=start.heapplace;i<=end.heapplace;i++)
	    {
	       clip.push_back(current->heap[i]);
	       len++;
	    }
	    
	    else//start和end非同行 
	    {
	       if(row==start.rowplace)
	        //意味着此段从start.heapplace开始复制到尾
	       for(i=start.heapplace;i<=current->heaplen-1;i++)
	       {
	       clip.push_back(current->heap[i]);
	       len++;
	       }
	       
	       else if(row!=start.heapplace&&row!=end.heapplace)
	       //意味着此段从0开始复制到尾
	       for(i=0;i<=current->heaplen-1;i++)
	       {
	       clip.push_back(current->heap[i]);
	       len++;
	       }
	       else if(row==end.rowplace)
	       //意味着此段从0开始复制到end.heapplace
	       for(i=0;i<=end.heapplace;i++)
	       {
	       clip.push_back(current->heap[i]);
	       len++;
	       }
	    }//start和end非同行 
	    current=current->next;
	    row++;
	}
	start.length=len;
	color.push_back(start);//插入剪贴板 
	return true;
    } 
}

bool block_fun(void)//块操作功能
{
    /******块操作功能键说明*****/
    /*
    'a' and 'A' for Check all;
    'c' and 'C' for copy;
    'v' and 'V' for paste;
    'x' and 'X' for cut;
    'f' and 'F' for find;
    'z' and 'Z' for cancel;
    'n' and 'N' for create a new file;
    */
    /****首先判断块操作会否取消*****/
    if(!func())//表明未选中功能键，清空剪贴板 
    {
    	color.clear();//清空color 
	clip.clear(); //清空贴板
	return false; 
    } 
}

void hotkey(void)//热键操作
{
    ;
}
char func(void)
//这个函数用于判断鼠标是否选中了功能键
//返回值是一个功能的字符，如果没有选中功能，则返回'\0' 
{
	char ch;
	return ch;
 } 
struct Location get_location(void)//定位光标逻辑位置
{
	struct Location a;
	return a;
}

