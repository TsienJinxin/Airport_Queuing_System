#include <stdio.h>
#include <string.h>
#include <time.h>
#include "model.h"
#include "output.h"


extern FILE* fptr;

int command_G()
{
	if(isOnDuty==1){
		if(bff.people == MaxCustSingleLine*MaxLines){
			bff.isfull=1;
		}
		//Èç¹û»º³åÇøÈËÊýµÈÓÚ MaxCustSingleLine*MaxLines£¬Ôò»º³åÇøÒÑÂú

		else{
			bff.isfull=0;
		}
		if(bff.isfull==0){
			bff.people=bff.people+1;
			return 1;
		}
		//Èç¹ûµ±Ç°»º³åÇøÎ´Âú£¬Ôò³Ë¿Í³É¹¦½øÈë

		else
		return 0;
		//Èç¹ûµ±Ç°»º³åÇøÒÑÂú£¬Ôò³Ë¿Í½øÈëÊ§°Ü


	}
	//µ±Ç°ÎªÏÂ°àÊ±£¬¶Ô ³Ë¿Í½øÈë»º³åÇøµÄÃüÁîµÄ´¦Àí

	else
	return 2;
	//Èç¹ûµ±Ç°´¦ÓÚÏÂ°à×´Ì¬£¬Ôò³Ë¿Í½øÈëÊ§°Ü
}
//¶ÔGÃüÁî¼´³Ë¿Í½øÈë»º³åÇøµÄÃüÁî½øÐÐ´¦Àí


void command_R(int window){
	if(cp[window].state==1||cp[window].state==2){
		cp[window].state=4;				//ÉêÇë½øÈëÐÝÏ¢×´Ì¬µÄ´°¿Ú½øÈëÉêÇëÐÝÏ¢×´Ì¬

    	cp[window].ask_for_rest_current_time=(double)(clock()-start_time)/CLOCKS_PER_SEC;//¼ÇÂ¼ÉêÇëÐÝÏ¢µÄÊ±¼ä
	}
    else{
    	printf("Check point %d can't rest.\n",window);
    	fprintf(fptr,"Check point %d can't rest.\n",window);
	}
	//ÎÞ·¨½øÈëÐÝÏ¢×´Ì¬µÄ´°¿Ú·¢³öÉêÇëÐÝÏ¢ÃüÁîÊ±£¬»á¸øÓè´íÎóÌáÊ¾
}
//¶Ô»º³åÇøÉêÇëÐÝÏ¢ÃüÁîµÄ´¦Àí


void command_C (int window)  //°´ÕÕ»ñµÃµÄÃüÁî½øÐÐ´°¿Ú»Ö¸´¹¤×÷µÄÒªÇó
{
	if(cp[window].state==3){
    	cp[window].state=1;       				//»Ö¸´¹¤×÷×´Ì¬
    	cp[window].already_restTime=0;
    	cp[window].need_rest_time=0;			//×´Ì¬»Ö¸´
	}
	//Èô°²¼ì¿ÚÒÑ¾­´¦ÓÚÐÝÏ¢×´Ì¬
	else if(cp[window].state==6){
		cp[window].state=2;       				//»Ö¸´¹¤×÷×´Ì¬
    	cp[window].already_restTime=0;
    	cp[window].need_rest_time=0;
	}
	//Èô°²¼ì¿ÚÕýÔÚ×¼±¸ÐÝÏ¢
    else{
    	printf("Check point %d isn't resting now.\n",window);
    	fprintf(fptr,"Check point %d isn't resting now.\n",window);
	}
	//·ÇÐÝÏ¢×´Ì¬´°¿ÚÉêÇë»Ö¸´ÐÝÏ¢Ê±¸øÓè´íÎóÌáÊ¾
}
//¶Ô»º³åÇøÉêÇë»Ö¸´¹¤×÷ÃüÁîµÄ´¦Àí

