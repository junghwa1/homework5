#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

#define MAX_STACK_SIZE 10       //���� �迭 ũ��
#define MAX_EXPRESSION_SIZE 20  //�Է� �� �� ������ �迭 ũ��

/* stack ������ �켱������ ��������, lparen = 0 ���� ���� */
typedef enum{
	lparen = 0,  /* ( ���� ��ȣ */
	rparen = 9,  /* ) ������ ��ȣ*/
	times = 7,   /* * ���� */
	divide = 6,  /* / ������ */
	plus = 5,    /* + ���� */
	minus = 4,   /* - ���� */
	operand = 1 /* �ǿ����� */
} precedence;                       //�켱 ���� typedef enum

char infixExp[MAX_EXPRESSION_SIZE];     //infix ���(���� ǥ���) ex) 3 + 4
char postfixExp[MAX_EXPRESSION_SIZE];   //postfix ���(���� ǥ���) ex) 3 4 +
char postfixStack[MAX_STACK_SIZE];      //postfix ����
int evalStack[MAX_STACK_SIZE];          //��� ����

int postfixStackTop = -1;               //posfix ������ ž�� -1�� �ʱ�ȭ
int evalStackTop = -1;                  //��� ������ ž�� -1�� �ʱ�ȭ

int evalResult = 0;                     //��� ���

void postfixPush(char x);               //�����ڸ� postfix ���ÿ� push
char postfixPop();                      //�����ڸ� postfix ���ÿ��� pop
void evalPush(int x);                   //���ڸ� ��� ���ÿ� push
int evalPop();                          //���ڸ� ��� ���ÿ��� pop
void getInfix();                        //���� ǥ������� �� ������ �Է¹���
precedence getToken(char symbol);       //symbol�� precedence�ȿ� ���� �� ��Ī�� �°� ����
precedence getPriority(char x);         //return getToken(x);
void charCat(char* c);                  //�����ϳ��� ���޹޾�, postfixExp�� �߰�
void toPostfix();                       //infixExp�� ���ڸ� �ϳ��� �о�鼭 stack�� �̿��Ͽ� postfix�� ����
void debug();                           //����� �Լ�
void reset();                           //reset �Լ�
void evaluation();                      //postfixExp�� ���ڸ� �ϳ��� �о�鼭 ���

