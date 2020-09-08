#include <stdio.h>
#include <time.h>
#include "output.h"
#include "model.h"

extern FILE* fptr;

void guide1(){
	printf("Thank you for using our airport security queuing system.\n");
	printf("Here is something you should before using it.\n\n");
	printf("First,you should choose a way to input the config first, by the keyboard or files.\n\n");
	printf("Second,while the program is running,you can input some commands to conntrol it.\n");
	printf("G means a passenger applies to enter the buffer.\n");
	printf("RX(X is an integer between 1 and 8) means check point X applies to rest.\n");
	printf("CX(X is an integer between 1 and 8) means check point X applies to resume work.\n");
	printf("And Q means it's off duty now,and no one can enter the buffer.\n");
	printf("You can input many orders at the same time,which you only need input the commands in a line and the press enter.\n");
	printf("Just like 'GGGGGGR1GGGGC3Q' and then press enter.Our program will handle it then.\n\n");
	printf("Last,you should know that after you input 'Q',the program will terminate when there's no one in both the buffer and checkpoints.\n\n");
	printf("Now,please press enter and input the config.\n\n\n");
	
	fputs("Thank you for using our airport security queuing system.\n",fptr);
	fputs("Here is something you should before using it.\n\n",fptr);
	fputs("First,you should choose a way to input the config first, by the keyboard or files.\n\n",fptr);
	fputs("Second,while the program is running,you can input some commands to conntrol it.\n",fptr);
	fputs("G means a passenger applies to enter the buffer.\n",fptr);
	fputs("RX(X is an integer between 1 and 8) means check point X applies to rest.\n",fptr);
	fputs("CX(X is an integer between 1 and 8) means check point X applies to resume work.\n",fptr);
	fputs("And Q means it's off duty now,and no one can enter the buffer.\n",fptr);
	fputs("You can input many orders at the same time,which you only need input the commands in a line and the press enter.\n",fptr);
	fputs("Just like 'GGGGGGR1GGGGC3Q' and then press enter.Our program will handle it then.\n\n",fptr);
	fputs("Last,you should know that after you input 'Q',the program will terminate when there's no one in both the buffer and checkpoints.\n\n",fptr);
	fputs("Now,please press enter and input the config.\n\n\n",fptr);
	getchar();
}
//引导界面1，用于说明使用须知 


void guide2(){
	printf("Now,press enter to start our program.\n\n\n");
	fputs("Now,press enter to start our program.\n\n\n",fptr);
	getchar();
}
//引导界面2，引导用户启动程序 

void guide3(){
	printf("T=%.lf\n",(double)(clock()-start_time)/CLOCKS_PER_SEC);
	fprintf(fptr,"T=%.lf\n",(double)(clock()-start_time)/CLOCKS_PER_SEC);
	standard_print();
	fprintf(fptr,"\n\nIt's the end.");
}
//引导界面3，程序终止时运行，提示程序已经结束 
