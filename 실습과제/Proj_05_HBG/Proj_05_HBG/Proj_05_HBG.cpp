#define _CRT_SECURE_NO_WARNINGS
#define PROB 2 // 각각의 문제를 구현하고 해당 문제 번호를 변경하여 테스트

#include<iostream>

using namespace std;

#if PROB == 1
// 1번 문제를 해결하기 위한 프로그램 작성

struct Data {

	int NUMBER;


	char Eqn;

};



struct MyStack
{

	int capacity; // 현재 스택의 크기

	int top; // 위치

	Data* Data;

};



void InitStack(MyStack* s, int num)

{

	s->top = -1;

	s->capacity = num;

	s->Data = new Data[s->capacity];


}



int isfull(MyStack* s)

{

	return (s->top == s->capacity - 1);

}



int isEmpty(MyStack* s)

{

	return (s->top == -1);

}



Data pop(MyStack* s)

{

	if (isEmpty(s)) {

		cout << "스택 공백 에러" << endl;

		exit(1);

	}

	return s->Data[(s->top)--];

}



Data peek(MyStack* s)

{

	if (isEmpty(s)) {

		cout << "스택 공백 에러" << endl;

		exit(1);

	}

	return s->Data[s->top];

}


void push(MyStack* s, char C = '\0', int num = 0)
{

	if (isfull(s)) {



		int newCapacity = s->capacity * 2;

		Data* newData = new Data[newCapacity];





		for (int i = 0; i <= s->top; ++i) {

			newData[i] = s->Data[i];

		}



		delete[] s->Data;



		s->Data = newData;
		s->capacity = newCapacity;

	}

	s->top++;

	s->Data[s->top].Eqn = C;
	s->Data[s->top].NUMBER = num;

}



void FreeStack(MyStack* s)
{

	if (s->Data != nullptr) {

		delete[] s->Data;

		s->Data = nullptr;

		//cout << "메모리가 해제되었습니다." << '\n';
	}

}

int prec(char op)
{
	switch (op) {
	case '(' : case ')' :
		return 0;
	case '+' : case '-' :
		return 1;
	case '*' : case '/' :
		return 2;
	}
	return -1;
}

void infix_to_postfix(const char* expr, char* pexpr)
{
	int i{};
	int j{};

	char ch{}, top_op{};

	int len = strlen(expr);

	MyStack s;

	InitStack(&s, len);

	for (int i = 0; i < len; ++i) {
		ch = expr[i];
		switch (ch) {
		case '+': case '-': case '*': case '/':
			while (!isEmpty(&s) && (prec(ch) <= prec(peek(&s).Eqn))) {
				//cout << pop(&s).Eqn;
				pexpr[j++] = pop(&s).Eqn;
			}
			push(&s, ch);
			break;
		case '(' :
			push(&s, ch);
			break;
		case ')' :
			top_op = pop(&s).Eqn;
			// 왼쪽 괄호를 만날때까지 출력
			while (top_op != '(') {
				//printf("%c", top_op);
				pexpr[j++] = top_op;
				top_op = pop(&s).Eqn;
			}
			break;
		default :
			//cout << ch;
			pexpr[j++] = ch;
			break;
		}

	}

	while (!isEmpty(&s)) {
		//cout << pop(&s).Eqn;
		pexpr[j++] = pop(&s).Eqn;
	}
	pexpr[j] = '\0';

	FreeStack(&s);

}



int eval(char* pexpr)
{
	int i{}, num,num1{}, num2{};	// k 는 연산자용 , j 는 숫자용
	int op{};
	char ch{};

	MyStack NUM;

	int len = strlen(pexpr);

	InitStack(&NUM, len);

	for (int i = 0; i < len; ++i) {
		ch = pexpr[i];
		switch (ch) {
		case '+': 
			num2 = pop(&NUM).NUMBER;
			num1 = pop(&NUM).NUMBER;
			op = num1 + num2;
			push(&NUM,'\0', op);
			break;
		case '-':
			num2 = pop(&NUM).NUMBER;
			num1 = pop(&NUM).NUMBER;
			
			op = num1 - num2;
			push(&NUM, '\0', op);
			break;
		case '*':
			num2 = pop(&NUM).NUMBER;
			num1 = pop(&NUM).NUMBER;
			
			op = num1 * num2;
			push(&NUM, '\0', op);
			break;
		case '/':
			num2 = pop(&NUM).NUMBER;
			num1 = pop(&NUM).NUMBER;
			
			op = num1 / num2;
			push(&NUM, '\0', op);
			break;

		default:
			if (ch == ' ') continue;
			num = 0;
			while ( i < len && pexpr[i] >= '0' && pexpr[i] <= '9') {
				num = num * 10 + (pexpr[i++] - '0');
			}
			--i;
			push(&NUM, '\0', num);
		}
	}

	int res = pop(&NUM).NUMBER;

	if (!isEmpty(&NUM)) {
		cout << "연산 오류" << '\n';
		return 2025180028;
	}

	FreeStack(&NUM);
	return  res;	
}




