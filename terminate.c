#include <stdio.h>
#include "model.h"

int isTerminate(){
	int i=1;
	//i��Ϊ�����Ƿ���ֹ���ж�����֮һ 
	//ֻ�е����а���ڵ�������Ϊ0ʱ��i��ֵΪ1
	 
	int c;    //cΪ������������ѭ�� 
	for(c=1;c<=8;c++){
		if(cp[c].people!=0){
			i=0;
			break;
		}
	}
	//����ѭ�������i��ֵ 
	
	if(isOnDuty==0&&i==1&&bff.people==0)
	return 1;
	//���յ��°�������һ������Լ�������е�������Ϊ0�ǣ�������ֹ������1 
	return 0;
} 
