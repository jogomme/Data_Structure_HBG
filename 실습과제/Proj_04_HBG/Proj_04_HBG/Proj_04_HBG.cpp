#include <iostream>

#include <random>

#include <cstdlib>

using namespace std;


struct Data {

	int Point;

	char parenthesis;

	int check;
};



struct MyStack
{

	int capacity; // 현재 스택의 크기

	int top; // 위치

	Data* Data;

};

struct Error
{
	Data* pData;
	bool FindError = false;
};

void InitError(Error* e, int n)
{
	e->pData = new Data[n];
}



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





void push(MyStack* s, char C, int num, int code = 0)
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

	s->Data[s->top].parenthesis = C;
	s->Data[s->top].Point = num;
	s->Data[s->top].check = code;

}



void FreeStack(MyStack* s) 
{

	if (s->Data != nullptr) {

		delete[] s->Data;

		s->Data = nullptr;

	}

}

int findMatch(MyStack* s, char c) 
{
	int i{};

	if (c == ')') {
		while (true) {
			if (s->Data[i].parenthesis = '(') return i;
		}
	}
	if (c == '}') {
		while (true) {
			if (s->Data[i].parenthesis = '{') return i;
		}
	}if (c == ']') {
		while (true) {
			if (s->Data[i].parenthesis = '[') return i;
		}
	}
	
	exit(2);
}



MyStack CheckMatching(const char* c)
{

	MyStack s;
	MyStack ForRe;


	char ch;


	Data open_ch;

	int n = strlen(c);

	InitStack(&ForRe, n);
	InitStack(&s, n);

	cout << c << '\n';

	int num{};
	char* line = new char[n];

	for (int i = 0; i < n; ++i) {
		ch = c[i];
		switch (ch)
		{
		case '(': case '[': case '{': {

			line[i] = '-';
			push(&s, ch, i);

			break;

		}
		case ')': case ']': case '}':

			if (isEmpty(&s)) {
				line[i] = '^';
				push(&ForRe, ch, i, 1);
			}
			else
			{
				open_ch = pop(&s);
				if ((open_ch.parenthesis == '(' && ch != ')') || (open_ch.parenthesis == '[' && ch != ']') || (open_ch.parenthesis == '{' && ch != '}')) {
					push(&ForRe, open_ch.parenthesis, open_ch.Point, 2);
					push(&ForRe, ch, i, 2);
					line[open_ch.Point] = '^';
					line[i] = '^';
				}
				else {
					line[i] = '-';
				}
			}

			break;

		default:
			line[i] = '-';
		}
	}

	

	if (!isEmpty(&s)) {

		Data left;

		while (!isEmpty(&s)) {
			line[peek(&s).Point] = '^';
			left = pop(&s);
			push(&ForRe, left.parenthesis, left.Point, 3);
		}

		for (int i = 0; i < n; ++i){
		
			
			cout << line[i];
		}

		return ForRe;
	}; // 스택에 남아있으면 오류

	

	for (int i = 0; i < n; ++i){
		cout << line[i];
	}
	return ForRe;

}





int main()
{

	const char* p = "A(x) = 24.5 * ( x + func(x, y)) * ({( r * r * 3.14 ) / [ 7%10* sqrt(25)];";

	MyStack Checked = CheckMatching(p);
	cout << '\n';

	// 검사 코드
	//while (!isEmpty(&Checked)) {
	//	Data Error = pop(&Checked);
	//	cout << Error.check;
	//	cout << Error.parenthesis << endl;
	//}

	if (!isEmpty(&Checked)) {
		while(!isEmpty(&Checked)){
			Data Error = pop(&Checked);
			if (Error.check == 3) {
					cout << "왼쪽 괄호 " << Error.parenthesis << " 오류: 위치 " << Error.Point << '\n';
			}
			else if (Error.check == 1) {
					cout << "오른쪽 괄호 " << Error.parenthesis << " 오류 위치 : " << Error.Point+1 << '\n';
			}
			else if (Error.check == 2) {
				Data PreError = pop(&Checked);
				cout << "양쪽 괄호 " << PreError.parenthesis << " 괄호와 " << Error.parenthesis << " 괄호 불일치 오류, 위치 : " << PreError.Point << ", " << Error.Point<<'\n';
			}
		}

		cout << '\n' << "괄호검사 실패";
	}

	else {

		printf("괄호검사성공\n");

	}



	return 0;

}