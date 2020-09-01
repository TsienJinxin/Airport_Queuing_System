#include <stdio.h>
#include <windows.h>
#include <time.h>
#include "model.h"

extern HANDLE hMutex;				//µ÷ÓÃÍâ²¿±äÁ¿hMutex£¬×÷Îª»¥³â¶ÔÏó
extern FILE *fptr;

void standard_print(){
	int c=1;						//¼ÆÊýÆ÷£¬ÓÃÓÚÑ­»·½á¹¹ÖÐ
	if(isOnDuty==1){
		printf("OFFDUTY=N\n");
		fputs("OFFDUTY=N\n",fptr);
	}
	else{
		printf("OFFDUTY=Y\n");
		fputs("OFFDUTY=Y\n",fptr);
	}
	//¸ù¾ÝisOnDutyµÄÖµÊä³öµ±Ç°ÉÏÏÂ°à×´Ì¬

	printf("ListLines=%d,ListCustCount=%d\n",bff.people%MaxCustSingleLine==0?bff.people/MaxCustSingleLine:bff.people/MaxCustSingleLine+1,bff.people);
	fprintf(fptr,"ListLines=%d,ListCustCount=%d\n",bff.people%MaxCustSingleLine==0?bff.people/MaxCustSingleLine:bff.people/MaxCustSingleLine+1,bff.people);
	//Êä³ö»º³åÇøµÄ×´Ì¬

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
			//°²¼ì¿Ú×´Ì¬Îª¿ÕÏÐ
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
			//°²¼ì¿Ú×´Ì¬Îª¹¤×÷ÖÐ
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
			//°²¼ì¿Ú×´Ì¬ÎªÐÝÏ¢
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
			//°²¼ì¿Ú×´Ì¬ÎªÉêÇëÐÝÏ¢
			case 5:
				printf("WIN%d:State=Close,",c);
				printf("ServLen=0/0");
				printf("RestLen=0/0,");
				printf("WinListCustCount=0");

				fprintf(fptr,"WIN%d:State=Close,",c);
				fprintf(fptr,"ServLen=0/0");
				fprintf(fptr,"RestLen=0/0,");
				fprintf(fptr,"WinListCustCount=0");
				break;
			//°²¼ì¿Ú×´Ì¬Îª¹Ø±Õ
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
			//°²¼ì¿Ú×´Ì¬Îª×¼±¸ÐÝÏ¢
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
			//°²¼ì¿Ú×´Ì¬Îª×¼±¸¹Ø±Õ
			}
		printf("\n");
		fprintf(fptr,"\n");
	//Êä³ö°²¼ì¿ÚµÄ×´Ì¬
	//¸ù¾Ý°²¼ì¿ÚµÄ×´Ì¬£¬Êä³ö²»Í¬ÄÚÈÝ
	}
	printf("\n");
	fprintf(fptr,"\n");
}
//Êä³öÊÇ·ñÏÂ°à£¬»º³åÇø×´Ì¬£¬°²¼ì¿Ú×´Ì¬
//×÷ÎªÊä³öµÄÒ»²¿·Ö±»ÆäËûº¯ÊýËùµ÷ÓÃ


