#include <stdio.h>
#include <time.h>
#include <string.h>
#include <windows.h>
#include "random.h"
#include "model.h"
#include "advancedFunction.h"


extern HANDLE hMutex;
//���ñ�������������� 


void judge_rest(){
	int c;									//c��Ϊ������������ѭ������ 
	int re[9][2];							
	//re�����¼�԰����������Ϣ�ķ���
	//re[n][0]�������n�Ƿ���������Ϣ״̬ 
	//re[n][1]�������n������Ϣ�Ĵ����� 
	int i;					//i�����жϴ���������Ϣ״̬�İ���ڵ����� 
	int f=1;				//f�����жϾ��밲���������Ϣ���Ƿ��Ѿ���ȥ���룬��ʵ�ְ����ͬʱ������Ϣʱ�����������Ϣ�Ĳ��� 
	int sum;				//sum�����ŵİ���ڵ����� 
	memset(re,0,sizeof(re));			//��ʼ������re 
	
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
	//����ѭ�������i�Լ�sum��ֵ
	 
	double currenttime=(double)(clock()-start_time)/CLOCKS_PER_SEC;
	//currenttime����ִ�иú���ʱ��ʱ��
	 
	for(c=1,f=1;c<=8;c++){
		if((currenttime-cp[c].ask_for_rest_current_time)<2){
			f=0;
			break;
		}
	}
	//���f��ֵ
	 
	if(i==0||f==0);
	//��i=0��f=0�����ݲ����κδ���
	 
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
		//������������С��sum*MaxSeqLen���ҹ����İ������������һ����ͬ����Ϣ 
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
		//���򣬾ܾ���Ϣ 
		output_after_judge_rest(re);
	}
	//i=1ʱ������һ�������������Ϣ�������ж����ȼ����� 
	
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
		//���и��������������Ϣʱ��������Ϣ����Ϣʱ��̵İ���� 
		
		for(c=1;c<=8;c++){
			if(cp[c].state==4&&re[c][1]==0&&cp[c].people==0){ 
				cp[c].state=1;
			}
			else if(cp[c].state==4&&re[c][1]==0&&cp[c].people!=0){
				cp[c].state=2;	
			}
		} 
		//����ܾ���Ϣ���жϽ�� 
		
		output_after_judge_rest(re);
	} 
}
//�ú��������жϵ�ǰʱ�䴦��������Ϣ״̬�İ�����Ƿ������Ϣ 

 
void checkpoint_state_update(){
	int c;							//cΪ������������ѭ����� 
	clock_t start,finish;			//start��¼�ú�����ʼ����ʱ�䣬finish��¼������������ʱ��
	double duration;				//durationΪ�������кķѵ�ʱ��
	//��������ԭ��ͬoutput_periodic����
	
	while(1){
		start=clock();
		WaitForSingleObject(hMutex,INFINITE);
		//�ȴ��������
		buffer_to_checkpoint();					//���˿ʹӻ��������䵽����� 
		for(c=1;c<=8;c++){
			switch(cp[c].state){
				case 1:
				if(cp[c].people!=0){
					cp[c].state=2;
					cp[c].currentPassenger_need_service_time=generate_random_service_time();
				}
				break;
				//����ڴ��ڿ���״̬ʱ��������Ӧ״̬���¼�ת��  
				
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
				//����ڴ��ڹ���״̬ʱ��������Ӧ״̬���¼�ת�� 
				
				case 3:
					cp[c].already_restTime++;
					cp[c].sum_already_restTime++;
					if(cp[c].already_restTime==cp[c].need_rest_time){
						cp[c].state=1;
						cp[c].already_restTime=0;
						cp[c].need_rest_time=0;
					}
					break;
				//����ڴ�����Ϣ״̬ʱ��������Ӧ״̬���¼�ת�� 
				
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
				//����ڴ���������Ϣ״̬ʱ��������Ӧ״̬���¼�ת�� 
				
				case 5:break;
				//����ڴ��ڹر�״̬ʱ������ڲ����κα仯
				 
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
				//����ڴ���׼����Ϣ״̬ʱ��������Ӧ״̬���¼�ת�� 
				
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
					//����ڴ���׼���ر�״̬ʱ��������Ӧ״̬���¼�ת��
					
			}
		}
		judge_rest();							//�жϵ�ǰʱ�䴦��������Ϣ״̬�İ�����Ƿ������Ϣ
		Passenger_flow_monitoring();			//��̬���Źرհ���� 
		ReleaseMutex(hMutex);					//�ͷŻ������ 
		finish=clock();
		duration=(double)(finish-start)/CLOCKS_PER_SEC;
		duration=duration*1000;
		//�õ��������е���ʱ��
		Sleep(1000-duration);
		//�߳����ߣ��Ѵﵽÿһ����°����״̬��Ŀ�� 
	}
}


