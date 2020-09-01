#ifndef MODEL_H_INCLUDED
#define MODEL_H_INCLUDED

#include<stdio.h>
#include<time.h>

int MaxCustSingleLine;      //µ¥¶ÓÁÐ×î´óµÈ´ý³Ë¿ÍÊý
int MaxLines;              //ÉßÐÎ»º³åÇø×î¶àÓÉMaxLines¸öÖ±¶Ó×é³É
int MaxSeqLen;            //×î´óÔÊÐíµÈ´ý³¤¶È
int MinTimeLen;           //Ò»´Î°²¼ì×î¶ÌÊ±³¤£¬µ¥Î»ÎªÃë
int MaxTimeLen;          //Ò»´Î°²¼ì×î´óÊ±³¤£¬µ¥Î»ÎªÃë
int MinRestTimeLen;       //°²¼ì¿ÚÒ»´ÎÔÝÍ£ÐÝÏ¢×î¶ÌÊ±³¤£¬µ¥Î»ÎªÃë
int MaxRestTimeLen;      //°²¼ì¿ÚÒ»´ÎÔÝÍ£ÐÝÏ¢×î´óÊ±³¤£¬µ¥Î»ÎªÃë

typedef struct list1{
    int people;                                //°²¼ì¿ÚÅÅ¶ÓµÄÈËÊý
    int state;								   //°²¼ì¿Ú×´Ì¬£¬1Îª¿ÕÏÐ£¬2Îª·þÎñ£¬3ÎªÐÝÏ¢£¬4ÎªÉêÇëÐÝÏ¢£¬5Îª¹Ø±Õ ,6Îª×¼±¸ÐÝÏ¢,7Îª×¼±¸¹Ø±Õ
    int currentPassenger_need_service_time;	   //µ±Ç°³Ë¿ÍËùÐè·þÎñµÄ×ÜÊ±¼ä
    int currentPassenger_already_service_time; //µ±Ç°³Ë¿ÍÒÑ·þÎñÊ±¼ä
    int need_rest_time; 					   //°²¼ì¿Ú¼Æ»®ÐÝÏ¢Ê±¼ä
    int already_restTime;					   //°²¼ì¿ÚÒÑÐÝÏ¢Ê±¼ä
	int sum_already_restTime;  				   //°²¼ì¿ÚÀÛ¼ÆÐÝÏ¢Ê±¼ä
	double ask_for_rest_current_time;             //ÉêÇëÐÝÏ¢µÄÊ±¿Ì
}checkpoint;


typedef struct list2{
    int people;								//»º³åÇøµÄÈËÊý
    int isfull;								//»º³åÇøÊÇ·ñÒÑÂú
}buffer;


checkpoint cp[9];							//´´½¨Ò»¸öcheckpointÐÎµÄ½á¹¹ÌåÊý×é£¬ÓÃÓÚ´ú±í°Ë¸ö°²¼ì¿Ú
buffer bff;									//´´½¨Ò»¸öbufferÐÎµÄ½á¹¹Ìå£¬ÓÃÓÚ´ú±í»º³åÇø


int isOnDuty;								//intÐÎ±äÁ¿´ú±íµ±Ç°ÊÇ·ñ´¦ÓÚÉÏ°à×´Ì¬


clock_t start_time;							//´ú±í³ÌÐò¿ªÊ¼ÔËÐÐµÄÊ±¼ä

#endif // MODEL_H_INCLUDED
