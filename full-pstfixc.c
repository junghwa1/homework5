#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

#define MAX_STACK_SIZE 10       //스택 배열 크기
#define MAX_EXPRESSION_SIZE 20  //입력 값 을 저장할 배열 크기

/* stack 내에서 우선순위는 내림차순, lparen = 0 가장 낮음 */
typedef enum{
	lparen = 0,  /* ( 왼쪽 괄호 */
	rparen = 9,  /* ) 오른쪽 괄호*/
	times = 7,   /* * 곱셈 */
	divide = 6,  /* / 나눗셈 */
	plus = 5,    /* + 덧셈 */
	minus = 4,   /* - 뺄셈 */
	operand = 1 /* 피연산자 */
} precedence;                       //우선 순위 typedef enum

char infixExp[MAX_EXPRESSION_SIZE];     //infix 방식(중위 표기법) ex) 3 + 4
char postfixExp[MAX_EXPRESSION_SIZE];   //postfix 방식(후위 표기법) ex) 3 4 +
char postfixStack[MAX_STACK_SIZE];      //postfix 스택
int evalStack[MAX_STACK_SIZE];          //계산 스택

int postfixStackTop = -1;               //posfix 스택의 탑을 -1로 초기화
int evalStackTop = -1;                  //계산 스택의 탑을 -1로 초기화

int evalResult = 0;                     //계산 결과

void postfixPush(char x);               //연산자를 postfix 스택에 push
char postfixPop();                      //연산자를 postfix 스택에서 pop
void evalPush(int x);                   //숫자를 계산 스택에 push
int evalPop();                          //숫자를 계산 스택에서 pop
void getInfix();                        //중위 표기법으로 된 수식을 입력받음
precedence getToken(char symbol);       //symbol을 precedence안에 정의 된 별칭에 맞게 리턴
precedence getPriority(char x);         //return getToken(x);
void charCat(char* c);                  //문자하나를 전달받아, postfixExp에 추가
void toPostfix();                       //infixExp의 문자를 하나씩 읽어가면서 stack을 이용하여 postfix로 변경
void debug();                           //디버그 함수
void reset();                           //reset 함수
void evaluation();                      //postfixExp의 문자를 하나씩 읽어가면서 계산

int main()
{
	char command;
        printf("[----- [염중화] [2019038062] -----]\n");
	do{
		printf("----------------------------------------------------------------\n");       //메뉴 출력
		printf("               Infix to Postfix, then Evaluation               \n");
		printf("----------------------------------------------------------------\n");
		printf(" Infix=i,   Postfix=p,  Eval=e,   Debug=d,   Reset=r,   Quit=q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);             //메뉴 선택

		switch(command) {
		case 'i': case 'I':
			getInfix();                     //수식 입력(infix 방식)
			break;
		case 'p': case 'P':
			toPostfix();                    //infix로 입력된 수식을 postfix로 변경
			break;
		case 'e': case 'E':
			evaluation();                   //계산 결과 출력
			break;
		case 'd': case 'D':
			debug();                        //디버그
			break;
		case 'r': case 'R':
			reset();                        //리셋
			break;
		case 'q': case 'Q':
			break;                          //프로그램 종료
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");      //메뉴 이외의 값 입력시 출력
			break;
		}

	}while(command != 'q' && command != 'Q');       //메뉴 선택시 q 또는 Q 입력시 반복문 종료

	return 1;
}

void postfixPush(char x)        //연산자를 포스픽스 스택에 저장(push)
{
    postfixStack[++postfixStackTop] = x;        //top + 1 후 x값을 스택에 저장
}

char postfixPop()               //연산자를 포스픽스 스택에서 빼내옴(pop)
{
	char x;
    if(postfixStackTop == -1)   //스택에 저장된 값이 없을 경우
        return '\0';            //'\0'리턴
    else {                      //스택에 저장된 값이 있을 경우
    	x = postfixStack[postfixStackTop--];    //스택의 탑에 있는 값을 x에 저장 후 top - 1
    }
    return x;   //원래 top에 저장됐던 값을 리턴
}

void evalPush(int x)            //숫자를 계산 스택에 저장(push)
{
    evalStack[++evalStackTop] = x;  //x를 계산 스택의 top에 저장 후 top + 1
}

int evalPop()                   //숫자를 계산 스택에서 빼내옴(pop)
{
    if(evalStackTop == -1)      //top이 -1이면 -1 리턴
        return -1;
    else                        //그렇지 않으면 top에 저장된 값을 리턴 후 top - 1
        return evalStack[evalStackTop--];
}

/**
 * infix expression을 입력받는다.
 * infixExp에는 입력된 값을 저장한다.
 */

void getInfix()                 //수식 입력(infix 방식)
{
    int err=0;					//오류 확인 변수
	printf("Type the expression >>> ");
    scanf("%s",infixExp);
	for (int i=0;infixExp[i]!='\0';i++){		//가능한 숫자: 0 ∼ 9 한자리 수,  가능한 연산자: ‘+’, ‘-’, ‘*’, ‘\’, ‘(’, ‘)’
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
				err=1;			//이외의 값은 오류
				break;
			}
		}
	}
	if(err==1)		//err이 1이면 에러문구 출력
		printf("-----input 0~9 number or '(', ')', '+', '-', '/', '*'-----\n-----please reset-----\n");
}

