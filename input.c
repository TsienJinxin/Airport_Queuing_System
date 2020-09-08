#include <stdio.h>
#include <string.h>
#include "model.h"
#include "command.h"

extern FILE* fptr;

void getConfig()    
{
	char ch;      //�ַ��ͱ���ch�洢�����ѡ���������÷�ʽ������ 
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
		//ѡ���������ʱ�������ļ�����Ĵ���
		 
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
			MaxCustSingleLine=temp[0];      //���������ȴ��˿���
			MaxLines=temp[1];              //���λ����������MaxLines��ֱ�����
			MaxSeqLen=temp[2];            //�������ȴ�����
			MinTimeLen=temp[3];           //һ�ΰ������ʱ������λΪ��
			MaxTimeLen=temp[4];          //һ�ΰ������ʱ������λΪ��
			MinRestTimeLen=temp[5];       //�����һ����ͣ��Ϣ���ʱ������λΪ��
			MaxRestTimeLen=temp[6];      //�����һ����ͣ��Ϣ���ʱ������λΪ��
			
			break; 
		}
		//ѡ���ļ�����ʱ�������ļ��Ĵ���
		 
		else{
			printf("Please input 'k' or 'f'\n");
			scanf("%c",&ch);
			getchar(); 
		}
		//��������ʱ������������������� 
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
	//��������ļ��������� 
}
//getConfig���ڻ�ȡ�����ļ�
 

void getCommand()
{
	while(1){
	char order[1000];						//�ַ�������order�洢���������� 
	memset(order,0,sizeof(order));			//��ʼ������order 
	gets(order);
	fputs(order,fptr);
	fputs("\n",fptr);
	choose_command(order);			//����choose_command����������������������Ӧ�Ĵ��� 
	}		
}
//getCommand���ڻ�ȡ������н�һ������Ӧ���� 