int main()
{
	char command;
        printf("[----- [����ȭ] [2019038062] -----]\n");
	do{
		printf("----------------------------------------------------------------\n");       //�޴� ���
		printf("               Infix to Postfix, then Evaluation               \n");
		printf("----------------------------------------------------------------\n");
		printf(" Infix=i,   Postfix=p,  Eval=e,   Debug=d,   Reset=r,   Quit=q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);             //�޴� ����

		switch(command) {
		case 'i': case 'I':
			getInfix();                     //���� �Է�(infix ���)
			break;
		case 'p': case 'P':
			toPostfix();                    //infix�� �Էµ� ������ postfix�� ����
			break;
		case 'e': case 'E':
			evaluation();                   //��� ��� ���
			break;
		case 'd': case 'D':
			debug();                        //�����
			break;
		case 'r': case 'R':
			reset();                        //����
			break;
		case 'q': case 'Q':
			break;                          //���α׷� ����
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");      //�޴� �̿��� �� �Է½� ���
			break;
		}

	}while(command != 'q' && command != 'Q');       //�޴� ���ý� q �Ǵ� Q �Է½� �ݺ��� ����

	return 1;
}

void postfixPush(char x)        //�����ڸ� �����Ƚ� ���ÿ� ����(push)
{
    postfixStack[++postfixStackTop] = x;        //top + 1 �� x���� ���ÿ� ����
}

char postfixPop()               //�����ڸ� �����Ƚ� ���ÿ��� ������(pop)
{
	char x;
    if(postfixStackTop == -1)   //���ÿ� ����� ���� ���� ���
        return '\0';            //'\0'����
    else {                      //���ÿ� ����� ���� ���� ���
    	x = postfixStack[postfixStackTop--];    //������ ž�� �ִ� ���� x�� ���� �� top - 1
    }
    return x;   //���� top�� ����ƴ� ���� ����
}

void evalPush(int x)            //���ڸ� ��� ���ÿ� ����(push)
{
    evalStack[++evalStackTop] = x;  //x�� ��� ������ top�� ���� �� top + 1
}

int evalPop()                   //���ڸ� ��� ���ÿ��� ������(pop)
{
    if(evalStackTop == -1)      //top�� -1�̸� -1 ����
        return -1;
    else                        //�׷��� ������ top�� ����� ���� ���� �� top - 1
        return evalStack[evalStackTop--];
}

/**
 * infix expression�� �Է¹޴´�.
 * infixExp���� �Էµ� ���� �����Ѵ�.
 */

void getInfix()                 //���� �Է�(infix ���)
{
    int err=0;					//���� Ȯ�� ����
	printf("Type the expression >>> ");
    scanf("%s",infixExp);
	for (int i=0;infixExp[i]!='\0';i++){		//������ ����: 0 �� 9 ���ڸ� ��,  ������ ������: ��+��, ��-��, ��*��, ��\��, ��(��, ��)��
		switch(infixExp[i]){
			case '(' : break;
			case ')' : break;
			case '+' : break;
			case '-' : break;
			case '/' : break;
			case '*' : break;
			case '0' : break;
			case '1' : break;
			case '2' : break;
			case '3' : break;
			case '4' : break;
			case '5' : break;
			case '6' : break;
			case '7' : break;
			case '8' : break;
			case '9' : break;
			default : {
				err=1;			//�̿��� ���� ����
				break;
			}
		}
	}
	if(err==1)		//err�� 1�̸� �������� ���
		printf("-----input 0~9 number or '(', ')', '+', '-', '/', '*'-----\n-----please reset-----\n");
}

precedence getToken(char symbol)       //symbol�� precedence�ȿ� ���� �� ��Ī���� ����
{
	switch(symbol) {
	case '(' : return lparen;
	case ')' : return rparen;
	case '+' : return plus;
	case '-' : return minus;
	case '/' : return divide;
	case '*' : return times;
	default : return operand;
	}
}

precedence getPriority(char x)         //return getToken(x);
{
	return getToken(x);
}

/**
 * �����ϳ��� ���޹޾�, postfixExp�� �߰�
 */
void charCat(char* c)
{
	if (postfixExp == '\0')
		strncpy(postfixExp, c, 1);      //���� c�� �����Ͽ� postfixExp�� ����
	else
		strncat(postfixExp, c, 1);      //���� c�� postfixExp���ڿ� �ڿ� �߰�
}

/**
 * infixExp�� ���ڸ� �ϳ��� �о�鼭 stack�� �̿��Ͽ� postfix�� �����Ѵ�.
 * ����� postfix�� postFixExp�� ����ȴ�.
 */
void toPostfix()
{
	/* infixExp�� ���� �ϳ����� �б����� ������ */
	char *exp = infixExp;
	char x; /* �����ϳ��� �ӽ÷� �����ϱ� ���� ���� */
	int i=0;	//ó�� ���ڸ� ���� ��� i=0;
	/* exp�� �������Ѱ��鼭, ���ڸ� �а� postfix�� ���� */
	while(*exp != '\0')
	{
		if(getPriority(*exp) == operand)        //������ ���
		{
			if((i!=0)&&(getPriority(*(exp-1))== operand)){	//�� ���� ���ڰ� ������ ��� �������� ���
				printf("-----input 0~9 number, please reset-----\n");
				return;					//�ݺ��� ����
			}
			x = *exp;
        	charCat(&x);        //postfixExp�� �߰�
		}
		
        else if(getPriority(*exp) == lparen) {  //���� ��ȣ�� ���

        	postfixPush(*exp);        //�����ڸ� postfixStack�� ����(push)
        }
        else if(getPriority(*exp) == rparen)    //������ ��ȣ�� ���
        {
        	while((x = postfixPop()) != '(') {  //�����ʺ��� �����鼭 ���� ��ȣ�� ������ ������ postfixExp�� �߰�
        		charCat(&x);
        	}
        }else if(postfixStackTop==-1)           //postfixStackTop�� -1�� �ƴϸ�
        {
            postfixPush(*exp);        //�����ڸ� postfixStack�� ����(push)
        }
        else
        {
            while((getPriority(postfixStack[postfixStackTop]) >= getPriority(*exp)))    //������ ž�� �ִ� �������� �켱 ������ exp�� �켱�������� ���ų� Ŭ�� 
            {
            	x = postfixPop();           //������ ž�� �ִ� �����ڸ� x�� ����
            	charCat(&x);                //postfixExp�� x�߰�
            }
            postfixPush(*exp);        //�����ڸ� postfixStack�� ����(push)
        }
        exp++;
		i=1;
	}

    while(postfixStackTop != -1)    //������ ž�� -1�� �ƴϸ� �ݺ�
    {
    	x = postfixPop();           //������ ž�� �ִ� �����ڸ� x�� ����
    	charCat(&x);                //postfixExp�� x�߰�
    }

}

void debug()        //�����
{
	printf("\n---DEBUG\n");
	printf("infixExp =  %s\n", infixExp);       //infix ����� ����
	printf("postExp =  %s\n", postfixExp);      //postfix ����� ����
	printf("eval result = %d\n", evalResult);   //��� ���

	printf("postfixStack : ");                  //��� �� postfixStack�� ���� ������
	for(int i = 0; i < MAX_STACK_SIZE; i++)
		printf("%c  ", postfixStack[i]);

	printf("\n");

}

void reset()        //����(�ʱ� ����)
{
	infixExp[0] = '\0';
	postfixExp[0] = '\0';

	for(int i = 0; i < MAX_STACK_SIZE; i++)
		postfixStack[i] = '\0';
         
	postfixStackTop = -1;
	evalStackTop = -1;
	evalResult = 0;
}

void evaluation()   //postfixExp�� ���ڸ� �ϳ��� �о�鼭 ���
{
	int opr1, opr2, i;

	int length = strlen(postfixExp);    //postfixExp ���ڿ��� ���̸� length�� ����
	char symbol;
	evalStackTop = -1;

	for(i = 0; i < length; i++)
	{
		symbol = postfixExp[i];
		if(getToken(symbol) == operand) {   //symbol�� ���ڷ� ǥ���� ������ �� 
			evalPush(symbol - '0');         //10������ ��Ÿ������ '0'�� �ƽ�Ű �ڵ� ��(48)�� ���ְ� ���ÿ� ����
		}
		else {
			opr2 = evalPop();               //evalStack�� top�� ����� ��
			opr1 = evalPop();               //evalStack�� top�� ����� ��
			switch(getToken(symbol)) {      //�����ڿ� �´� ������ ������ �� ��� ������ top�� ����
			case plus: evalPush(opr1 + opr2); break;
			case minus: evalPush(opr1 - opr2); break;
			case times: evalPush(opr1 * opr2); break;
			case divide: evalPush(opr1 / opr2); break;
			default: break;
			}
		}
	}
    for(int i = 0; i < MAX_STACK_SIZE; i++)
		postfixStack[i] = '\0';             //��� �� ���ÿ� �����ִ� ������ ����
	evalResult = evalPop();                 //������ top�� ����� ���� evalResult�� ����(������ �ùٸ��� �Ǿ����� top�� 0)
}

