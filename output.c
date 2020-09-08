#include <stdio.h>
#include <windows.h>
#include <time.h>
#include "model.h"

extern HANDLE hMutex;				//�����ⲿ����hMutex����Ϊ������� 
extern FILE *fptr;

void standard_print(){
	int c=1;						//������������ѭ���ṹ�� 
	if(isOnDuty==1){
		printf("OFFDUTY=N\n");
		fputs("OFFDUTY=N\n",fptr);
	}	
	else{ 
		printf("OFFDUTY=Y\n");
		fputs("OFFDUTY=Y\n",fptr);
	}
	//����isOnDuty��ֵ�����ǰ���°�״̬
	 
	printf("ListLines=%d,ListCustCount=%d\n",bff.people%MaxCustSingleLine==0?bff.people/MaxCustSingleLine:bff.people/MaxCustSingleLine+1,bff.people);
	fprintf(fptr,"ListLines=%d,ListCustCount=%d\n",bff.people%MaxCustSingleLine==0?bff.people/MaxCustSingleLine:bff.people/MaxCustSingleLine+1,bff.people);
	//�����������״̬
	 
	for(c=1;c<=8;c++){
		switch(cp[c].state){
			case 1:
				printf("WIN%d:State=Idle,",c);
				printf("ServLen=0/0,");
				printf("RestLen=0/0,");
				printf("WinListCustCount=%d",cp[c].people);
				
				fprintf(fptr,"WIN%d:State=Idle,",c);
				fprintf(fptr,"ServLen=0/0,");
				fprintf(fptr,"RestLen=0/0,");
				fprintf(fptr,"WinListCustCount=%d",cp[c].people);
				break;
			//�����״̬Ϊ���� 
			case 2:
				printf("WIN%d:State=OnService,",c);
				printf("ServLen=%d/%d,",cp[c].currentPassenger_already_service_time,cp[c].currentPassenger_need_service_time);
				printf("RestLen=0/0,");
				printf("WinListCustCount=%d",cp[c].people);
				
				fprintf(fptr,"WIN%d:State=OnService,",c);
				fprintf(fptr,"ServLen=%d/%d,",cp[c].currentPassenger_already_service_time,cp[c].currentPassenger_need_service_time);
				fprintf(fptr,"RestLen=0/0,");
				fprintf(fptr,"WinListCustCount=%d",cp[c].people);
				break;
			//�����״̬Ϊ������ 
			case 3:
				printf("WIN%d:State=Rest,",c);
				printf("ServLen=0/0,");
				printf("RestLen=%d/%d,",cp[c].already_restTime,cp[c].need_rest_time);
				printf("WinListCustCount=0",cp[c].people);
				
				fprintf(fptr,"WIN%d:State=Rest,",c);
				fprintf(fptr,"ServLen=0/0,");
				fprintf(fptr,"RestLen=%d/%d,",cp[c].already_restTime,cp[c].need_rest_time);
				fprintf(fptr,"WinListCustCount=0",cp[c].people);
				break;
			//�����״̬Ϊ��Ϣ 
			case 4:
				printf("WIN%d:State=AskForRest,",c);
				printf("ServLen=%d/%d,",cp[c].currentPassenger_already_service_time,cp[c].currentPassenger_need_service_time);
				printf("RestLen=0/0,");
				printf("WinListCustCount=%d",cp[c].people);
				
				fprintf(fptr,"WIN%d:State=AskForRest,",c);
				fprintf(fptr,"ServLen=%d/%d,",cp[c].currentPassenger_already_service_time,cp[c].currentPassenger_need_service_time);
				fprintf(fptr,"RestLen=0/0,");
				fprintf(fptr,"WinListCustCount=%d",cp[c].people);
				break;
			//�����״̬Ϊ������Ϣ 
			case 5:
				printf("WIN%d:State=Close,",c);
				printf("ServLen=0/0,");
				printf("RestLen=0/0,");
				printf("WinListCustCount=0");
				
				fprintf(fptr,"WIN%d:State=Close,",c);
				fprintf(fptr,"ServLen=0/0,");
				fprintf(fptr,"RestLen=0/0,");
				fprintf(fptr,"WinListCustCount=0");
				break;
			//�����״̬Ϊ�ر� 
			case 6:
				printf("WIN%d:State=Prepare to rest,",c);
				printf("ServLen=%d/%d,",cp[c].currentPassenger_already_service_time,cp[c].currentPassenger_need_service_time);
				printf("RestLen=0/0,");
				printf("WinListCustCount=%d",cp[c].people);
				
				fprintf(fptr,"WIN%d:State=Prepare to rest,",c);
				fprintf(fptr,"ServLen=%d/%d,",cp[c].currentPassenger_already_service_time,cp[c].currentPassenger_need_service_time);
				fprintf(fptr,"RestLen=0/0,");
				fprintf(fptr,"WinListCustCount=%d",cp[c].people);
				break;
			//�����״̬Ϊ׼����Ϣ 
			case 7:
				printf("WIN%d:State=Prepare to close,",c);
				printf("ServLen=%d/%d,",cp[c].currentPassenger_already_service_time,cp[c].currentPassenger_need_service_time);
				printf("RestLen=0/0,");
				printf("WinListCustCount=%d",cp[c].people);
				
				fprintf(fptr,"WIN%d:State=Prepare to close,",c);
				fprintf(fptr,"ServLen=%d/%d,",cp[c].currentPassenger_already_service_time,cp[c].currentPassenger_need_service_time);
				fprintf(fptr,"RestLen=0/0,");
				fprintf(fptr,"WinListCustCount=%d",cp[c].people);
				break;
			//�����״̬Ϊ׼���ر� 
			}
		printf("\n");
		fprintf(fptr,"\n");
	//�������ڵ�״̬
	//���ݰ���ڵ�״̬�������ͬ����	
	}
	printf("\n");
	fprintf(fptr,"\n");
}
//����Ƿ��°࣬������״̬�������״̬
//��Ϊ�����һ���ֱ���������������

 
void output_after_state_change(int order_g[],int order_r[],int order_c[],int order_q)
{
	int c=1;						//cΪ������������ѭ������ 
	int i=0;						
	//i�����жϸ������Ƿ���������Ϣ��ָ������İ����
	//��iΪ 0�����ޣ���������Ӧ��������������Ӧ�ı仯 
	
	printf("T=%.1lf\n",(double)(clock()-start_time)/CLOCKS_PER_SEC);
	fprintf(fptr,"T=%.1lf\n",(double)(clock()-start_time)/CLOCKS_PER_SEC);
	//�����ǰʱ�� 
	
	if(order_g[1]!=0){
		if(order_g[1]==1){
			printf("A passenger enters the buffer ");
			fprintf(fptr,"A passenger enters the buffer ");
		}
		else{
			printf("%d passengers enter the buffer ",order_g[1]);
			fprintf(fptr,"%d passengers enter the buffer ",order_g[1]);
		}
	}
	//����ж��ٳ˿ͳɹ����밲���
	//�öδ���Ե����˿ͽ���͸����˿ͽ�������˷ֱ�Ĵ���Ӣ���﷨���⣩������Ҳ����������ͬ�Ĳ��� 
	 
	if(order_g[0]!=0){
		if(order_g[0]==1){
			printf("A passenger is refused access to the buffer ");
			fprintf(fptr,"A passenger is refused access to the buffer ");
		}
		else{
			printf("%d passengers are refused access to the buffer ",order_g[0]);
			fprintf(fptr,"%d passengers are refused access to the buffer ",order_g[0]);
		}
	}
	//����ж��ٳ˿�û�ܳɹ����밲���
	
	if(order_g[2]!=0){
		printf("It's off duty now so passengers can't enter the buffer ");
		fprintf(fptr,"It's off duty now so passengers can't enter the buffer ");
	}
	//����ǰ�����°�״̬���˿��޷����밲��� 
	
	for(c=1;c<=8;c++){
		if(order_r[c]==1){
			i=1;
			break;
		}
	}
	//�жϵ�ǰ�����Ƿ��а����������Ϣ 
	
	if(i==1){
		printf("Check point");
		fprintf(fptr,"Check point");
		for(c=1;c<=8;c++){
			if(order_r[c]==1){
				printf("%d ",c);
				fprintf(fptr,"%d ",c);
			}
		}
		printf("request for rest ");
		fprintf(fptr,"request for rest ");
	}
	//���������Ϣ�İ���ڵ���Ϣ
	 
	for(i=0,c=1;c<=8;c++){
		if(order_c[c]==1){
			i=1;
			break;
		}
	}
	//�жϵ�ǰ�����Ƿ��а��������ָ�����
	
	if(i==1){
		printf("Check point");
		fprintf(fptr,"Check point");
		for(c=1;c<=8;c++){
			if(order_c[c]==1){
				printf("%d ",c);
				fprintf(fptr,"%d ",c);
			}
		}
		printf("request reinstatement of security ");
		fprintf(fptr,"request reinstatement of security ");
	}
	//�������ָ������İ���ڵ���Ϣ
	
	if(order_q==1){
		printf("It's off duty now");
		fprintf(fptr,"It's off duty now");
	}
	//����ǰ�����յ��°�����������Ӧ��Ϣ
	 
	printf("\n\n");
	fprintf(fptr,"\n\n");
}


void output_periodic()
{
	clock_t start,finish;				
	//start��¼�ú�����ʼ����ʱ�䣬finish��¼������������ʱ�� 
	double duration;
	//durationΪ�������кķѵ�ʱ��
	
	//Ҫ�������������ԭ�򣺸ú���Ҫ��֤ÿ��������һ�Σ��������߳�����ʱ���м�ȥ�߳�����ʱ�䣬����������һ��ʱ����������
	
	// ���ִ������Ի����һ����������С���ɺ���
	 
	while(1){
		WaitForSingleObject(hMutex,INFINITE);			//�ȴ�������� 
		start=clock();
		
		printf("T=%.lf\n",(double)(start-start_time)/CLOCKS_PER_SEC);
		fprintf(fptr,"T=%.lf\n",(double)(start-start_time)/CLOCKS_PER_SEC);
		//�����ǰʱ��
		 
		standard_print();					//����������Ͱ���ڵ�״̬ 
		ReleaseMutex(hMutex);				//�ͷŻ������ 
		finish=clock();
		duration=(double)(finish-start)/CLOCKS_PER_SEC;
		duration=duration*1000;
		Sleep(3000-duration);				//�߳���Ϣ���Ѵﵽ�����������Ŀ�� 
	}
}
//���ڰ�һ������������������״̬
//���ڽ������������  ���ʲ�����Ҫ���״̬�仯��Ϣ


void output_after_judge_rest(int re[][2]){
	int c=1;					//cΪ������������ѭ������ 
	printf("T=%.1lf\n",(double)(clock()-start_time)/CLOCKS_PER_SEC);
	fprintf(fptr,"T=%.1lf\n",(double)(clock()-start_time)/CLOCKS_PER_SEC);
	//���ʱ��
	 
	for(c=1;c<=8;c++){
		if(re[c][0]==1&&re[c][1]==0){
			printf("Checkpoint %d was refused to rest ",c);
			fprintf(fptr,"Checkpoint %d was refused to rest ",c);
		}
		else if(re[c][0]==1&&re[c][1]==1){
			printf("Checkpoint %d was agreed to rest ",c);
			fprintf(fptr,"Checkpoint %d was agreed to rest ",c);
		}
	}
	//��������ͬ����Ϣ��ܾ���Ϣ����Ϣ 
	 
	printf("\n\n");
	fprintf(fptr,"\n\n");
}

void  output_after_close(int re[]){
	printf("T=%.1lf\n",(double)(clock()-start_time)/CLOCKS_PER_SEC);
	fprintf(fptr,"T=%.1lf\n",(double)(clock()-start_time)/CLOCKS_PER_SEC);
	//���ʱ�� 
	int c;						//cΪ������������ѭ����� 
	int i=0;					//i�����ж��Ƿ��а���ڽ����˹رջ򿪷Ų�����i=1���а���ڽ�����ز�����i=0��û�� 
	for(c=5;c<=8;c++){
		if(re[c]==1){
			i=1;
			break;
		}
	}
	//�ж��Ƿ��а���ڿ��ţ��Ӷ��ж��Ƿ����
	 
	if(i==1){
		printf("Check point ");
		fprintf(fptr,"Check point ");
		for(c=5;c<=8;c++){
			if(re[c]==1){
				printf("%d ",c);
				fprintf(fptr,"%d ",c);
			}
		}
		printf("opend ");
		fprintf(fptr,"opend ");
	}
	//�������ڿ�����Ϣ
	
	for(c=5,i=0;c<=8;c++){
		if(re[c]==2){
			i=1;
			break;
		}
	}
	//�ж��Ƿ��а���ڹرգ��Ӷ��ж��Ƿ����
	 
	if(i==1){
		printf("Check point ");
		fprintf(fptr,"Check point ");
		for(c=5;c<=8;c++){
			if(re[c]==2){
				printf("%d ",c);
				fprintf(fptr,"%d ",c);
			}
		}
		printf("prepare to close ");
		fprintf(fptr,"prepare to close ");
	}
	//�������ڹر���Ϣ
	
	printf("\n\n");
	fprintf(fptr,"\n\n");
}

