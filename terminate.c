#include <stdio.h>
#include "model.h"

int isTerminate(){
	int i=1;
	//i作为程序是否终止的判断条件之一 
	//只有当所有安检口的人数都为0时，i的值为1
	 
	int c;    //c为计数器，用于循环 
	for(c=1;c<=8;c++){
		if(cp[c].people!=0){
			i=0;
			break;
		}
	}
	//遍历循环，求得i的值 
	
	if(isOnDuty==0&&i==1&&bff.people==0)
	return 1;
	//若收到下班命令后，且缓冲区以及安检口中的人数都为0是，程序终止，返回1 
	return 0;
} 
