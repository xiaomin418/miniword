#include<iostream>
#include<stdlib.h>
#include<string.h>
using namespace std;
int main()
{
           char argc[100]; 
          char argc_con[100];
          char argc_compress[100];
         char argc_decompress[100];
         int i;
         for(i=0;i<100;i++)
         {
         	argc[i]=0;
         	argc_con[i]=0;
         	argc_compress[i]=0;
         	argc_decompress[i]=0;
         }
	 cout<<"Please enter the name of the file you want to decompress"<<endl;
	  cin>>argc;
	  strcpy(argc_decompress,argc); 
	  for(i=0;i<100&&argc_decompress[i]!='\0';i++)
	  {
	     if(argc[i]=='.')
	     break;
	  }
	  argc_decompress[i]='1';
	  argc_decompress[i+1]='.';
	  argc_decompress[i+2]='t';
	  argc_decompress[i+3]='x';
	  argc_decompress[i+4]='t';
	  //argc_decompress[i+5]='/0'; 
	  //if(decode(argc,argc_con,argc_decompress))
	  cout<<"Success to decompress the file: "<<argc_decompress<<endl;
	  //else 
	  //cout<<"Fail!"<<endl;
}
