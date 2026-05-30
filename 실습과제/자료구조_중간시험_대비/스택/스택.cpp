#include<iostream>

using namespace std;

#define PROB 1 // 각각의 문제를 구현하고 해당 문제 번호를 변경하여 테스트

struct DATA
{
	int a;
	int b;
	int c;
};

struct STACK
{
	DATA* data;
	int top;
	int capacity;
};

void error(const char* c);

void callFunc(int n, STACK* s);

#if PROB == 1
// 배열로 구현

void Init(STACK* s, int capa)
{
	s->top = -1;
	s->capacity = capa;

	s->data = new DATA[capa];
}

int isFull(STACK* s)
{
	return (s->capacity - 1 == s->top);
}

int isEmpty(STACK* s)
{
	return (s->top == -1);
}

void push(STACK* s)
{
	if (!isFull(s)) {
		DATA data{};

		cout << "값을 입력하시오 : ";
		cin >> data.a >> data.b >> data.c;
		s->top++;
		s->data[s->top] = data;
	}
	else {
		cout << "스택이 포화상태 입니다" << '\n';
	}
}

DATA peek(STACK* s)
{
	if (!isEmpty(s)) {
		cout << s->data[s->top].a << ", " << s->data[s->top].b << ", " << s->data[s->top].c;
		return s->data[s->top];
	}

	error("스택에 데이터가 없습니다.");
}

DATA pop(STACK* s)
{
	if (!isEmpty(s)) {
		DATA tmp = s->data[s->top];
		cout << s->data[s->top].a << ", " << s->data[s->top].b << ", " << s->data[s->top].c;
		s->top--;
		return tmp;
	}
	error("스택에 데이터가 없습니다.");
}

#elif PROB == 2

#endif
//-------------------------------------------
int main()
//-------------------------------------------
{
	STACK s;

	int capa;

	cout << "용량 : ";
	cin >> capa;

	Init(&s, capa);

	int call;

	while (true) {

		cout << "불러올 함수 : ";
		cin >> call;
		callFunc(call, &s);
	}

}

void error(const char* c)
{
	cout << c << endl;
	exit(2025180028);
}

void callFunc(int n, STACK* s)
{
	switch (n)
	{
	case 1:
		push(s);
		break;
	case 2:
		pop(s);
		break;
	case 3:
		peek(s);
		break;
	default:
		break;
	}
}