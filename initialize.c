#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "model.h"

void initialize()
{
	int c;   //ÕûÐÍ±äÁ¿cÎª¼ÆÊýÆ÷£¬ÔÚÑ­»·ÖÐÊ¹ÓÃ
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
	//³õÊ¼»¯1-4ºÅ°²¼ì¿ÚµÄÐÅÏ¢£¬Æä×´Ì¬Îª¿ÕÏÐ

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
	//³õÊ¼»¯1-4ºÅ°²¼ì¿ÚµÄÐÅÏ¢£¬Æä×´Ì¬Îª¹Ø±Õ

	bff.people=0;
	bff.isfull=0;
	//³õÊ¼»¯»º³åÇøÐÅÏ¢

	isOnDuty=1;
	//³õÊ¼»¯È«¾Ö±äÁ¿ÊÇ·ñ´¦ÓÚÉÏ°à×´Ì¬Îª1£¬¼´´¦ÓÚÉÏ°à×´Ì¬

	srand((int)time(NULL));
	//³õÊ¼»¯Ëæ»úÊýÖÖ×Ó

	start_time=clock();
	//³õÊ¼»¯³ÌÐò¿ªÊ¼Ê±¼ä


}