precedence getToken(char symbol)       //symbol을 precedence안에 정의 된 별칭으로 리턴
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
 * 문자하나를 전달받아, postfixExp에 추가
 */
void charCat(char* c)
{
	if (postfixExp == '\0')
		strncpy(postfixExp, c, 1);      //문자 c를 복사하여 postfixExp에 저장
	else
		strncat(postfixExp, c, 1);      //문자 c를 postfixExp문자열 뒤에 추가
}

/**
 * infixExp의 문자를 하나씩 읽어가면서 stack을 이용하여 postfix로 변경한다.
 * 변경된 postfix는 postFixExp에 저장된다.
 */
void toPostfix()
{
	/* infixExp의 문자 하나씩을 읽기위한 포인터 */
	char *exp = infixExp;
	char x; /* 문자하나를 임시로 저장하기 위한 변수 */
	int i=0;	//처음 문자를 읽을 경우 i=0;
	/* exp를 증가시켜가면서, 문자를 읽고 postfix로 변경 */
	while(*exp != '\0')
	{
		if(getPriority(*exp) == operand)        //숫자일 경우
		{
			if((i!=0)&&(getPriority(*(exp-1))== operand)){	//그 전의 문자가 숫자일 경우 에러문구 출력
				printf("-----input 0~9 number, please reset-----\n");
				return;					//반복문 종료
			}
			x = *exp;
        	charCat(&x);        //postfixExp에 추가
		}
		
        else if(getPriority(*exp) == lparen) {  //왼쪽 괄호일 경우

        	postfixPush(*exp);        //연산자를 postfixStack에 저장(push)
        }
        else if(getPriority(*exp) == rparen)    //오른쪽 괄호일 경우
        {
        	while((x = postfixPop()) != '(') {  //오른쪽부터 읽으면서 왼쪽 괄호가 나오기 전까지 postfixExp에 추가
        		charCat(&x);
        	}
        }else if(postfixStackTop==-1)           //postfixStackTop가 -1이 아니면
        {
            postfixPush(*exp);        //연산자를 postfixStack에 저장(push)
        }
        else
        {
            while((getPriority(postfixStack[postfixStackTop]) >= getPriority(*exp)))    //스택의 탑에 있는 연산자의 우선 순위가 exp의 우선순위보다 같거나 클때 
            {
            	x = postfixPop();           //스택의 탑에 있는 연산자를 x에 저장
            	charCat(&x);                //postfixExp에 x추가
            }
            postfixPush(*exp);        //연산자를 postfixStack에 저장(push)
        }
        exp++;
		i=1;
	}

    while(postfixStackTop != -1)    //스택의 탑이 -1이 아니면 반복
    {
    	x = postfixPop();           //스택의 탑에 있는 연산자를 x에 저장
    	charCat(&x);                //postfixExp에 x추가
    }

}

void debug()        //디버그
{
	printf("\n---DEBUG\n");
	printf("infixExp =  %s\n", infixExp);       //infix 방식의 수식
	printf("postExp =  %s\n", postfixExp);      //postfix 방식의 수식
	printf("eval result = %d\n", evalResult);   //계산 결과

	printf("postfixStack : ");                  //계산 전 postfixStack에 남은 연산자
	for(int i = 0; i < MAX_STACK_SIZE; i++)
		printf("%c  ", postfixStack[i]);

	printf("\n");

}

void reset()        //리셋(초기 상태)
{
	infixExp[0] = '\0';
	postfixExp[0] = '\0';

	for(int i = 0; i < MAX_STACK_SIZE; i++)
		postfixStack[i] = '\0';
         
	postfixStackTop = -1;
	evalStackTop = -1;
	evalResult = 0;
}

void evaluation()   //postfixExp의 문자를 하나씩 읽어가면서 계산
{
	int opr1, opr2, i;

	int length = strlen(postfixExp);    //postfixExp 문자열의 길이를 length에 저장
	char symbol;
	evalStackTop = -1;

	for(i = 0; i < length; i++)
	{
		symbol = postfixExp[i];
		if(getToken(symbol) == operand) {   //symbol이 숫자로 표현된 문자일 때 
			evalPush(symbol - '0');         //10진수로 나타내려면 '0'의 아스키 코드 값(48)을 빼주고 스택에 저장
		}
		else {
			opr2 = evalPop();               //evalStack의 top에 저장된 값
			opr1 = evalPop();               //evalStack의 top에 저장된 값
			switch(getToken(symbol)) {      //연산자에 맞는 연산을 실행한 뒤 계산 스택의 top에 저장
			case plus: evalPush(opr1 + opr2); break;
			case minus: evalPush(opr1 - opr2); break;
			case times: evalPush(opr1 * opr2); break;
			case divide: evalPush(opr1 / opr2); break;
			default: break;
			}
		}
	}
    for(int i = 0; i < MAX_STACK_SIZE; i++)
		postfixStack[i] = '\0';             //계산 후 스택에 남아있는 연산자 제거
	evalResult = evalPop();                 //스택의 top에 저장된 값을 evalResult에 저장(연산이 올바르게 되었으면 top은 0)
}

