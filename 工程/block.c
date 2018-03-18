/******************块操作****************/ 
#include"main.h"
#include"block.h"
#include"insert.h"
#include"file.h"

/****用到组员的子函数 *****/

/************判断是否是进行了块操作 **********/

bool copy(void)
{
  	mouse_msg  msg;
  	int i;//用于循环 
  	int len;//用于统计字符的长度
	len=0; 
  	struct Location start;//鼠标开始逻辑位置
  	struct Location end;//鼠标结束逻辑位置
  	struct Location temp;
  	struct Rowlist *current;
  	struct Rowlist *head;
  	start=get_location();//定位光标的逻辑位置 
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
	//即未进行块操作
	return false; 
	else 
	{
	if(start.rowplace>end.rowplace||
	start.rowplace==end.rowplace&&start.heapplace>end.heapplace)
	//说明块操作起始位置在结束位置前面
	{
	temp=start;
	start=end;
	end=temp;
          }
	current=head->next;
	/***首先找到start开始的行链表，用current指向它****/ 
	  while(current!=NULL)
	  {
	    if(start.rowplace==current->No)
	    break;
	    else 
	    {
                 current=current->next;
  	    }
	  }
	/******重定位start指向从开始复制的ch开始*****/
	if(current->heap[start.heapplace]=='\n'
	&&start.heapplace==current->heaplen-1)
	{
	   current=current->next;
	   start.rowplace= start.rowplace+1;
	   start.heapplace=0;//指向下一行第一个 
	 }
	 else
	 {
	 	start.heapplace=start.heapplace+1;//指向start的下一个 
	  } 
	  
	while(current!=NULL&&current->No<=current->No)
	{
	    if(current->No==end.rowplace)//start和end同行 
	    for(i=start.heapplace;i<=end.heapplace;i++)
	    {
	       clip.push_back(current->heap[i]);
	    }
	    
	    else//start和end非同行 
	    {
	       if(current->No==start.rowplace)
	        //意味着此段从start.heapplace开始复制到尾
	       for(i=start.heapplace;i<=current->heaplen-1;i++)
	       {
	       clip.push_back(current->heap[i]);
	       }
	       
	       else if(current->No!=start.heapplace&&current->No!=end.heapplace)
	       //意味着此段从0开始复制到尾
	       for(i=0;i<=current->heaplen-1;i++)
	       {
	       clip.push_back(current->heap[i]);
	       }
	       else if(current->No==end.rowplace)
	       //意味着此段从0开始复制到end.heapplace
	       for(i=0;i<=end.heapplace;i++)
	       {
	       clip.push_back(current->heap[i]);
	       }
	    }//start和end非同行 
	    current=current->next;
	}
	return true;
    } 
}
bool live_blk(struct Location start,struct Location end)//实时定位块选，方便print变色 
{
	int sum; 
	struct Location temp;
	Rowlist *current;
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
	/***首先找到start开始的行链表，用current指向它****/ 
	  while(current!=NULL)
	  {
	    if(start.rowplace==current->No)
	    break;
	    else 
	    {
                 current=current->next;
  	    }
	  }
	/******重定位start指向从开始复制的ch开始*****/
	if(current->heap[start.heapplace]=='\n'
	&&start.heapplace==current->heaplen-1)
	{
	   current=current->next;
	   start.rowplace= start.rowplace+1;
	   start.heapplace=0;//指向下一行第一个 
	 }
	 else
	 {
	 	start.heapplace=start.heapplace+1;//指向start的下一个 
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
	color.push_back(start);//插入变色区 
           }  
           return true; 
}
bool block_fun(char sign)//块操作功能
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
	mouse_msg  msg;//鼠标消息 
	struct Location inser;//插入位置 
    /****首先判断块操作会否取消*****/
	if (sign == '\0')//表明未选中功能键，清空剪贴板 
	{
		color.clear();//清空color 
		//clip.clear(); //清空贴板
		return false;
	}
	else if (sign == 'c' || sign == 'C') //块选时已经复制到了剪贴板 
	{
	   color.clear();//清空color,	取消高亮 
	   return  true; 
	 } 
	else if(sign=='v'||sign=='V')
	{
		if(!clip.empty())//首先判断剪贴板是否有内容
		return false;
		else
		{
		   inser=get_location();//inser是当前光标所在位置 
		   insert(inser); 
		}
		return true;
	}
	else if(sign=='d'||sign=='D')
	{
	         if(!clip.empty())//首先判断剪贴板是否有内容
		return false;
		else
		{
		   inser=get_location();//inser是当前光标所在位置 
		   del(inser); 
		   clip.clear();//清空剪贴板 
		} 
		return true;  
	} 
	else if(sign=='x'||sign=='X')
	{
		if(!clip.empty())//首先判断剪贴板是否有内容
		return false;
		else
		{
		   inser=get_location();//inser是当前光标所在位置 
		   del(inser); 
		} 
		return true; 
	}
	else if(sign=='f'||sign=='F') 
	{
		
		if(search(clip))//查找string
		return true;
		else 
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

