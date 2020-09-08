#include <stdio.h>
#include <string.h>
#include <time.h>
#include "model.h"


extern FILE* fptr;

int command_G()
{
	if(isOnDuty==1){		
		if(bff.people == MaxCustSingleLine*MaxLines){
			bff.isfull=1;
		}
		//如果缓冲区人数等于 MaxCustSingleLine*MaxLines，则缓冲区已满
		 
		else{
			bff.isfull=0;
		}
		if(bff.isfull==0){
			bff.people=bff.people+1;
			return 1;
		}
		//如果当前缓冲区未满，则乘客成功进入 
		
		else 
		return 0;
		//如果当前缓冲区已满，则乘客进入失败 
		

	}
	//当前为下班时，对 乘客进入缓冲区的命令的处理
	 
	else
	return 2;
	//如果当前处于下班状态，则乘客进入失败 
} 
//对G命令即乘客进入缓冲区的命令进行处理 


void command_R(int window){
	if(cp[window].state==1||cp[window].state==2){
		cp[window].state=4;				//申请进入休息状态的窗口进入申请休息状态 
		
    	cp[window].ask_for_rest_current_time=(double)(clock()-start_time)/CLOCKS_PER_SEC;//记录申请休息的时间
	}
    else{
    	printf("Check point %d can't rest.\n",window);
    	fprintf(fptr,"Check point %d can't rest.\n",window);
	}
	//无法进入休息状态的窗口发出申请休息命令时，会给予错误提示 
}
//对缓冲区申请休息命令的处理
 

void command_C (int window)  //按照获得的命令进行窗口恢复工作的要求
{
	if(cp[window].state==3){
    	cp[window].state=1;       				//恢复工作状态
    	cp[window].already_restTime=0; 				
    	cp[window].need_rest_time=0;			//状态恢复 
	}
	//若安检口已经处于休息状态 
	else if(cp[window].state==6){
		cp[window].state=2;       				//恢复工作状态
    	cp[window].already_restTime=0; 				
    	cp[window].need_rest_time=0;
	} 
	//若安检口正在准备休息 
    else{
    	printf("Check point %d isn't resting now.\n",window);
    	fprintf(fptr,"Check point %d isn't resting now.\n",window);
	}
	//非休息状态窗口申请恢复休息时给予错误提示 
}
//对缓冲区申请恢复工作命令的处理

void command_Q ()           //按照获得的命令进行决定下班的要求
{
	if(isOnDuty)
    	isOnDuty=0;				 //进入下班状态  
    else{
    	printf("It's already off duty now.\n");
    	fprintf(fptr,"It's already off duty now.\n");
	} 
	//若已发出了下班指令，则给予错误提示 
}
//对下班命令的处理 

void choose_command(char order[]){
	int c;			//计数器，用于循环中 
	int re;			
	//为防止重复引用函数 command_G(),使用整形变量re 
	//re的值为command_G()的返回值，根据re的值的不同，做出相应不同的输出状态变化
	 
	int order_g[3]={0,0,0};
	//order_g[3]数组代表乘客进入安检口的结果
	//order_g[0]代表因缓冲区人满而进入失败的人数，order_g[1]代表进入成功的人数，order[2]代表因处于下班状态而进入失败的人数 
	
	int order_r[9];
	//order_r[9]数组代表安检口是否有申请休息
	//order_r[n]=0代表安检口n未申请休息，order_r[n]=1代表安检口n申请休息
	
	int order_c[9];
	//order_c[9]数组代表安检口是否有申请恢复工作
	//order_c[n]=0代表安检口n未申请恢复工作，order_c[n]=1代表安检口n申请恢复工作 
	
	int order_q=0;
	//order_q=0代表未发出下班命令。order_q=1代表发出了下班命令
	
	int mistake=0;
	//mistake用于记录输入的命令中是否有错误信息，若有，则mistake的值为1 
	memset(order_c,0,sizeof(order_r));
	memset(order_r,0,sizeof(order_c));
	//初始化order_c及order_r数组
	 
	for(c=0;order[c]!='\0';c++){
		switch(order[c]){
			case 'G':
				re=command_G();
				if(re==0)
				order_g[0]++;
				else if(re==1)
				order_g[1]++;
				else if(re==2)
				order_g[2]++;
				break;
			case 'R':
				c++;
				command_R(order[c]-48);
				order_r[order[c]-48]=1;
				break;
			case 'C':
				c++;
				command_C(order[c]-48);
				order_c[order[c]-48]=1;
				break;
			case 'Q':
				order_q=1;
				command_Q();
				break;
			default :
				mistake=1;
				break; 
		}
	}
	//根据输入命令的不同做出相应的操作并且记录相应的操作结果 
	
	output_after_state_change(order_g,order_r,order_c,order_q);
	//对状态的变化进行相应的输出 
	if(mistake){
		printf("Something in your order isn't right,and we only handle the right part.\n");
		fprintf(fptr,"Something in your order isn't right,and we only handle the right part.\n");
	} 
}