// main 함수
int main(void)
{
	const char* expr = "100 + 11 * 20 *(20+ 10) / 100 +5 -3";
	char pexpr[100]; // 후위표기 수직 저장용
	int result; // 연산 결과 저장용
	printf("중위표기 수식 : %s \n", expr);
	infix_to_postfix(expr, pexpr);

	cout << "후위표기 수식 : " << pexpr << '\n';
	
	result = eval(pexpr);
	if (result != 2025180028) {
		printf("연산 결과 : %d \n", result);
	}
	return 0;
}
#elif PROB == 2
// 2번 문제를 해결하기 위한 프로그램 작성

#define MAZE_SIZE 8
char maze[MAZE_SIZE][MAZE_SIZE] = {
{'e', '0', '0', '0', '0', '0', '0', '1'},
	{'1', '1', '1', '1', '1', '1', '0', '1'},
	{'1', '0', '0', '0', '0', '0', '0', '1'},
	{'1', '0', '1', '1', '1', '1', '1', '1'},
	{'1', '0', '0', '0', '0', '0', '1', '1'}, 
	{'1', '0', '1', '1', '1', '0', '1', '1'},
	{'1', '0', '0', '0', '0', '0', '1', '1'},
	{'1', '1', '0', '1', 'x', '1', '1', '1'}

};


struct Data {

	int xPos;
	int yPos;

};



struct MyStack
{

	int capacity; // 현재 스택의 크기
	int top; // 위치

	Data* Data;

};



void InitStack(MyStack* s, int num)

{

	s->top = -1;

	s->capacity = num;

	s->Data = new Data[s->capacity];


}



int isfull(MyStack* s)

{

	return (s->top == s->capacity - 1);

}



int isEmpty(MyStack* s)

{

	return (s->top == -1);

}



Data pop(MyStack* s)

{

	if (isEmpty(s)) {

		cout << "스택 공백 에러" << endl;

		exit(1);

	}

	return s->Data[(s->top)--];

}



Data peek(MyStack* s)

{

	if (isEmpty(s)) {

		cout << "스택 공백 에러" << endl;

		exit(1);

	}

	return s->Data[s->top];

}


void push(MyStack* s, int xPos, int yPos)
{

	if (isfull(s)) {



		int newCapacity = s->capacity * 2;

		Data* newData = new Data[newCapacity];





		for (int i = 0; i <= s->top; ++i) {

			newData[i] = s->Data[i];

		}



		delete[] s->Data;



		s->Data = newData;
		s->capacity = newCapacity;

	}

	s->top++;

	s->Data[s->top].xPos = xPos;
	s->Data[s->top].yPos = yPos;

}



void FreeStack(MyStack* s)
{

	if (s->Data != nullptr) {

		delete[] s->Data;

		s->Data = nullptr;

		//cout << "메모리가 해제되었습니다." << '\n';
	}

}

void PrintMaze() 
{
	for (int i = 0; i < MAZE_SIZE; ++i) {
		for (int j = 0; j < MAZE_SIZE; ++j) {
			cout << maze[i][j] << " ";
		}
		cout << '\n';
	}
}

int SaveWay[MAZE_SIZE][MAZE_SIZE] = {0};

void PrintWay()
{
	cout << "경로"<<'\n' <<"(row, col)" << '\n';
	for (int i = 0; i < MAZE_SIZE; ++i) {
		for (int j = 0; j < MAZE_SIZE; ++j) {
			if (SaveWay[i][j] == 1) {
				cout << "( " << j << " , " << i << " )" << '\n';
			}
		}
	}

}

void FindEND()
{
	MyStack s;

	InitStack(&s, MAZE_SIZE);

	for (int i = 0; i < MAZE_SIZE; ++i) {
		for (int j = 0; j < MAZE_SIZE; ++j) {
			if (maze[i][j] == 'e') {
				push(&s, j, i);
				break;
			}

		}
	}

	cout << "입구의 위치 : (" << s.Data->xPos << ", " << s.Data->yPos << ")" << '\n';

	Data data{};

	while (!isEmpty(&s) && maze[peek(&s).yPos][peek(&s).xPos] != 'x') {
		//PrintMaze();
		//cout << "-----------------------" << endl;
		data = pop(&s);

		

		int x = data.xPos;
		int y = data.yPos;

		

		maze[y][x] = '*';
		SaveWay[y][x] = 1;

		if (y - 1 >= 0 && maze[y - 1][x] != '1' && maze[y - 1][x] != '*') {
			// 상
			push(&s, x, y - 1);
		}
		if (y + 1 < MAZE_SIZE && maze[y + 1][x] != '1' && maze[y + 1][x] != '*') {
			// 하
			push(&s, x, y + 1);
		}
		if (x - 1 >= 0 && maze[y][x - 1] != '1' && maze[y][x - 1] != '*') {
			// 좌
			push(&s, x - 1, y);
		}
		if (x + 1 < MAZE_SIZE && maze[y][x + 1] != '1' && maze[y][x + 1] != '*') {
			// 우
			push(&s, x + 1, y);
		}
	}

	if (isEmpty(&s)) {
		cout << "탈출 불가능한 미로입니다." << '\n';
		exit(2025180028);
	}

	FreeStack(&s);

}



int main()
{
	cout << "탐색 전" << '\n';
	cout << "---------------------" << '\n';
	PrintMaze();

	cout << '\n' << "탐색 후" << '\n';
	cout << "---------------------" << '\n';
	
	FindEND();

	

	PrintMaze();
	cout << "---------------------" << '\n';
	PrintWay();

}

#endif