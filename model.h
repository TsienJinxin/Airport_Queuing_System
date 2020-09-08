#include<stdio.h>
#include<time.h>

int MaxCustSingleLine;      //单队列最大等待乘客数
int MaxLines;              //蛇形缓冲区最多由MaxLines个直队组成
int MaxSeqLen;            //最大允许等待长度
int MinTimeLen;           //一次安检最短时长，单位为秒
int MaxTimeLen;          //一次安检最大时长，单位为秒
int MinRestTimeLen;       //安检口一次暂停休息最短时长，单位为秒
int MaxRestTimeLen;      //安检口一次暂停休息最大时长，单位为秒

typedef struct list1
{
    int people;                                //安检口排队的人数
    int state;								   //安检口状态，1为空闲，2为服务，3为休息，4为申请休息，5为关闭 ,6为准备休息,7为准备关闭
    int currentPassenger_need_service_time;	   //当前乘客所需服务的总时间
    int currentPassenger_already_service_time; //当前乘客已服务时间
    int need_rest_time; 					   //安检口计划休息时间
    int already_restTime;					   //安检口已休息时间
    int sum_already_restTime;  				   //安检口累计休息时间
    double ask_for_rest_current_time;             //申请休息的时刻
} checkpoint;


typedef struct list2
{
    int people;								//缓冲区的人数
    int isfull;								//缓冲区是否已满
} buffer;


checkpoint cp[9];							//创建一个checkpoint形的结构体数组，用于代表八个安检口
buffer bff;									//创建一个buffer形的结构体，用于代表缓冲区


int isOnDuty;								//int形变量代表当前是否处于上班状态


clock_t start_time;							//代表程序开始运行的时间
