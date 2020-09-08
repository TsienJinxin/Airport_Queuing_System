#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <windows.h>
#include "model.h"
#include "guide.h"
#include "input.h" 
#include "output.h"
#include "random.h"
#include "initialize.h"
#include "terminate.h"
#include "updateState.h"



HANDLE hMutex;      //����������� 
FILE *fptr;			//����һ���ļ�ָ�룬���ڶԽ����������ļ��н��в��� 

int main() 
{
	fptr=fopen("result.txt","w");    
	guide1(); 
	getConfig();    //��������ļ� 
	guide2();
	initialize();
	//��ʼ������ڣ���������ȫ�ֱ�����Ϣ
	
	DWORD ThreadID1,ThreadID2,ThreadID3;  
	HANDLE hThread1,hThread2,hThread3;
	hMutex=CreateMutex(NULL,FALSE,NULL);
	
	hThread1=CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)output_periodic,NULL,0,&ThreadID1);
	hThread2=CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)checkpoint_state_update,NULL,0,&ThreadID2);
	hThread3=CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)getCommand,NULL,0,&ThreadID3);
	// ���������̡߳������߳�1Ϊ��������������߳�2Ϊ���»������������״̬�������߳���Ϊ��������ĺ��� 
	
	
	while(1){
		if(isTerminate()){
			guide3();
			break;
		}
	}
	//���̸߳����жϳ����Ƿ���ֹ 
	fclose(fptr);
}
