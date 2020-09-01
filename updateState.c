#include <stdio.h>
#include <time.h>
#include <string.h>
#include <windows.h>
#include "random.h"
#include "model.h"
#include "advancedFunction.h"


extern HANDLE hMutex;
//ÒýÓÃ±äÁ¿¡ª¡ª»¥³â¶ÔÏó


void judge_rest(){
	int c;									//c×÷Îª¼ÆÊýÆ÷£¬ÓÃÓÚÑ­»·²Ù×÷
	int re[9][2];
	//reÊý×é¼ÇÂ¼¶Ô°²¼ì¿ÚÉêÇëÐÝÏ¢µÄ·´À¡
	//re[n][0]´ú±í°²¼ì¿ÚnÊÇ·ñ´¦ÓÚÉêÇëÐÝÏ¢×´Ì¬
	//re[n][1]´ú±í°²¼ì¿ÚnÉêÇëÐÝÏ¢µÄ´¦Àí½á¹û
	int i;					//iÓÃÓÚÅÐ¶Ï´¦ÓÚÉêÇëÐÝÏ¢×´Ì¬µÄ°²¼ì¿ÚµÄÊýÁ¿
	int f=1;				//fÓÃÓÚÅÐ¶Ï¾àÀë°²¼ì¿ÚÉêÇëÐÝÏ¢ºóÊÇ·ñÒÑ¾­¹ýÈ¥Á½Ãë£¬ÒÔÊµÏÖ°²¼ì¿ÚÍ¬Ê±ÉêÇëÐÝÏ¢Ê±°²¼ì¿ÚÓÅÏÈÐÝÏ¢µÄ²Ù×÷
	int sum;				//sum´ú±í¿ª·ÅµÄ°²¼ì¿ÚµÄÊýÁ¿
	memset(re,0,sizeof(re));			//³õÊ¼»¯Êý×ére

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
	//±éÀúÑ­»·£¬ÇóµÃiÒÔ¼°sumµÄÖµ

	double currenttime=(double)(clock()-start_time)/CLOCKS_PER_SEC;
	//currenttime´ú±íÖ´ÐÐ¸Ãº¯ÊýÊ±µÄÊ±¼ä

	for(c=1,f=1;c<=8;c++){
		if((currenttime-cp[c].ask_for_rest_current_time)<2){
			f=0;
			break;
		}
	}
	//ÇóµÃfµÄÖµ

	if(i==0||f==0);
	//Èôi=0»òf=0£¬ÔòÔÝ²»×öÈÎºÎ´¦Àí

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
		//Èô»º³åÇøÈËÊýÐ¡ÓÚsum*MaxSeqLen²¢ÇÒ¹¤×÷µÄ°²¼ì¿ÚÊýÁ¿´óÓÚÒ»£¬ÔòÍ¬ÒâÐÝÏ¢
		else{
			for(c=1;c<=8;c++){
				if(cp[c].state==4){
					cp[c].state=2;
					re[c][1]=0;
					break;
				}
			}
		}
		//·ñÔò£¬¾Ü¾øÐÝÏ¢
		output_after_judge_rest(re);
	}
	//i=1Ê±£¬½öÓÐÒ»¸ö°²¼ì¿ÚÉêÇëÐÝÏ¢£¬ÎÞÐèÅÐ¶ÏÓÅÏÈ¼¶ÎÊÌâ

	else{
		while((sum-1)&&(bff.people<sum*MaxSeqLen)){
			int min_already_restTime=86401;
			int t;
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
		//µ±ÓÐ¸´Êý°²¼ì¿ÚÉêÇëÐÝÏ¢Ê±£¬ÓÅÏÈÐÝÏ¢ÒÑÐÝÏ¢Ê±¼ä¶ÌµÄ°²¼ì¿Ú

		for(c=1;c<=8;c++){
			if(cp[c].state==4&&re[c][1]==0&&cp[c].people==0)
				cp[c].state=1;
			else if(cp[c].state==4&&re[c][1]==0&&cp[c].people==0)
				cp[c].state=2;
		}
		//´¦ÀíÐÝÏ¢ÅÐ¶Ï½á¹û

		output_after_judge_rest(re);
	}
}
//¸Ãº¯ÊýÓÃÓÚÅÐ¶Ïµ±Ç°Ê±¼ä´¦ÓÚÉêÇëÐÝÏ¢×´Ì¬µÄ°²¼ì¿ÚÊÇ·ñ¿ÉÒÔÐÝÏ¢


