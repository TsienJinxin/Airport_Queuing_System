#include <stdio.h>
#include <string.h>
#include "model.h"

void Passenger_flow_monitoring(){
	int c;						//cΪ������������ѭ������ 
	int sum;					//sum�����ŵİ�������� 
	int i=0;					//i�����ж��Ƿ��а���ڿ��Ż�رգ��Ӷ������Ƿ���� 
	int re[9];					//re��¼������ 
	memset(re,0,sizeof(re));	//��ʼ������re
	 
	for(c=1;c<=8;c++){
		if(cp[c].state!=5&&cp[c].state!=7)
			sum++;
	}
	//�ó�sum��ֵ
	 
	for(c=5;c<=8&&bff.people>sum*3;c++){
		if(cp[c].state==5){
			cp[c].state=1;
			re[c]=1;
			sum++;
		}
	}
	//�ж��Ƿ��а������Ҫ����
	 
	for(c=5;c<=8&&bff.people<sum*2;c++){
		if(cp[c].state!=5&&cp[c].state!=7){
			cp[c].state=7;
			re[c]=2;
			sum--;
		}
	}
	//�ж��Ƿ��а������Ҫ�ر�
	 
	for(c=5;c<=8;c++){
		if(re[c]!=0){
			i=1;
			break;
		}
	}
	//�ж��Ƿ��а���ڿ��Źر�״̬�ڸ����ڷ����仯
	 
	if(i)
	output_after_close(re);
	//���б仯������� 
}
//�ú������ڶ�̬���Źرհ����

 

void buffer_to_checkpoint()
{
	int min=6;				//min��ʼ��Ϊ6�������������ٵİ���ڵ����� 
	int c;					//cΪ������ 
	int i=0;				//i�����ж��Ƿ���Ҫ���˿ͷ��䵽����� 
	int t=1;				//t�����������ٵİ���ڱ��
	 
	while(bff.people!=0){
		for(c=1,i=0;c<=8;c++){
			if((cp[c].state==1||cp[c].state==2)&&(cp[c].people<6)){
				i=1;
				break;
			}
		}
		//�õ�i��ֵ
		 
		if(i==0)
		break;
		//��iΪ0��������ѭ����ֹͣ����
		 
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
		//���˿ͷ��䵽�������ٵİ���� 
	}
}
//�ú������ڽ��˿ʹӻ��������䵽�����
//�������Ϊ���Ƚ��˿ͷ��䵽�����ٵİ����
 

