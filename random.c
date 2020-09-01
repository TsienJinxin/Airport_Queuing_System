#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "model.h"

int generate_random_service_time()
{
	int i;
	i = (int)(rand() % ( MaxTimeLen - MinTimeLen + 1) + MinTimeLen);
	return i;
}
//¸Ãº¯Êý·µ»ØÖµÎªÒ»¸ö´¦ÓÚ MinTimeLenºÍ MaxTimeLenÖ®¼äµÄËæ»úÊý

int generate_random_rest_time()
{
	int i;
	i = rand() % ( MaxRestTimeLen - MinRestTimeLen + 1) + MinRestTimeLen;
	return i;
}
//¸Ãº¯Êý·µ»ØÖµÎªÒ»¸ö´¦ÓÚ MinRestTimeLenºÍ MaxRestTimeLenÖ®¼äµÄËæ»úÊý
