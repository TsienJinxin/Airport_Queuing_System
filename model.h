#include<stdio.h>
#include<time.h>

int MaxCustSingleLine;      //���������ȴ��˿���
int MaxLines;              //���λ����������MaxLines��ֱ�����
int MaxSeqLen;            //�������ȴ�����
int MinTimeLen;           //һ�ΰ������ʱ������λΪ��
int MaxTimeLen;          //һ�ΰ������ʱ������λΪ��
int MinRestTimeLen;       //�����һ����ͣ��Ϣ���ʱ������λΪ��
int MaxRestTimeLen;      //�����һ����ͣ��Ϣ���ʱ������λΪ��

typedef struct list1
{
    int people;                                //������Ŷӵ�����
    int state;								   //�����״̬��1Ϊ���У�2Ϊ����3Ϊ��Ϣ��4Ϊ������Ϣ��5Ϊ�ر� ,6Ϊ׼����Ϣ,7Ϊ׼���ر�
    int currentPassenger_need_service_time;	   //��ǰ�˿�����������ʱ��
    int currentPassenger_already_service_time; //��ǰ�˿��ѷ���ʱ��
    int need_rest_time; 					   //����ڼƻ���Ϣʱ��
    int already_restTime;					   //���������Ϣʱ��
    int sum_already_restTime;  				   //������ۼ���Ϣʱ��
    double ask_for_rest_current_time;             //������Ϣ��ʱ��
} checkpoint;


typedef struct list2
{
    int people;								//������������
    int isfull;								//�������Ƿ�����
} buffer;


checkpoint cp[9];							//����һ��checkpoint�εĽṹ�����飬���ڴ���˸������
buffer bff;									//����һ��buffer�εĽṹ�壬���ڴ�������


int isOnDuty;								//int�α�������ǰ�Ƿ����ϰ�״̬


clock_t start_time;							//�������ʼ���е�ʱ��
