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
		//����������������� MaxCustSingleLine*MaxLines���򻺳�������
		 
		else{
			bff.isfull=0;
		}
		if(bff.isfull==0){
			bff.people=bff.people+1;
			return 1;
		}
		//�����ǰ������δ������˿ͳɹ����� 
		
		else 
		return 0;
		//�����ǰ��������������˿ͽ���ʧ�� 
		

	}
	//��ǰΪ�°�ʱ���� �˿ͽ��뻺����������Ĵ���
	 
	else
	return 2;
	//�����ǰ�����°�״̬����˿ͽ���ʧ�� 
} 
//��G����˿ͽ��뻺������������д��� 


void command_R(int window){
	if(cp[window].state==1||cp[window].state==2){
		cp[window].state=4;				//���������Ϣ״̬�Ĵ��ڽ���������Ϣ״̬ 
		
    	cp[window].ask_for_rest_current_time=(double)(clock()-start_time)/CLOCKS_PER_SEC;//��¼������Ϣ��ʱ��
	}
    else{
    	printf("Check point %d can't rest.\n",window);
    	fprintf(fptr,"Check point %d can't rest.\n",window);
	}
	//�޷�������Ϣ״̬�Ĵ��ڷ���������Ϣ����ʱ������������ʾ 
}
//�Ի�����������Ϣ����Ĵ���
 

void command_C (int window)  //���ջ�õ�������д��ڻָ�������Ҫ��
{
	if(cp[window].state==3){
    	cp[window].state=1;       				//�ָ�����״̬
    	cp[window].already_restTime=0; 				
    	cp[window].need_rest_time=0;			//״̬�ָ� 
	}
	//��������Ѿ�������Ϣ״̬ 
	else if(cp[window].state==6){
		cp[window].state=2;       				//�ָ�����״̬
    	cp[window].already_restTime=0; 				
    	cp[window].need_rest_time=0;
	} 
	//�����������׼����Ϣ 
    else{
    	printf("Check point %d isn't resting now.\n",window);
    	fprintf(fptr,"Check point %d isn't resting now.\n",window);
	}
	//����Ϣ״̬��������ָ���Ϣʱ���������ʾ 
}
//�Ի���������ָ���������Ĵ���

void command_Q ()           //���ջ�õ�������о����°��Ҫ��
{
	if(isOnDuty)
    	isOnDuty=0;				 //�����°�״̬  
    else{
    	printf("It's already off duty now.\n");
    	fprintf(fptr,"It's already off duty now.\n");
	} 
	//���ѷ������°�ָ�����������ʾ 
}
//���°�����Ĵ��� 

void choose_command(char order[]){
	int c;			//������������ѭ���� 
	int re;			
	//Ϊ��ֹ�ظ����ú��� command_G(),ʹ�����α���re 
	//re��ֵΪcommand_G()�ķ���ֵ������re��ֵ�Ĳ�ͬ��������Ӧ��ͬ�����״̬�仯
	 
	int order_g[3]={0,0,0};
	//order_g[3]�������˿ͽ��밲��ڵĽ��
	//order_g[0]�����򻺳�������������ʧ�ܵ�������order_g[1]�������ɹ���������order[2]���������°�״̬������ʧ�ܵ����� 
	
	int order_r[9];
	//order_r[9]�����������Ƿ���������Ϣ
	//order_r[n]=0�������nδ������Ϣ��order_r[n]=1�������n������Ϣ
	
	int order_c[9];
	//order_c[9]�����������Ƿ�������ָ�����
	//order_c[n]=0�������nδ����ָ�������order_c[n]=1�������n����ָ����� 
	
	int order_q=0;
	//order_q=0����δ�����°����order_q=1���������°�����
	
	int mistake=0;
	//mistake���ڼ�¼������������Ƿ��д�����Ϣ�����У���mistake��ֵΪ1 
	memset(order_c,0,sizeof(order_r));
	memset(order_r,0,sizeof(order_c));
	//��ʼ��order_c��order_r����
	 
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
	//������������Ĳ�ͬ������Ӧ�Ĳ������Ҽ�¼��Ӧ�Ĳ������ 
	
	output_after_state_change(order_g,order_r,order_c,order_q);
	//��״̬�ı仯������Ӧ����� 
	if(mistake){
		printf("Something in your order isn't right,and we only handle the right part.\n");
		fprintf(fptr,"Something in your order isn't right,and we only handle the right part.\n");
	} 
}

