#include <stdio.h>
#include <time.h>
#include <string.h>
#include <windows.h>
#include "random.h"
#include "model.h"
#include "advancedFunction.h"


extern HANDLE hMutex;
//引用变量——互斥对象 


void judge_rest(){
	int c;									//c作为计数器，用于循环操作 
	int re[9][2];							
	//re数组记录对安检口申请休息的反馈
	//re[n][0]代表安检口n是否处于申请休息状态 
	//re[n][1]代表安检口n申请休息的处理结果 
	int i;					//i用于判断处于申请休息状态的安检口的数量 
	int f=1;				//f用于判断距离安检口申请休息后是否已经过去两秒，以实现安检口同时申请休息时安检口优先休息的操作 
	int sum;				//sum代表开放的安检口的数量 
	memset(re,0,sizeof(re));			//初始化数组re 
	
	for(c=1,i=0,sum=0;c<=8;c++){
		if(cp[c].state==4){
			re[c][0]=1;
			i++;
			sum++;
		}
		else if(cp[c].state==1||cp[c].state==2){
			sum++;
		}
	} 	
	//遍历循环，求得i以及sum的值
	 
	double currenttime=(double)(clock()-start_time)/CLOCKS_PER_SEC;
	//currenttime代表执行该函数时的时间
	 
	for(c=1,f=1;c<=8;c++){
		if((currenttime-cp[c].ask_for_rest_current_time)<2){
			f=0;
			break;
		}
	}
	//求得f的值
	 
	if(i==0||f==0);
	//若i=0或f=0，则暂不做任何处理
	 
	else if(i==1){
		if((sum-1)&&bff.people<sum*MaxSeqLen){
			for(c=1;c<=8;c++){
				if(cp[c].state==4){
					cp[c].state=6;
					re[c][1]=1;
					break;
				}
			}
		}
		//若缓冲区人数小于sum*MaxSeqLen并且工作的安检口数量大于一，则同意休息 
		else{
			for(c=1;c<=8;c++){
				if(cp[c].state==4&&cp[c].people!=0){
					cp[c].state=2; 
					re[c][1]=0;
					break;
				}
				else if(cp[c].state==4&&cp[c].people==0){
					cp[c].state=1;
					re[c][1]=0;
					break;
				}
			}
		}
		//否则，拒绝休息 
		output_after_judge_rest(re);
	}
	//i=1时，仅有一个安检口申请休息，无需判断优先级问题 
	
	else{
	
		int min_already_restTime=86401;
		int t=0;
		while((sum-1)&&(bff.people<sum*MaxSeqLen)){
			for(c=1;c<=8;c++){
				if(cp[c].state==4&&cp[c].sum_already_restTime<min_already_restTime){
					min_already_restTime=cp[c].sum_already_restTime;
					t=c;
				}
			}
			re[t][1]=1;
			cp[t].state=6;
			sum--;
		}
		//当有复数安检口申请休息时，优先休息已休息时间短的安检口 
		
		for(c=1;c<=8;c++){
			if(cp[c].state==4&&re[c][1]==0&&cp[c].people==0){ 
				cp[c].state=1;
			}
			else if(cp[c].state==4&&re[c][1]==0&&cp[c].people!=0){
				cp[c].state=2;	
			}
		} 
		//处理拒绝休息的判断结果 
		
		output_after_judge_rest(re);
	} 
}
//该函数用于判断当前时间处于申请休息状态的安检口是否可以休息 

 
void checkpoint_state_update(){
	int c;							//c为计数器，用于循环语句 
	clock_t start,finish;			//start记录该函数开始运行时间，finish记录函数结束运行时间
	double duration;				//duration为函数运行耗费的时间
	//上述操作原因同output_periodic函数
	
	while(1){
		start=clock();
		WaitForSingleObject(hMutex,INFINITE);
		//等待互斥对象
		buffer_to_checkpoint();					//将乘客从缓冲区分配到安检口 
		for(c=1;c<=8;c++){
			switch(cp[c].state){
				case 1:
				if(cp[c].people!=0){
					cp[c].state=2;
					cp[c].currentPassenger_need_service_time=generate_random_service_time();
				}
				break;
				//安检口处于空闲状态时，进行相应状态更新及转移  
				
				case 2:
					cp[c].currentPassenger_already_service_time++;
					if(cp[c].currentPassenger_already_service_time==cp[c].currentPassenger_need_service_time){
						cp[c].people--;
						cp[c].currentPassenger_need_service_time=0;
						cp[c].currentPassenger_already_service_time=0;
						if(cp[c].people==0){
							cp[c].state=1;
						}
						else{
							cp[c].currentPassenger_need_service_time=generate_random_service_time();
						}
					}
					break;
				//安检口处于工作状态时，进行相应状态更新及转移 
				
				case 3:
					cp[c].already_restTime++;
					cp[c].sum_already_restTime++;
					if(cp[c].already_restTime==cp[c].need_rest_time){
						cp[c].state=1;
						cp[c].already_restTime=0;
						cp[c].need_rest_time=0;
					}
					break;
				//安检口处于休息状态时，进行相应状态更新及转移 
				
				case 4:
					if(cp[c].people!=0){
						cp[c].currentPassenger_already_service_time++;
						if(cp[c].currentPassenger_already_service_time==cp[c].currentPassenger_need_service_time){
							cp[c].people--;
							cp[c].currentPassenger_need_service_time=0;
							cp[c].currentPassenger_already_service_time=0;
							if(cp[c].people!=0){
								cp[c].currentPassenger_need_service_time=generate_random_service_time();
							}
						}
					}
					break;
				//安检口处于申请休息状态时，进行相应状态更新及转移 
				
				case 5:break;
				//安检口处于关闭状态时，安检口不做任何变化
				 
				case 6:
					if(cp[c].people!=0){
						cp[c].currentPassenger_already_service_time++;
						if(cp[c].currentPassenger_already_service_time==cp[c].currentPassenger_need_service_time){
							cp[c].people--;
							cp[c].currentPassenger_already_service_time=0;
							cp[c].currentPassenger_need_service_time=0;
							if(cp[c].people!=0)
								cp[c].currentPassenger_need_service_time=generate_random_service_time();
							else{
								cp[c].state=3;
								cp[c].need_rest_time=generate_random_rest_time();
							}
						}
					}
					else{
						cp[c].state=3;
						cp[c].need_rest_time=generate_random_rest_time();
					}
					break;
				//安检口处于准备休息状态时，进行相应状态更新及转移 
				
				case 7: 
					if(cp[c].people!=0){
						if(cp[c].currentPassenger_already_service_time==cp[c].currentPassenger_need_service_time&&cp[c].people!=0){
							cp[c].currentPassenger_need_service_time=generate_random_service_time();
						}
						cp[c].currentPassenger_already_service_time++;
						if(cp[c].currentPassenger_already_service_time==cp[c].currentPassenger_need_service_time){
							cp[c].people--;
							cp[c].currentPassenger_already_service_time=0;
							cp[c].currentPassenger_need_service_time=0;
							if(cp[c].people!=0)
								cp[c].currentPassenger_need_service_time=generate_random_service_time();
							else{
								cp[c].state=5;
							}
						}
						
					}
					else{
						cp[c].state=5;
					}
					break;
					//安检口处于准备关闭状态时，进行相应状态更新及转移
					
			}
		}
		judge_rest();							//判断当前时间处于申请休息状态的安检口是否可以休息
		Passenger_flow_monitoring();			//动态开放关闭安检口 
		ReleaseMutex(hMutex);					//释放互斥对象 
		finish=clock();
		duration=(double)(finish-start)/CLOCKS_PER_SEC;
		duration=duration*1000;
		//得到程序运行的总时间
		Sleep(1000-duration);
		//线程休眠，已达到每一秒更新安检口状态的目的 
	}
}