void output_after_state_change(int order_g[],int order_r[],int order_c[],int order_q)
{
	int c=1;						//cÎª¼ÆÊýÆ÷£¬ÓÃÓÚÑ­»·²Ù×÷
	int i=0;
	//iÓÃÓÚÅÐ¶Ï¸ÃÖÜÆÚÊÇ·ñÓÐÉêÇëÐÝÏ¢Óë»Ö¸´¹¤×÷µÄ°²¼ì¿Ú
	//ÈôiÎª 0£¬ÔòÎÞ£¬²»ÓÃ×öÏàÓ¦Êä³ö£»·ñÔò£¬Êä³öÏàÓ¦µÄ±ä»¯

	printf("T=%.1lf\n",(double)(clock()-start_time)/CLOCKS_PER_SEC);
	fprintf(fptr,"T=%.1lf\n",(double)(clock()-start_time)/CLOCKS_PER_SEC);
	//Êä³öµ±Ç°Ê±¼ä

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
	//Êä³öÓÐ¶àÉÙ³Ë¿Í³É¹¦½øÈë°²¼ì¿Ú
	//¸Ã¶Î´úÂë¶Ôµ¥¶À³Ë¿Í½øÈëºÍ¸´Êý³Ë¿Í½øÈë½øÐÐÁË·Ö±ðµÄ´¦Àí£¨Ó¢ÎÄÓï·¨ÎÊÌâ£©£¬ÏÂÃæÒ²¶¼½øÐÐÁËÏàÍ¬µÄ²Ù×÷

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
	//Êä³öÓÐ¶àÉÙ³Ë¿ÍÃ»ÄÜ³É¹¦½øÈë°²¼ì¿Ú

	if(order_g[2]!=0){
		printf("It's off duty now so passengers can't enter the buffer ");
		fprintf(fptr,"It's off duty now so passengers can't enter the buffer ");
	}
	//Èôµ±Ç°´¦ÓÚÏÂ°à×´Ì¬£¬³Ë¿ÍÎÞ·¨½øÈë°²¼ì¿Ú

	for(c=1;c<=8;c++){
		if(order_r[c]==1){
			i=1;
			break;
		}
	}
	//ÅÐ¶Ïµ±Ç°ÖÜÆÚÊÇ·ñÓÐ°²¼ì¿ÚÉêÇëÐÝÏ¢

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
	//Êä³öÉêÇëÐÝÏ¢µÄ°²¼ì¿ÚµÄÐÅÏ¢

	for(i=0,c=1;c<=8;c++){
		if(order_c[c]==1){
			i=1;
			break;
		}
	}
	//ÅÐ¶Ïµ±Ç°ÖÜÆÚÊÇ·ñÓÐ°²¼ì¿ÚÉêÇë»Ö¸´¹¤×÷

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
	//Êä³öÉêÇë»Ö¸´¹¤×÷µÄ°²¼ì¿ÚµÄÐÅÏ¢

	if(order_q==1){
		printf("It's off duty now");
		fprintf(fptr,"It's off duty now");
	}
	//Èôµ±Ç°ÖÜÆÚÊÕµ½ÏÂ°àÃüÁî£¬ÔòÊä³öÏàÓ¦ÐÅÏ¢

	printf("\n\n");
	fprintf(fptr,"\n\n");
}


void output_periodic()
{
	clock_t start,finish;
	//start¼ÇÂ¼¸Ãº¯Êý¿ªÊ¼ÔËÐÐÊ±¼ä£¬finish¼ÇÂ¼º¯Êý½áÊøÔËÐÐÊ±¼ä
	double duration;
	//durationÎªº¯ÊýÔËÐÐºÄ·ÑµÄÊ±¼ä

	//Òª×ö³öÉÏÊö´¦ÀíµÄÔ­Òò£º¸Ãº¯ÊýÒª±£Ö¤Ã¿ÈýÃëÔËÐÐÒ»´Î£¬Èô²»ÔÚÏß³ÌÐÝÃßÊ±¼äÖÐ¼õÈ¥Ïß³ÌÔËÐÐÊ±¼ä£¬µ±³ÌÐòÔËÐÐÒ»¶ÎÊ±¼äºó»á²úÉúÎó²î

	// ÕâÖÖ´¦Àí·½·¨ÈÔ»á´æÔÚÒ»¶¨Îó²î£¬²»¹ýºÜÐ¡£¬¿ÉºöÂÔ

	while(1){
		WaitForSingleObject(hMutex,INFINITE);			//µÈ´ý»¥³â¶ÔÏó
		start=clock();

		printf("T=%.lf\n",(double)(start-start_time)/CLOCKS_PER_SEC);
		fprintf(fptr,"T=%.lf\n",(double)(start-start_time)/CLOCKS_PER_SEC);
		//Êä³öµ±Ç°Ê±¼ä

		standard_print();					//Êä³ö»º³åÇøºÍ°²¼ì¿ÚµÄ×´Ì¬
		ReleaseMutex(hMutex);				//ÊÍ·Å»¥³â¶ÔÏó
		finish=clock();
		duration=(double)(finish-start)/CLOCKS_PER_SEC;
		duration=duration*1000;
		Sleep(3000-duration);				//Ïß³ÌÐÝÏ¢£¬ÒÑ´ïµ½ÖÜÆÚÐÔÊä³öµÄÄ¿µÄ
	}
}
//ÓÃÓÚ°´Ò»¶¨ÖÜÆÚÊä³ö°²¼ì´óÌüµÄ×´Ì¬
//ÓÉÓÚ½öÓÃÓÚÖÜÆÚÊä³ö  £¬¹Ê²¢²»ÐèÒªÊä³ö×´Ì¬±ä»¯ÐÅÏ¢


