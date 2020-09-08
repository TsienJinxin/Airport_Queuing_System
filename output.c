#include <stdio.h>
#include <windows.h>
#include <time.h>
#include "model.h"

extern HANDLE hMutex;				//调用外部变量hMutex，作为互斥对象 
extern FILE *fptr;

void standard_print(){
	int c=1;						//计数器，用于循环结构中 
	if(isOnDuty==1){
		printf("OFFDUTY=N\n");
		fputs("OFFDUTY=N\n",fptr);
	}	
	else{ 
		printf("OFFDUTY=Y\n");
		fputs("OFFDUTY=Y\n",fptr);
	}
	//根据isOnDuty的值输出当前上下班状态
	 
	printf("ListLines=%d,ListCustCount=%d\n",bff.people%MaxCustSingleLine==0?bff.people/MaxCustSingleLine:bff.people/MaxCustSingleLine+1,bff.people);
	fprintf(fptr,"ListLines=%d,ListCustCount=%d\n",bff.people%MaxCustSingleLine==0?bff.people/MaxCustSingleLine:bff.people/MaxCustSingleLine+1,bff.people);
	//输出缓冲区的状态
	 
	for(c=1;c<=8;c++){
		switch(cp[c].state){
			case 1:
				printf("WIN%d:State=Idle,",c);
				printf("ServLen=0/0,");
				printf("RestLen=0/0,");
				printf("WinListCustCount=%d",cp[c].people);
				
				fprintf(fptr,"WIN%d:State=Idle,",c);
				fprintf(fptr,"ServLen=0/0,");
				fprintf(fptr,"RestLen=0/0,");
				fprintf(fptr,"WinListCustCount=%d",cp[c].people);
				break;
			//安检口状态为空闲 
			case 2:
				printf("WIN%d:State=OnService,",c);
				printf("ServLen=%d/%d,",cp[c].currentPassenger_already_service_time,cp[c].currentPassenger_need_service_time);
				printf("RestLen=0/0,");
				printf("WinListCustCount=%d",cp[c].people);
				
				fprintf(fptr,"WIN%d:State=OnService,",c);
				fprintf(fptr,"ServLen=%d/%d,",cp[c].currentPassenger_already_service_time,cp[c].currentPassenger_need_service_time);
				fprintf(fptr,"RestLen=0/0,");
				fprintf(fptr,"WinListCustCount=%d",cp[c].people);
				break;
			//安检口状态为工作中 
			case 3:
				printf("WIN%d:State=Rest,",c);
				printf("ServLen=0/0,");
				printf("RestLen=%d/%d,",cp[c].already_restTime,cp[c].need_rest_time);
				printf("WinListCustCount=0",cp[c].people);
				
				fprintf(fptr,"WIN%d:State=Rest,",c);
				fprintf(fptr,"ServLen=0/0,");
				fprintf(fptr,"RestLen=%d/%d,",cp[c].already_restTime,cp[c].need_rest_time);
				fprintf(fptr,"WinListCustCount=0",cp[c].people);
				break;
			//安检口状态为休息 
			case 4:
				printf("WIN%d:State=AskForRest,",c);
				printf("ServLen=%d/%d,",cp[c].currentPassenger_already_service_time,cp[c].currentPassenger_need_service_time);
				printf("RestLen=0/0,");
				printf("WinListCustCount=%d",cp[c].people);
				
				fprintf(fptr,"WIN%d:State=AskForRest,",c);
				fprintf(fptr,"ServLen=%d/%d,",cp[c].currentPassenger_already_service_time,cp[c].currentPassenger_need_service_time);
				fprintf(fptr,"RestLen=0/0,");
				fprintf(fptr,"WinListCustCount=%d",cp[c].people);
				break;
			//安检口状态为申请休息 
			case 5:
				printf("WIN%d:State=Close,",c);
				printf("ServLen=0/0,");
				printf("RestLen=0/0,");
				printf("WinListCustCount=0");
				
				fprintf(fptr,"WIN%d:State=Close,",c);
				fprintf(fptr,"ServLen=0/0,");
				fprintf(fptr,"RestLen=0/0,");
				fprintf(fptr,"WinListCustCount=0");
				break;
			//安检口状态为关闭 
			case 6:
				printf("WIN%d:State=Prepare to rest,",c);
				printf("ServLen=%d/%d,",cp[c].currentPassenger_already_service_time,cp[c].currentPassenger_need_service_time);
				printf("RestLen=0/0,");
				printf("WinListCustCount=%d",cp[c].people);
				
				fprintf(fptr,"WIN%d:State=Prepare to rest,",c);
				fprintf(fptr,"ServLen=%d/%d,",cp[c].currentPassenger_already_service_time,cp[c].currentPassenger_need_service_time);
				fprintf(fptr,"RestLen=0/0,");
				fprintf(fptr,"WinListCustCount=%d",cp[c].people);
				break;
			//安检口状态为准备休息 
			case 7:
				printf("WIN%d:State=Prepare to close,",c);
				printf("ServLen=%d/%d,",cp[c].currentPassenger_already_service_time,cp[c].currentPassenger_need_service_time);
				printf("RestLen=0/0,");
				printf("WinListCustCount=%d",cp[c].people);
				
				fprintf(fptr,"WIN%d:State=Prepare to close,",c);
				fprintf(fptr,"ServLen=%d/%d,",cp[c].currentPassenger_already_service_time,cp[c].currentPassenger_need_service_time);
				fprintf(fptr,"RestLen=0/0,");
				fprintf(fptr,"WinListCustCount=%d",cp[c].people);
				break;
			//安检口状态为准备关闭 
			}
		printf("\n");
		fprintf(fptr,"\n");
	//输出安检口的状态
	//根据安检口的状态，输出不同内容	
	}
	printf("\n");
	fprintf(fptr,"\n");
}
//输出是否下班，缓冲区状态，安检口状态
//作为输出的一部分被其他函数所调用

 
void output_after_state_change(int order_g[],int order_r[],int order_c[],int order_q)
{
	int c=1;						//c为计数器，用于循环操作 
	int i=0;						
	//i用于判断该周期是否有申请休息与恢复工作的安检口
	//若i为 0，则无，不用做相应输出；否则，输出相应的变化 
	
	printf("T=%.1lf\n",(double)(clock()-start_time)/CLOCKS_PER_SEC);
	fprintf(fptr,"T=%.1lf\n",(double)(clock()-start_time)/CLOCKS_PER_SEC);
	//输出当前时间 
	
	if(order_g[1]!=0){
		if(order_g[1]==1){
			printf("A passenger enters the buffer ");
			fprintf(fptr,"A passenger enters the buffer ");
		}
		else{
			printf("%d passengers enter the buffer ",order_g[1]);
			fprintf(fptr,"%d passengers enter the buffer ",order_g[1]);
		}
	}
	//输出有多少乘客成功进入安检口
	//该段代码对单独乘客进入和复数乘客进入进行了分别的处理（英文语法问题），下面也都进行了相同的操作 
	 
	if(order_g[0]!=0){
		if(order_g[0]==1){
			printf("A passenger is refused access to the buffer ");
			fprintf(fptr,"A passenger is refused access to the buffer ");
		}
		else{
			printf("%d passengers are refused access to the buffer ",order_g[0]);
			fprintf(fptr,"%d passengers are refused access to the buffer ",order_g[0]);
		}
	}
	//输出有多少乘客没能成功进入安检口
	
	if(order_g[2]!=0){
		printf("It's off duty now so passengers can't enter the buffer ");
		fprintf(fptr,"It's off duty now so passengers can't enter the buffer ");
	}
	//若当前处于下班状态，乘客无法进入安检口 
	
	for(c=1;c<=8;c++){
		if(order_r[c]==1){
			i=1;
			break;
		}
	}
	//判断当前周期是否有安检口申请休息 
	
	if(i==1){
		printf("Check point");
		fprintf(fptr,"Check point");
		for(c=1;c<=8;c++){
			if(order_r[c]==1){
				printf("%d ",c);
				fprintf(fptr,"%d ",c);
			}
		}
		printf("request for rest ");
		fprintf(fptr,"request for rest ");
	}
	//输出申请休息的安检口的信息
	 
	for(i=0,c=1;c<=8;c++){
		if(order_c[c]==1){
			i=1;
			break;
		}
	}
	//判断当前周期是否有安检口申请恢复工作
	
	if(i==1){
		printf("Check point");
		fprintf(fptr,"Check point");
		for(c=1;c<=8;c++){
			if(order_c[c]==1){
				printf("%d ",c);
				fprintf(fptr,"%d ",c);
			}
		}
		printf("request reinstatement of security ");
		fprintf(fptr,"request reinstatement of security ");
	}
	//输出申请恢复工作的安检口的信息
	
	if(order_q==1){
		printf("It's off duty now");
		fprintf(fptr,"It's off duty now");
	}
	//若当前周期收到下班命令，则输出相应信息
	 
	printf("\n\n");
	fprintf(fptr,"\n\n");
}


