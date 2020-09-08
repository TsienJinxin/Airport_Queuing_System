#include <stdio.h>
#include <string.h>
#include "model.h"

void Passenger_flow_monitoring(){
	int c;						//c为计数器，用于循环操作 
	int sum;					//sum代表开放的安检口总数 
	int i=0;					//i用于判断是否有安检口开放或关闭，从而决定是否输出 
	int re[9];					//re记录处理结果 
	memset(re,0,sizeof(re));	//初始化数组re
	 
	for(c=1;c<=8;c++){
		if(cp[c].state!=5&&cp[c].state!=7)
			sum++;
	}
	//得出sum的值
	 
	for(c=5;c<=8&&bff.people>sum*3;c++){
		if(cp[c].state==5){
			cp[c].state=1;
			re[c]=1;
			sum++;
		}
	}
	//判断是否有安检口需要开放
	 
	for(c=5;c<=8&&bff.people<sum*2;c++){
		if(cp[c].state!=5&&cp[c].state!=7){
			cp[c].state=7;
			re[c]=2;
			sum--;
		}
	}
	//判断是否有安检口需要关闭
	 
	for(c=5;c<=8;c++){
		if(re[c]!=0){
			i=1;
			break;
		}
	}
	//判断是否有安检口开放关闭状态在该周期发生变化
	 
	if(i)
	output_after_close(re);
	//若有变化，则输出 
}
//该函数用于动态开放关闭安检口

 

void buffer_to_checkpoint()
{
	int min=6;				//min初始化为6，代表人数最少的安检口的人数 
	int c;					//c为计数器 
	int i=0;				//i用于判断是否需要将乘客分配到安检口 
	int t=1;				//t代表人数最少的安检口编号
	 
	while(bff.people!=0){
		for(c=1,i=0;c<=8;c++){
			if((cp[c].state==1||cp[c].state==2)&&(cp[c].people<6)){
				i=1;
				break;
			}
		}
		//得到i的值
		 
		if(i==0)
		break;
		//若i为0，则跳出循环，停止分配
		 
		for(c=1;c<=8;c++){
			if(cp[c].state==1||cp[c].state==2){
				if(cp[c].people<min){
					min=cp[c].people;
					t=c;
				}
			}
		}
		min=6;
		bff.people--;
		cp[t].people++;
		//将乘客分配到人数最少的安检口 
	}
}
//该函数用于将乘客从缓冲区分配到安检口
//分配策略为优先将乘客分配到人数少的安检口
 