void checkpoint_state_update(){
	int c;							//cÎª¼ÆÊýÆ÷£¬ÓÃÓÚÑ­»·Óï¾ä
	clock_t start,finish;			//start¼ÇÂ¼¸Ãº¯Êý¿ªÊ¼ÔËÐÐÊ±¼ä£¬finish¼ÇÂ¼º¯Êý½áÊøÔËÐÐÊ±¼ä
	double duration;				//durationÎªº¯ÊýÔËÐÐºÄ·ÑµÄÊ±¼ä
	//ÉÏÊö²Ù×÷Ô­ÒòÍ¬output_periodicº¯Êý

	while(1){
		start=clock();
		WaitForSingleObject(hMutex,INFINITE);
		//µÈ´ý»¥³â¶ÔÏó

		for(c=1;c<=8;c++){
			switch(cp[c].state){
				case 1:
				if(cp[c].people!=0){
					cp[c].state=2;
					cp[c].currentPassenger_need_service_time=generate_random_service_time();
				}
				break;
				//°²¼ì¿Ú´¦ÓÚ¿ÕÏÐ×´Ì¬Ê±£¬½øÐÐÏàÓ¦×´Ì¬¸üÐÂ¼°×ªÒÆ

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
				//°²¼ì¿Ú´¦ÓÚ¹¤×÷×´Ì¬Ê±£¬½øÐÐÏàÓ¦×´Ì¬¸üÐÂ¼°×ªÒÆ

				case 3:
					cp[c].already_restTime++;
					cp[c].sum_already_restTime++;
					if(cp[c].already_restTime==cp[c].need_rest_time){
						cp[c].state=1;
						cp[c].already_restTime=0;
						cp[c].need_rest_time=0;
					}
					break;
				//°²¼ì¿Ú´¦ÓÚÐÝÏ¢×´Ì¬Ê±£¬½øÐÐÏàÓ¦×´Ì¬¸üÐÂ¼°×ªÒÆ

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
				//°²¼ì¿Ú´¦ÓÚÉêÇëÐÝÏ¢×´Ì¬Ê±£¬½øÐÐÏàÓ¦×´Ì¬¸üÐÂ¼°×ªÒÆ

				case 5:break;
				//°²¼ì¿Ú´¦ÓÚ¹Ø±Õ×´Ì¬Ê±£¬°²¼ì¿Ú²»×öÈÎºÎ±ä»¯

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
				//°²¼ì¿Ú´¦ÓÚ×¼±¸ÐÝÏ¢×´Ì¬Ê±£¬½øÐÐÏàÓ¦×´Ì¬¸üÐÂ¼°×ªÒÆ

				case 7:
					if(cp[c].people!=0){
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
					//°²¼ì¿Ú´¦ÓÚ×¼±¸¹Ø±Õ×´Ì¬Ê±£¬½øÐÐÏàÓ¦×´Ì¬¸üÐÂ¼°×ªÒÆ

			}
		}
		buffer_to_checkpoint();					//½«³Ë¿Í´Ó»º³åÇø·ÖÅäµ½°²¼ì¿Ú
		judge_rest();							//ÅÐ¶Ïµ±Ç°Ê±¼ä´¦ÓÚÉêÇëÐÝÏ¢×´Ì¬µÄ°²¼ì¿ÚÊÇ·ñ¿ÉÒÔÐÝÏ¢
		Passenger_flow_monitoring();			//¶¯Ì¬¿ª·Å¹Ø±Õ°²¼ì¿Ú
		ReleaseMutex(hMutex);					//ÊÍ·Å»¥³â¶ÔÏó
		finish=clock();
		duration=(double)(finish-start)/CLOCKS_PER_SEC;
		duration=duration*1000;
		//µÃµ½³ÌÐòÔËÐÐµÄ×ÜÊ±¼ä
		Sleep(1000-duration);
		//Ïß³ÌÐÝÃß£¬ÒÑ´ïµ½Ã¿Ò»Ãë¸üÐÂ°²¼ì¿Ú×´Ì¬µÄÄ¿µÄ
	}
}