void command_Q ()           //°´ÕÕ»ñµÃµÄÃüÁî½øÐÐ¾ö¶¨ÏÂ°àµÄÒªÇó
{
	if(isOnDuty)
    	isOnDuty=0;				 //½øÈëÏÂ°à×´Ì¬
    else{
    	printf("It's already off duty now.\n");
    	fprintf(fptr,"It's already off duty now.\n");
	}
	//ÈôÒÑ·¢³öÁËÏÂ°àÖ¸Áî£¬Ôò¸øÓè´íÎóÌáÊ¾
}
//¶ÔÏÂ°àÃüÁîµÄ´¦Àí

void choose_command(char order[]){
	int c;			//¼ÆÊýÆ÷£¬ÓÃÓÚÑ­»·ÖÐ
	int re;
	//Îª·ÀÖ¹ÖØ¸´ÒýÓÃº¯Êý command_G(),Ê¹ÓÃÕûÐÎ±äÁ¿re
	//reµÄÖµÎªcommand_G()µÄ·µ»ØÖµ£¬¸ù¾ÝreµÄÖµµÄ²»Í¬£¬×ö³öÏàÓ¦²»Í¬µÄÊä³ö×´Ì¬±ä»¯

	int order_g[3]={0,0,0};
	//order_g[3]Êý×é´ú±í³Ë¿Í½øÈë°²¼ì¿ÚµÄ½á¹û
	//order_g[0]´ú±íÒò»º³åÇøÈËÂú¶ø½øÈëÊ§°ÜµÄÈËÊý£¬order_g[1]´ú±í½øÈë³É¹¦µÄÈËÊý£¬order[2]´ú±íÒò´¦ÓÚÏÂ°à×´Ì¬¶ø½øÈëÊ§°ÜµÄÈËÊý

	int order_r[9];
	//order_r[9]Êý×é´ú±í°²¼ì¿ÚÊÇ·ñÓÐÉêÇëÐÝÏ¢
	//order_r[n]=0´ú±í°²¼ì¿ÚnÎ´ÉêÇëÐÝÏ¢£¬order_r[n]=1´ú±í°²¼ì¿ÚnÉêÇëÐÝÏ¢

	int order_c[9];
	//order_c[9]Êý×é´ú±í°²¼ì¿ÚÊÇ·ñÓÐÉêÇë»Ö¸´¹¤×÷
	//order_c[n]=0´ú±í°²¼ì¿ÚnÎ´ÉêÇë»Ö¸´¹¤×÷£¬order_c[n]=1´ú±í°²¼ì¿ÚnÉêÇë»Ö¸´¹¤×÷

	int order_q=0;
	//order_q=0´ú±íÎ´·¢³öÏÂ°àÃüÁî¡£order_q=1´ú±í·¢³öÁËÏÂ°àÃüÁî

	int mistake=0;
	//mistakeÓÃÓÚ¼ÇÂ¼ÊäÈëµÄÃüÁîÖÐÊÇ·ñÓÐ´íÎóÐÅÏ¢£¬ÈôÓÐ£¬ÔòmistakeµÄÖµÎª1
	memset(order_c,0,sizeof(order_r));
	memset(order_r,0,sizeof(order_c));
	//³õÊ¼»¯order_c¼°order_rÊý×é

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
	//¸ù¾ÝÊäÈëÃüÁîµÄ²»Í¬×ö³öÏàÓ¦µÄ²Ù×÷²¢ÇÒ¼ÇÂ¼ÏàÓ¦µÄ²Ù×÷½á¹û

	output_after_state_change(order_g,order_r,order_c,order_q);
	//¶Ô×´Ì¬µÄ±ä»¯½øÐÐÏàÓ¦µÄÊä³ö
	if(mistake){
		printf("Something in your order isn't right,and we only handle the right part.\n");
		fprintf(fptr,"Something in your order isn't right,and we only handle the right part.\n");
	}
}
