#include <stdio.h>
#include <string.h>
#include "model.h"
#include "output.h"
void Passenger_flow_monitoring(){
	int c;						//cÎª¼ÆÊýÆ÷£¬ÓÃÓÚÑ­»·²Ù×÷
	int sum;					//sum´ú±í¿ª·ÅµÄ°²¼ì¿Ú×ÜÊý
	int i=0;					//iÓÃÓÚÅÐ¶ÏÊÇ·ñÓÐ°²¼ì¿Ú¿ª·Å»ò¹Ø±Õ£¬´Ó¶ø¾ö¶¨ÊÇ·ñÊä³ö
	int re[9];					//re¼ÇÂ¼´¦Àí½á¹û
	memset(re,0,sizeof(re));	//³õÊ¼»¯Êý×ére

	for(c=1;c<=8;c++){
		if(cp[c].state!=5&&cp[c].state!=7)
			sum++;
	}
	//µÃ³ösumµÄÖµ

	for(c=5;c<=8&&bff.people>sum*3;c++){
		if(cp[c].state==5){
			cp[c].state=1;
			re[c]=1;
			sum++;
		}
	}
	//ÅÐ¶ÏÊÇ·ñÓÐ°²¼ì¿ÚÐèÒª¿ª·Å

	for(c=5;c<=8&&bff.people<sum*2;c++){
		if(cp[c].state!=5&&cp[c].state!=7){
			cp[c].state=7;
			re[c]=2;
			sum--;
		}
	}
	//ÅÐ¶ÏÊÇ·ñÓÐ°²¼ì¿ÚÐèÒª¹Ø±Õ

	for(c=5;c<=8;c++){
		if(re[c]!=0){
			i=1;
			break;
		}
	}
	//ÅÐ¶ÏÊÇ·ñÓÐ°²¼ì¿Ú¿ª·Å¹Ø±Õ×´Ì¬ÔÚ¸ÃÖÜÆÚ·¢Éú±ä»¯

	if(i)
        output_after_close(re);
	//ÈôÓÐ±ä»¯£¬ÔòÊä³ö
}
//¸Ãº¯ÊýÓÃÓÚ¶¯Ì¬¿ª·Å¹Ø±Õ°²¼ì¿Ú



void buffer_to_checkpoint()
{
	int min=6;				//min³õÊ¼»¯Îª6£¬´ú±íÈËÊý×îÉÙµÄ°²¼ì¿ÚµÄÈËÊý
	int c;					//cÎª¼ÆÊýÆ÷
	int i=0;				//iÓÃÓÚÅÐ¶ÏÊÇ·ñÐèÒª½«³Ë¿Í·ÖÅäµ½°²¼ì¿Ú
	int t=1;				//t´ú±íÈËÊý×îÉÙµÄ°²¼ì¿Ú±àºÅ

	while(bff.people!=0){
		for(c=1,i=0;c<=8;c++){
			if((cp[c].state==1||cp[c].state==2)&&(cp[c].people<6)){
				i=1;
				break;
			}
		}
		//µÃµ½iµÄÖµ

		if(i==0)
		break;
		//ÈôiÎª0£¬ÔòÌø³öÑ­»·£¬Í£Ö¹·ÖÅä

		for(c=1;c<=8;c++){
			if(cp[c].state==1||cp[c].state==2){
				if(cp[c].people<min){
					min=cp[c].people;
					t=c;
				}
			}
		}
		min=6;
		bff.people--;
		cp[t].people++;
		//½«³Ë¿Í·ÖÅäµ½ÈËÊý×îÉÙµÄ°²¼ì¿Ú
	}
}
//¸Ãº¯ÊýÓÃÓÚ½«³Ë¿Í´Ó»º³åÇø·ÖÅäµ½°²¼ì¿Ú
//·ÖÅä²ßÂÔÎªÓÅÏÈ½«³Ë¿Í·ÖÅäµ½ÈËÊýÉÙµÄ°²¼ì¿Ú

