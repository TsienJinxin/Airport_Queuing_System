#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "model.h"

void initialize()
{
	int c;   //���ͱ���cΪ����������ѭ����ʹ�� 
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
	//��ʼ��1-4�Ű���ڵ���Ϣ����״̬Ϊ���� 
	
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
	//��ʼ��1-4�Ű���ڵ���Ϣ����״̬Ϊ�ر�
	
	bff.people=0;
	bff.isfull=0;
	//��ʼ����������Ϣ 
	
	isOnDuty=1;
	//��ʼ��ȫ�ֱ����Ƿ����ϰ�״̬Ϊ1���������ϰ�״̬
	
	srand((int)time(NULL));
	//��ʼ�����������
	 
	start_time=clock();
	//��ʼ������ʼʱ�� 
	
	
} 
