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



HANDLE hMutex;      //ÉùÃ÷»¥³â¶ÔÏó
FILE *fptr;			//ÉùÃ÷Ò»¸öÎÄ¼þÖ¸Õë£¬ÓÃÓÚ¶Ô½«½á¹ûÊä³öµ½ÎÄ¼þÖÐ½øÐÐ²Ù×÷

int main()
{
	fptr=fopen("result.txt","w");
	guide1();
	getConfig();    //»ñµÃÅäÖÃÎÄ¼þ
	guide2();
	initialize();
	//³õÊ¼»¯°²¼ì¿Ú£¬»º³åÇøµÈÈ«¾Ö±äÁ¿ÐÅÏ¢

	DWORD ThreadID1,ThreadID2,ThreadID3;
	HANDLE hThread1,hThread2,hThread3;
	hMutex=CreateMutex(NULL,FALSE,NULL);

	hThread1=CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)output_periodic,NULL,0,&ThreadID1);
	hThread2=CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)checkpoint_state_update,NULL,0,&ThreadID2);
	hThread3=CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)getCommand,NULL,0,&ThreadID3);
	// ´´½¨Èý¸öÏß³Ì¡£ÆäÖÐÏß³Ì1ÎªÖÜÆÚÊä³öº¯Êý£¬Ïß³Ì2Îª¸üÐÂ»º³åÇø¼°°²¼ì¿Ú×´Ì¬º¯Êý£¬Ïß³ÌÈýÎª½ÓÊÜÃüÁîµÄº¯Êý


	while(1){
		if(isTerminate()){
			guide3();
			break;
		}
	}
	//Ö÷Ïß³Ì¸ºÔðÅÐ¶Ï³ÌÐòÊÇ·ñÖÕÖ¹
	fclose(fptr);
}
