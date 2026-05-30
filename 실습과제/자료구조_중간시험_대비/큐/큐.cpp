#include<iostream>

using namespace std;

#define MAX_QUEUE_SIZE 5
typedef int element;

struct Queue
{
	element data[MAX_QUEUE_SIZE];
	int front, rear;
};

void Init(Queue* que)
{
	que->front = que->rear = 0;
}

int isfull(Queue* que)
{
	return ((que->rear + 1) % MAX_QUEUE_SIZE) == que->front;
}

int isEmpty(Queue* que)
{
	return que->front == que->rear;
}

void insertFrontQue(Queue* que)
{
	if (!isfull(que)) {
		cout << "값 입력 : ";
		element data;
		cin >> data;
		que->data[que->front] = data;
		que->front = (que->front - 1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
	}
	else {
		cout << "큐가 포화상태 입니다." << '\n';
	}
}

void insertRearQue(Queue* que)
{
	if (!isfull(que)) {
		cout << "값 입력 : ";
		element data;
		cin >> data;
		que->rear = (que->rear + 1) % MAX_QUEUE_SIZE;
		que->data[que->rear] = data;
	}
	else {
		cout << "큐가 포화상태 입니다." << '\n';
	}
}

element popFrontQue(Queue* que)
{
	if (!isEmpty(que)) {
		que->front = (que->front + 1) % MAX_QUEUE_SIZE;
		element data = que->data[que->front];
		cout << data << '\n';
		return data;
	}
	else {
		cout << "큐가 공백상태 입니다." << '\n';
	}
}

element popRearQue(Queue* que)
{
	if (!isEmpty(que)) {
		element data = que->data[que->rear];
		cout << data << '\n';
		que->rear = (que->rear - 1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
		return data;
	}
	else {
		cout << "큐가 공백상태 입니다." << '\n';
	}
}

int main()
{
	return 0;
}