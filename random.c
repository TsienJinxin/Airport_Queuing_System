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
//�ú�������ֵΪһ������ MinTimeLen�� MaxTimeLen֮��������

int generate_random_rest_time()
{

	int i;
	i = rand() % ( MaxRestTimeLen - MinRestTimeLen + 1) + MinRestTimeLen;
	return i;
}
//�ú�������ֵΪһ������ MinRestTimeLen�� MaxRestTimeLen֮��������
