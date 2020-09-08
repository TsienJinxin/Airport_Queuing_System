#include <stdio.h>
#include <string.h>
#include "model.h"
#include "command.h"

extern FILE* fptr;

void getConfig()    
{
	char ch;      //字符型变量ch存储输入的选择输入配置方式的命令 
	printf("Which way would you like to input the config?\nK means input by keyboard and F means input by file\n");
	fputs("Which way would you like to input the config?\nK means input by keyboard and F means input by file\n",fptr);
	scanf("%c",&ch);
	fputc(ch,fptr);
	fputs("\n",fptr);
	getchar();
	while(1){
		if(ch=='k'||ch=='K'){
			printf("Please input the MaxCustSingleLine\n");
			fputs("Please input the MaxCustSingleLine\n",fptr);
			scanf("%d",&MaxCustSingleLine);
			fprintf(fptr,"%d\n",MaxCustSingleLine);
		
			printf("Please input the MaxLines\n");
			fputs("Please input the MaxLines\n",fptr);
			scanf("%d",&MaxLines);
			fprintf(fptr,"%d\n",MaxLines);
			
			printf("Please input the MaxSeqLen\n");
			fputs("Please input the MaxSeqLen\n",fptr);
			scanf("%d",&MaxSeqLen);
		 	fprintf(fptr,"%d\n",MaxSeqLen);
		 				
			printf("Please input the MinTimeLen\n");
			fputs("Please input the MinTimeLen\n",fptr);
			scanf("%d",&MinTimeLen);
			fprintf(fptr,"%d\n",MinTimeLen);
					
			printf("Please input the MaxTimeLen\n");
			fputs("Please input the MaxTimeLen\n",fptr);
			scanf("%d",&MaxTimeLen);
			fprintf(fptr,"%d\n",MaxTimeLen);
						
			printf("Please input the MinRestTimeLen\n");
			fputs("Please input the MinRestTimeLen\n",fptr);
			scanf("%d",&MinRestTimeLen);
			fprintf(fptr,"%d\n",MinRestTimeLen);
					
			printf("Please input the MaxRestTimeLen\n");
			fputs("Please input the MaxRestTimeLen\n",fptr);
			scanf("%d",&MaxRestTimeLen);
			fprintf(fptr,"%d\n",MaxRestTimeLen);
						
			break; 
		}
		//选择键盘输入时对配置文件输入的处理
		 
		else if(ch=='F'||ch=='f') {
			int count;
			int temp[7];
			FILE *fptr;
			char a[100],b[100];
			fptr=fopen("config.txt","r");
			for(count=0;count<7;count++){
				fgets(a,sizeof(a),fptr);
				sscanf(a,"%*[^0-9]%[0-9]",b);
				sscanf(b,"%d",&temp[count]);
			}
			MaxCustSingleLine=temp[0];      //单队列最大等待乘客数
			MaxLines=temp[1];              //蛇形缓冲区最多由MaxLines个直队组成
			MaxSeqLen=temp[2];            //最大允许等待长度
			MinTimeLen=temp[3];           //一次安检最短时长，单位为秒
			MaxTimeLen=temp[4];          //一次安检最大时长，单位为秒
			MinRestTimeLen=temp[5];       //安检口一次暂停休息最短时长，单位为秒
			MaxRestTimeLen=temp[6];      //安检口一次暂停休息最大时长，单位为秒
			
			break; 
		}
		//选择文件输入时对配置文件的处理
		 
		else{
			printf("Please input 'k' or 'f'\n");
			scanf("%c",&ch);
			getchar(); 
		}
		//错误输入时重新输入命令，再做处理 
	}
	
	
	printf("Here are the results.\n");
	printf("MaxCustSingleLine=%d\n",MaxCustSingleLine);
	printf("MaxLines=%d\n",MaxLines);
	printf("MaxSeqLen=%d\n",MaxSeqLen);
	printf("MinTimeLen=%d\n",MinTimeLen);
	printf("MaxTimeLen=%d\n",MaxTimeLen);
	printf("MinRestTimeLen=%d\n",MinRestTimeLen);
	printf("MaxRestTimeLen=%d\n",MaxRestTimeLen);
	
	fputs("Here are the results.\n",fptr);
	fprintf(fptr,"MaxCustSingleLine=%d\n",MaxCustSingleLine);
	fprintf(fptr,"MaxLines=%d\n",MaxLines);
	fprintf(fptr,"MaxSeqLen=%d\n",MaxSeqLen);
	fprintf(fptr,"MinTimeLen=%d\n",MinTimeLen);
	fprintf(fptr,"MaxTimeLen=%d\n",MaxTimeLen);
	fprintf(fptr,"MinRestTimeLen=%d\n",MinRestTimeLen);
	fprintf(fptr,"MaxRestTimeLen=%d\n",MaxRestTimeLen);
	fputs("\n\n",fptr);
	//输出配置文件的输入结果 
}
//getConfig用于获取配置文件
 

void getCommand()
{
	while(1){
	char order[1000];						//字符型数组order存储输入的命令集合 
	memset(order,0,sizeof(order));			//初始化数组order 
	gets(order);
	fputs(order,fptr);
	fputs("\n",fptr);
	choose_command(order);			//调用choose_command函数，对输入的命令进行相应的处理 
	}		
}
//getCommand用于获取命令并进行进一步的相应处理 


