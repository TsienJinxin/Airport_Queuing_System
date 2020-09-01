#include <stdio.h>
#include "model.h"

int isTerminate(){
	int i=1;
	//i×÷Îª³ÌÐòÊÇ·ñÖÕÖ¹µÄÅÐ¶ÏÌõ¼þÖ®Ò»
	//Ö»ÓÐµ±ËùÓÐ°²¼ì¿ÚµÄÈËÊý¶¼Îª0Ê±£¬iµÄÖµÎª1

	int c;    //cÎª¼ÆÊýÆ÷£¬ÓÃÓÚÑ­»·
	for(c=1;c<=8;c++){
		if(cp[c].people!=0){
			i=0;
			break;
		}
	}
	//±éÀúÑ­»·£¬ÇóµÃiµÄÖµ

	if(isOnDuty==0&&i==1&&bff.people==0)
	return 1;
	//ÈôÊÕµ½ÏÂ°àÃüÁîºó£¬ÇÒ»º³åÇøÒÔ¼°°²¼ì¿ÚÖÐµÄÈËÊý¶¼Îª0ÊÇ£¬³ÌÐòÖÕÖ¹£¬·µ»Ø1
	return 0;
}
