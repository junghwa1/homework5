#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 4            //큐의 크기

typedef char element;
typedef struct {                    //큐 정의
	element queue[MAX_QUEUE_SIZE];
	int front, rear;
}QueueType;


QueueType *createQueue();           //큐 생성
int freeQueue(QueueType *cQ);       //동적 할당된 메모리 해제
int isEmpty(QueueType *cQ);         //큐가 완전히 비어있는지 확인
int isFull(QueueType *cQ);          //큐가 다 찼는지 확인
void enQueue(QueueType *cQ, element item);      //item 삽입
void deQueue(QueueType *cQ, element* item);     //item 삭제
void printQ(QueueType *cQ);         //큐 출력
void debugQ(QueueType *cQ);         //디버그
element getElement();               //item 입력


int main(void)
{
	QueueType *cQ = createQueue();      //cQ라는 큐 생성
	element data;                       //== char data

	char command;

    for(int i = 0; i < MAX_QUEUE_SIZE; i++)
        cQ->queue[i] = '\0';                //'\0'로 초기화

    printf("[----- [염중화] [2019038062] -----]\n");
	do{
		printf("\n----------------------------------------------------\n");        //메뉴 출력
		printf("                     Circular Q                       \n");
		printf("------------------------------------------------------\n");
		printf(" Insert=i,  Delete=d,   PrintQ=p,   Debug=b,   Quit=q \n");
		printf("------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);         //메뉴 선택

		switch(command) {
		case 'i': case 'I':
			data = getElement();    //함수를 통해 입력한 값을 data에 저장
			enQueue(cQ, data);      //cQ에 data삽입
			break;
		case 'd': case 'D':
			deQueue(cQ,&data);      //cQ의 front앞의 값을 삭제
			break;
		case 'p': case 'P':
			printQ(cQ);             //cQ 출력
			break;
		case 'b': case 'B':
			debugQ(cQ);             //cQ 디버그
			break;
		case 'q': case 'Q':         //프로그램 종료
			break;
		default:                    //메뉴 제외 값 입력시
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');   //메뉴 선택시 q 또는 Q 입력시 반복문 종료
    freeQueue(cQ);
	return 1;
}

QueueType *createQueue()        //큐 생성
{
	QueueType *cQ;
	cQ = (QueueType *)malloc(sizeof(QueueType));        //동적 메모리 할당
	cQ->front = 0;
	cQ->rear = 0;
	return cQ;          //cQ의 주소를 리턴
}

int freeQueue(QueueType *cQ)        //동적 할당된 메모리 해제
{
    if(cQ == NULL) return 1;        //큐 cQ에 아무것도 없을 때 리턴 1
    free(cQ);           //cQ 동적 할당 해제
    return 1;           //리턴 1
}

element getElement()        //item 입력
{
	element item;       //== char item;
	printf("Input element = ");
	scanf(" %c", &item);
	return item;        //입력한 값 리턴
}


int isEmpty(QueueType *cQ)          //큐가 완전히 비어있는지 확인
{
	if (cQ->front == cQ->rear){     //front와 rear의 값이 같다면 애러문구 출력 후 리턴 1
		printf("Circular Queue is empty!");
		return 1;
	}
	else return 0;                  //같지않다면 리턴 0
}

int isFull(QueueType *cQ)           //큐가 다 찼는지 확인
{
	if (((cQ->rear+1) % MAX_QUEUE_SIZE) == cQ->front) {       //rear+1이 front와 같다면(*원형 큐) 애러문구 출력 후 리턴 1
		printf(" Circular Queue is full!");
		return 1;
	}
	else return 0;                  //같지않다면 리턴 0
}

void enQueue(QueueType *cQ, element item)           //item 삽입
{
	if(isFull(cQ)) return;          //원형큐가 다 찼다면 함수 종료
	else {                          //그렇지 않다면
		cQ->rear = (cQ->rear + 1) % MAX_QUEUE_SIZE;     //rear = rear + 1 (rear = rear + 1을 원형 큐의 크기로 나눈 나머지)
		cQ->queue[cQ->rear] = item;     //원형 큐의 rear위치에 item의 값 저장
	}
}

void deQueue(QueueType *cQ, element *item)          //item 삭제
{
	if(isEmpty(cQ)) return;         //큐가 완전히 비어있다면 함수 종료
	else {                          //그렇지 않다면
		cQ->front = (cQ->front + 1) % MAX_QUEUE_SIZE;     //front = front + 1 (front = front + 1을 원형 큐의 크기로 나눈 나머지)
		cQ->queue[cQ->front]='\0';   //item이 가리키는 값에 큐의 front위치에 있는 값 저장
		return;
	}
}


void printQ(QueueType *cQ)      //큐 출력
{
	int i, first, last;

	first = (cQ->front + 1) % MAX_QUEUE_SIZE;   //원형 큐의 front 앞에 있는 값
	last = (cQ->rear + 1) % MAX_QUEUE_SIZE;     //원형 큐의 rear 앞에 있는 값

	printf("Circular Queue : [");

	i = first;
	while(i != last){       //원형 큐에서 front 앞에 위치에서 한칸씩 이동하며 출력 rear까지 출력
		printf("%3c", cQ->queue[i]);
		i = (i+1)%MAX_QUEUE_SIZE;

	}
	printf(" ]\n");
}


void debugQ(QueueType *cQ)      //디버그
{

	printf("\n---DEBUG\n");
	for(int i = 0; i < MAX_QUEUE_SIZE; i++)     //큐의 크기만큼 반복
	{
		if(i == cQ->front) {
			printf("  [%d] = front\n", i);      //front의 위치 출력
			continue;
		}
		printf("  [%d] = %c\n", i, cQ->queue[i]);   //값 출력

	}
	//printQ(cQ);
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear);     //rear와 front 위치 출력
}