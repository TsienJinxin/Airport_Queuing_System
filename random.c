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
//该函数返回值为一个处于 MinTimeLen和 MaxTimeLen之间的随机数

int generate_random_rest_time()
{

	int i;
	i = rand() % ( MaxRestTimeLen - MinRestTimeLen + 1) + MinRestTimeLen;
	return i;
}
//该函数返回值为一个处于 MinRestTimeLen和 MaxRestTimeLen之间的随机数
