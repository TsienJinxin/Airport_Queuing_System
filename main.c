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



HANDLE hMutex;      //声明互斥对象 
FILE *fptr;			//声明一个文件指针，用于对将结果输出到文件中进行操作 

int main() 
{
	fptr=fopen("result.txt","w");    
	guide1(); 
	getConfig();    //获得配置文件 
	guide2();
	initialize();
	//初始化安检口，缓冲区等全局变量信息
	
	DWORD ThreadID1,ThreadID2,ThreadID3;  
	HANDLE hThread1,hThread2,hThread3;
	hMutex=CreateMutex(NULL,FALSE,NULL);
	
	hThread1=CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)output_periodic,NULL,0,&ThreadID1);
	hThread2=CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)checkpoint_state_update,NULL,0,&ThreadID2);
	hThread3=CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)getCommand,NULL,0,&ThreadID3);
	// 创建三个线程。其中线程1为周期输出函数，线程2为更新缓冲区及安检口状态函数，线程三为接受命令的函数 
	
	
	while(1){
		if(isTerminate()){
			guide3();
			break;
		}
	}
	//主线程负责判断程序是否终止 
	fclose(fptr);
}