void output_periodic()
{
	clock_t start,finish;				
	//start记录该函数开始运行时间，finish记录函数结束运行时间 
	double duration;
	//duration为函数运行耗费的时间
	
	//要做出上述处理的原因：该函数要保证每三秒运行一次，若不在线程休眠时间中减去线程运行时间，当程序运行一段时间后会产生误差
	
	// 这种处理方法仍会存在一定误差，不过很小，可忽略
	 
	while(1){
		WaitForSingleObject(hMutex,INFINITE);			//等待互斥对象 
		start=clock();
		
		printf("T=%.lf\n",(double)(start-start_time)/CLOCKS_PER_SEC);
		fprintf(fptr,"T=%.lf\n",(double)(start-start_time)/CLOCKS_PER_SEC);
		//输出当前时间
		 
		standard_print();					//输出缓冲区和安检口的状态 
		ReleaseMutex(hMutex);				//释放互斥对象 
		finish=clock();
		duration=(double)(finish-start)/CLOCKS_PER_SEC;
		duration=duration*1000;
		Sleep(3000-duration);				//线程休息，已达到周期性输出的目的 
	}
}
//用于按一定周期输出安检大厅的状态
//由于仅用于周期输出  ，故并不需要输出状态变化信息


void output_after_judge_rest(int re[][2]){
	int c=1;					//c为计数器，用于循环操作 
	printf("T=%.1lf\n",(double)(clock()-start_time)/CLOCKS_PER_SEC);
	fprintf(fptr,"T=%.1lf\n",(double)(clock()-start_time)/CLOCKS_PER_SEC);
	//输出时间
	 
	for(c=1;c<=8;c++){
		if(re[c][0]==1&&re[c][1]==0){
			printf("Checkpoint %d was refused to rest ",c);
			fprintf(fptr,"Checkpoint %d was refused to rest ",c);
		}
		else if(re[c][0]==1&&re[c][1]==1){
			printf("Checkpoint %d was agreed to rest ",c);
			fprintf(fptr,"Checkpoint %d was agreed to rest ",c);
		}
	}
	//输出安检口同意休息或拒绝休息的信息 
	 
	printf("\n\n");
	fprintf(fptr,"\n\n");
}

