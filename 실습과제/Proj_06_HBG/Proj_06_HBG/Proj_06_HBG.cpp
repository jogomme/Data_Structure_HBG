#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include <unordered_map>
using namespace std;

#define MAX_QUEUE_SIZE 1000000

#define PROB 3 // 각각의 문제를 구현하고 해당 문제 번호를 변경하여 테스트



#if PROB == 1
// 1번 문제를 해결하기 위한 프로그램 작성

struct Data
{
	int N;
	int T;
};

struct Virous
{
	Data* data = new Data[MAX_QUEUE_SIZE];
	int front, rear;
	int cnt;
};

void error(const char* message)
{
	cout << message << '\n';
	exit(2025180028);
}

// 큐 초기화
void initQue(Virous* q)
{
	q->front = q->rear = 0;
	q->cnt = 0;
}

// 공백 검출
int isEmpty(Virous* q)
{
	// 같으면 1 다르면 0
	return (q->front == q->rear);
}

// 포화 검출
int isFull(Virous* q)
{
	// rear + 1을 MAXQUE로 나눈 나머지가 front랑 같으면 포화상태
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

// 삽입 함수
void enqueue(Virous* q, Data data)
{
	if (isFull(q)) {
		error("큐가 포화상태 입니다.");
	}
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = data;
	q->cnt++;
}

// 삭제 함수
Data dequeue(Virous* q)
{
	if (isEmpty(q))
	{
		error("큐가 공백상태 입니다.");
	}

	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	q->cnt--;
	return q->data[q->front];
}


int main()
{
	Virous v;
	bool* CheckList = new bool[MAX_QUEUE_SIZE]{ false };

	Data data{ 1, 0 };
	CheckList[data.N] = true;

	unsigned long long ListSize = MAX_QUEUE_SIZE;

	int num{};

	cout << "현재 바이러스 수 입력 : ";
	cin >> num;

	initQue(&v);

	enqueue(&v, data);

	while (!isEmpty(&v))
	{
		data = dequeue(&v);
		
		if (data.N == num) {
			cout << num << " 마리가 되는 데 필요한 시간 : " << data.T << '\n';
			break;
		}

		Data Nmul;
		Nmul.N = data.N * 2;
		Nmul.T = data.T + 1;

		if (Nmul.N < 0) {
			Nmul.N = 0;
		}


		if (Nmul.N >= ListSize) {
			
			bool* temp = new bool[Nmul.N + 1] {false};

			for (int i = 0; i < ListSize; ++i) {
				temp[i] = CheckList[i];
			}

			delete[] CheckList;

			CheckList = temp;

			ListSize = Nmul.N+1;
			CheckList[Nmul.N] = true;

			enqueue(&v, Nmul);

		}
		else if (CheckList[Nmul.N] == false) {
			CheckList[Nmul.N] = true;
			enqueue(&v, Nmul);

		}

		Data Ndiv;
		Ndiv.N = data.N / 3;
		Ndiv.T = data.T + 1;


		if (CheckList[Ndiv.N] == false) {
			CheckList[Ndiv.N] = true;
			enqueue(&v, Ndiv);

		}
		
	}

	delete[] CheckList;
	delete[] v.data;

}

#elif PROB == 2
// 2번 문제를 해결하기 위한 프로그램 작성


// 생각해보니까 받는 인자는 사람수인 n 밖에 없기에 삭제함
//struct Data
//{
//	int n;
//	int k;
//};

struct KillingGame
{
	int* data;
	int capacity;

	int front;
	int rear;
};

// 큐를 만들면 큐 초기화, 삽입, 삭제, 포화, Empty, 출력을 만든다

void error(const char* message)
{
	cout << message << '\n';
	exit(2025180028);
}

// 숫자를 입력받은 만큼 할 것이기 때문에 동적으로 할당하였다.
// 삽입
void initQueue(KillingGame* G, int Size)
{
	G->capacity = Size + 1;

	G->data = new int[Size + 1]{};

	G->front = 0;
	G->rear = Size;
	for (int i = 1; i <= Size; ++i) {
		G->data[i] = i;
	}

}

// 공백 확인
int isEmpty(KillingGame* G)
{
	return (G->front == G->rear);
}
// 포화 확인
int isFull(KillingGame* G)
{
	return ((G->rear + 1) % G->capacity == G->front);
}

 // 삽입
void EnQueue(KillingGame* G, int num)
{
	if (isFull(G)) {
		error("큐가 포화상태 입니다.");
	}
	
	G->rear = (G->rear + 1) % G->capacity;

	G->data[G->rear] = num;

}

int DelQueue(KillingGame* G)
{
	if (isEmpty(G))
	{
		error("큐가 공백상태 입니다.");
	}
	
	G->front = (G->front + 1) % G->capacity;
	return G->data[G->front];
}

int main()
{
	int n{}, k{};
	cout << "게임에 참여하는 사람 수 n과 선택하는 k 값 입력 : ";
	cin >> n >> k;

	KillingGame G;
	initQueue(&G, n);

	int suv{};

	while(!isEmpty(&G)){

		for (int i = 0; i < k-1; ++i) {
			int move = DelQueue(&G);
			EnQueue(&G, move);
		}

		suv = DelQueue(&G);

		cout << suv << " " << '\n';
	}

	cout << "최종 살아남은 사람은 " << suv << " 위치에 줄을 선 사람입니다." << '\n';

	delete[] G.data;

}

#elif PROB == 3
// 3번 문제를 해결하기 위한 프로그램 작성

struct Stack
{
	int top;
	int capacity;

	int* Data;
};

void error(const char* message)
{
	cout << message << '\n';
	exit(2025180028);
}

void initStack(Stack* s, int Size)
{
	s->top = -1;

	s->capacity = Size;

	s->Data = new int[Size];

}

int isEmptyStack(Stack* s)
{
	return (s->top == -1);
}

int isFullStack(Stack* s)
{
	return (s->top == s->capacity - 1);
}

void insertStack(Stack* s, int num)
{
	if (isFullStack(s)) {
		s->capacity = s->capacity * 2;

		int* newData = new int[s->capacity];

		for (int i = 0; i < s->top; ++i) {
			newData[i] = s->Data[i];
		}

		delete[] s->Data;

		s->Data = newData;

	}
	s->Data[++s->top] = num;

}

int pop(Stack* s)
{
	if (isEmptyStack(s)) {
		error("스택이 공백입니다");
	}

	return s->Data[(s->top)--];

}

int peekStack(Stack* s)
{
	if (isEmptyStack(s)) {
		error("스택이 공백입니다");
	}

	return s->Data[(s->top)];
}

void FreeStack(Stack* s)
{

	if (s->Data != nullptr) {

		delete[] s->Data;

		s->Data = nullptr;

		cout << "메모리가 해제되었습니다." << '\n';
	}

}

struct Queue
{
	int rear;
	int front;
	int capacity;

	int* Data;
};

void initQueue(Queue* q, int Size)
{

	q->front = q->rear = 0;

	q->capacity = Size + 1;

	q->Data = new int[q->capacity];


}

int isFullQueue(Queue* q)
{
	return ((q->rear + 1) % q->capacity == q->front);
}

int isEmptyQueue(Queue* q)
{
	return (q->rear == q->front);
}

void enQueue(Queue* q, int num)
{
	if (isFullQueue(q)) {
		error("큐가 포화상태 입니다.");
	}

	q->rear = (q->rear + 1) % q->capacity;

	q->Data[q->rear] = num;

}

int deQueue(Queue* q)
{
	if (isEmptyQueue(q)) {
		error("큐가 공백상태 입니다.");
	}

	q->front = (q->front + 1) % q->capacity;

	return q->Data[q->front];
}

int peekQue(Queue* q)
{
	if (isEmptyQueue(q)) {
		error("큐가 공백상태 입니다.");
	}

	int forpeek = (q->front + 1) % q->capacity;

	return q->Data[forpeek];

}

// q1 이 배열을 가지고 있는거, q2가 옮겨 담을 거
void Sort(Queue* q1, Queue* q2, Stack* s, int num[], int n)
{
	int i{};

	while (i < n){
		if (!isEmptyQueue(q1) && num[i] == peekQue(q1)) {
			enQueue(q2, deQueue(q1));
			++i;
		}
		else if (!isEmptyQueue(q1)&& num[i] > peekQue(q1)) {
			insertStack(s, deQueue(q1));
		}
		else if (num[i] < peekQue(q1)) {
			if (!isEmptyStack(s) && num[i] == peekStack(s)) {
				enQueue(q2, pop(s));
				++i;
			}
			else {
				error("생성 여부 : 불가능");
			}
		}
	}

	cout << "생성 여부 : 가능 " << '\n';

}


int main()
{
	int n = 10;
	int testNumberSquence[10] = { 1,2,3,4,5,6,7,8, 9 };
	
	Queue Q1;
	Queue Q2;

	initQueue(&Q1, n);
	initQueue(&Q2, n);

	for (int i = 1; i <= 10; ++i) {
		enQueue(&Q1, i);
	}

	Stack s;
	initStack(&s, n);

	// 코드 시작

	cout << "9개의 테스트 수열 : ";
	int num[9]{};
	for (int i = 0; i < 9; ++i) {
		cin >> num[i];
	}

	int Size = sizeof(num) / 4;

	Sort(&Q1, &Q2, &s, num, Size);

}

#endif