void output_after_judge_rest(int re[][2]){
	int c=1;					//cÎª¼ÆÊýÆ÷£¬ÓÃÓÚÑ­»·²Ù×÷
	printf("T=%.1lf\n",(double)(clock()-start_time)/CLOCKS_PER_SEC);
	fprintf(fptr,"T=%.1lf\n",(double)(clock()-start_time)/CLOCKS_PER_SEC);
	//Êä³öÊ±¼ä

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
	//Êä³ö°²¼ì¿ÚÍ¬ÒâÐÝÏ¢»ò¾Ü¾øÐÝÏ¢µÄÐÅÏ¢

	printf("\n\n");
	fprintf(fptr,"\n\n");
}

void  output_after_close(int re[]){
	printf("T=%.1lf\n",(double)(clock()-start_time)/CLOCKS_PER_SEC);
	fprintf(fptr,"T=%.1lf\n",(double)(clock()-start_time)/CLOCKS_PER_SEC);
	//Êä³öÊ±¼ä
	int c;						//cÎª¼ÆÊýÆ÷£¬ÓÃÓÚÑ­»·Óï¾ä
	int i=0;					//iÓÃÓÚÅÐ¶ÏÊÇ·ñÓÐ°²¼ì¿Ú½øÐÐÁË¹Ø±Õ»ò¿ª·Å²Ù×÷£»i=1ÔòÓÐ°²¼ì¿Ú½øÐÐÏà¹Ø²Ù×÷£¬i=0ÔòÃ»ÓÐ
	for(c=5;c<=8;c++){
		if(re[c]==1){
			i=1;
			break;
		}
	}
	//ÅÐ¶ÏÊÇ·ñÓÐ°²¼ì¿Ú¿ª·Å£¬´Ó¶øÅÐ¶ÏÊÇ·ñÊä³ö

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
	//Êä³ö°²¼ì¿Ú¿ª·ÅÐÅÏ¢

	for(c=5,i=0;c<=8;c++){
		if(re[c]==2){
			i=1;
			break;
		}
	}
	//ÅÐ¶ÏÊÇ·ñÓÐ°²¼ì¿Ú¹Ø±Õ£¬´Ó¶øÅÐ¶ÏÊÇ·ñÊä³ö

	if(i==1){
		printf("Check point ");
		fprintf(fptr,"Check point ");
		for(c=5;c<=8;c++){
			if(re[c]==1){
				printf("%d ",c);
				fprintf(fptr,"%d ",c);
			}
		}
		printf("prepare to close ");
		fprintf(fptr,"prepare to close ");
	}
	//Êä³ö°²¼ì¿Ú¹Ø±ÕÐÅÏ¢

	printf("\n\n");
	fprintf(fptr,"\n\n");
}