void  output_after_close(int re[]){
	printf("T=%.1lf\n",(double)(clock()-start_time)/CLOCKS_PER_SEC);
	fprintf(fptr,"T=%.1lf\n",(double)(clock()-start_time)/CLOCKS_PER_SEC);
	//输出时间 
	int c;						//c为计数器，用于循环语句 
	int i=0;					//i用于判断是否有安检口进行了关闭或开放操作；i=1则有安检口进行相关操作，i=0则没有 
	for(c=5;c<=8;c++){
		if(re[c]==1){
			i=1;
			break;
		}
	}
	//判断是否有安检口开放，从而判断是否输出
	 
	if(i==1){
		printf("Check point ");
		fprintf(fptr,"Check point ");
		for(c=5;c<=8;c++){
			if(re[c]==1){
				printf("%d ",c);
				fprintf(fptr,"%d ",c);
			}
		}
		printf("opend ");
		fprintf(fptr,"opend ");
	}
	//输出安检口开放信息
	
	for(c=5,i=0;c<=8;c++){
		if(re[c]==2){
			i=1;
			break;
		}
	}
	//判断是否有安检口关闭，从而判断是否输出
	 
	if(i==1){
		printf("Check point ");
		fprintf(fptr,"Check point ");
		for(c=5;c<=8;c++){
			if(re[c]==2){
				printf("%d ",c);
				fprintf(fptr,"%d ",c);
			}
		}
		printf("prepare to close ");
		fprintf(fptr,"prepare to close ");
	}
	//输出安检口关闭信息
	
	printf("\n\n");
	fprintf(fptr,"\n\n");
}

