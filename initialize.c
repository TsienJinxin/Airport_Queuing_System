#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "model.h"

void initialize()
{
	int c;   //整型变量c为计数器，在循环中使用 
	for(c=1;c<=4;c++){
		cp[c].people=0;
		cp[c].state=1;
		cp[c].currentPassenger_need_service_time=0;
		cp[c].currentPassenger_already_service_time=0;
		cp[c].need_rest_time=0;
		cp[c].already_restTime=0;
		cp[c].sum_already_restTime=0;
		cp[c].ask_for_rest_current_time=0;
	}
	//初始化1-4号安检口的信息，其状态为空闲 
	
	for(;c<=8;c++){
		cp[c].people=0;
		cp[c].state=5;
		cp[c].currentPassenger_need_service_time=0;
		cp[c].currentPassenger_already_service_time=0;
		cp[c].need_rest_time=0;
		cp[c].already_restTime=0;
		cp[c].sum_already_restTime=0;
		cp[c].ask_for_rest_current_time=0;
	}
	//初始化1-4号安检口的信息，其状态为关闭
	
	bff.people=0;
	bff.isfull=0;
	//初始化缓冲区信息 
	
	isOnDuty=1;
	//初始化全局变量是否处于上班状态为1，即处于上班状态
	
	srand((int)time(NULL));
	//初始化随机数种子
	 
	start_time=clock();
	//初始化程序开始时间 
	
	
} 
