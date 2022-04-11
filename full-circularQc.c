#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 4            //ť�� ũ��

typedef char element;
typedef struct {                    //ť ����
	element queue[MAX_QUEUE_SIZE];
	int front, rear;
}QueueType;


QueueType *createQueue();           //ť ����
int freeQueue(QueueType *cQ);       //���� �Ҵ�� �޸� ����
int isEmpty(QueueType *cQ);         //ť�� ������ ����ִ��� Ȯ��
int isFull(QueueType *cQ);          //ť�� �� á���� Ȯ��
void enQueue(QueueType *cQ, element item);      //item ����
void deQueue(QueueType *cQ, element* item);     //item ����
void printQ(QueueType *cQ);         //ť ���
void debugQ(QueueType *cQ);         //�����
element getElement();               //item �Է�


int main(void)
{
	QueueType *cQ = createQueue();      //cQ��� ť ����
	element data;                       //== char data

	char command;

    for(int i = 0; i < MAX_QUEUE_SIZE; i++)
        cQ->queue[i] = '\0';                //'\0'�� �ʱ�ȭ

    printf("[----- [����ȭ] [2019038062] -----]\n");
	do{
		printf("\n----------------------------------------------------\n");        //�޴� ���
		printf("                     Circular Q                       \n");
		printf("------------------------------------------------------\n");
		printf(" Insert=i,  Delete=d,   PrintQ=p,   Debug=b,   Quit=q \n");
		printf("------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);         //�޴� ����

		switch(command) {
		case 'i': case 'I':
			data = getElement();    //�Լ��� ���� �Է��� ���� data�� ����
			enQueue(cQ, data);      //cQ�� data����
			break;
		case 'd': case 'D':
			deQueue(cQ,&data);      //cQ�� front���� ���� ����
			break;
		case 'p': case 'P':
			printQ(cQ);             //cQ ���
			break;
		case 'b': case 'B':
			debugQ(cQ);             //cQ �����
			break;
		case 'q': case 'Q':         //���α׷� ����
			break;
		default:                    //�޴� ���� �� �Է½�
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');   //�޴� ���ý� q �Ǵ� Q �Է½� �ݺ��� ����
    freeQueue(cQ);
	return 1;
}

QueueType *createQueue()        //ť ����
{
	QueueType *cQ;
	cQ = (QueueType *)malloc(sizeof(QueueType));        //���� �޸� �Ҵ�
	cQ->front = 0;
	cQ->rear = 0;
	return cQ;          //cQ�� �ּҸ� ����
}

int freeQueue(QueueType *cQ)        //���� �Ҵ�� �޸� ����
{
    if(cQ == NULL) return 1;        //ť cQ�� �ƹ��͵� ���� �� ���� 1
    free(cQ);           //cQ ���� �Ҵ� ����
    return 1;           //���� 1
}

element getElement()        //item �Է�
{
	element item;       //== char item;
	printf("Input element = ");
	scanf(" %c", &item);
	return item;        //�Է��� �� ����
}


int isEmpty(QueueType *cQ)          //ť�� ������ ����ִ��� Ȯ��
{
	if (cQ->front == cQ->rear){     //front�� rear�� ���� ���ٸ� �ַ����� ��� �� ���� 1
		printf("Circular Queue is empty!");
		return 1;
	}
	else return 0;                  //�����ʴٸ� ���� 0
}

int isFull(QueueType *cQ)           //ť�� �� á���� Ȯ��
{
	if (((cQ->rear+1) % MAX_QUEUE_SIZE) == cQ->front) {       //rear+1�� front�� ���ٸ�(*���� ť) �ַ����� ��� �� ���� 1
		printf(" Circular Queue is full!");
		return 1;
	}
	else return 0;                  //�����ʴٸ� ���� 0
}

void enQueue(QueueType *cQ, element item)           //item ����
{
	if(isFull(cQ)) return;          //����ť�� �� á�ٸ� �Լ� ����
	else {                          //�׷��� �ʴٸ�
		cQ->rear = (cQ->rear + 1) % MAX_QUEUE_SIZE;     //rear = rear + 1 (rear = rear + 1�� ���� ť�� ũ��� ���� ������)
		cQ->queue[cQ->rear] = item;     //���� ť�� rear��ġ�� item�� �� ����
	}
}

void deQueue(QueueType *cQ, element *item)          //item ����
{
	if(isEmpty(cQ)) return;         //ť�� ������ ����ִٸ� �Լ� ����
	else {                          //�׷��� �ʴٸ�
		cQ->front = (cQ->front + 1) % MAX_QUEUE_SIZE;     //front = front + 1 (front = front + 1�� ���� ť�� ũ��� ���� ������)
		cQ->queue[cQ->front]='\0';   //item�� ����Ű�� ���� ť�� front��ġ�� �ִ� �� ����
		return;
	}
}


void printQ(QueueType *cQ)      //ť ���
{
	int i, first, last;

	first = (cQ->front + 1) % MAX_QUEUE_SIZE;   //���� ť�� front �տ� �ִ� ��
	last = (cQ->rear + 1) % MAX_QUEUE_SIZE;     //���� ť�� rear �տ� �ִ� ��

	printf("Circular Queue : [");

	i = first;
	while(i != last){       //���� ť���� front �տ� ��ġ���� ��ĭ�� �̵��ϸ� ��� rear���� ���
		printf("%3c", cQ->queue[i]);
		i = (i+1)%MAX_QUEUE_SIZE;

	}
	printf(" ]\n");
}


void debugQ(QueueType *cQ)      //�����
{

	printf("\n---DEBUG\n");
	for(int i = 0; i < MAX_QUEUE_SIZE; i++)     //ť�� ũ�⸸ŭ �ݺ�
	{
		if(i == cQ->front) {
			printf("  [%d] = front\n", i);      //front�� ��ġ ���
			continue;
		}
		printf("  [%d] = %c\n", i, cQ->queue[i]);   //�� ���

	}
	//printQ(cQ);
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear);     //rear�� front ��ġ ���
}