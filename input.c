#include <stdio.h>
#include <string.h>
#include "model.h"
#include "command.h"

extern FILE* fptr;

void getConfig()
{
	char ch;      //×Ö·ûÐÍ±äÁ¿ch´æ´¢ÊäÈëµÄÑ¡ÔñÊäÈëÅäÖÃ·½Ê½µÄÃüÁî
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
		//Ñ¡Ôñ¼üÅÌÊäÈëÊ±¶ÔÅäÖÃÎÄ¼þÊäÈëµÄ´¦Àí

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
			MaxCustSingleLine=temp[0];      //µ¥¶ÓÁÐ×î´óµÈ´ý³Ë¿ÍÊý
			MaxLines=temp[1];              //ÉßÐÎ»º³åÇø×î¶àÓÉMaxLines¸öÖ±¶Ó×é³É
			MaxSeqLen=temp[2];            //×î´óÔÊÐíµÈ´ý³¤¶È
			MinTimeLen=temp[3];           //Ò»´Î°²¼ì×î¶ÌÊ±³¤£¬µ¥Î»ÎªÃë
			MaxTimeLen=temp[4];          //Ò»´Î°²¼ì×î´óÊ±³¤£¬µ¥Î»ÎªÃë
			MinRestTimeLen=temp[5];       //°²¼ì¿ÚÒ»´ÎÔÝÍ£ÐÝÏ¢×î¶ÌÊ±³¤£¬µ¥Î»ÎªÃë
			MaxRestTimeLen=temp[6];      //°²¼ì¿ÚÒ»´ÎÔÝÍ£ÐÝÏ¢×î´óÊ±³¤£¬µ¥Î»ÎªÃë

			break;
		}
		//Ñ¡ÔñÎÄ¼þÊäÈëÊ±¶ÔÅäÖÃÎÄ¼þµÄ´¦Àí

		else{
			printf("Please input 'k' or 'f'\n");
			scanf("%c",&ch);
			getchar();
		}
		//´íÎóÊäÈëÊ±ÖØÐÂÊäÈëÃüÁî£¬ÔÙ×ö´¦Àí
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
	//Êä³öÅäÖÃÎÄ¼þµÄÊäÈë½á¹û
}
//getConfigÓÃÓÚ»ñÈ¡ÅäÖÃÎÄ¼þ


void getCommand()
{
	while(1){
	char order[1000];						//×Ö·ûÐÍÊý×éorder´æ´¢ÊäÈëµÄÃüÁî¼¯ºÏ
	memset(order,0,sizeof(order));			//³õÊ¼»¯Êý×éorder
	gets(order);
	fputs(order,fptr);
	fputs("\n",fptr);
	choose_command(order);			//µ÷ÓÃchoose_commandº¯Êý£¬¶ÔÊäÈëµÄÃüÁî½øÐÐÏàÓ¦µÄ´¦Àí
	}
}
//getCommandÓÃÓÚ»ñÈ¡ÃüÁî²¢½øÐÐ½øÒ»²½µÄÏàÓ¦´¦Àí

