#include<iostream>

using namespace std;

typedef int element;

typedef struct QueueNode {
	element data;
	QueueNode* next;
} QueueNode;

typedef struct {
	int capacity;
	QueueNode* front, * rear;
} LinkedlistQueue;

void Init(LinkedlistQueue* Que)
{
	Que->capacity = 0;
	Que->front = Que->rear = nullptr;
}

int isFull(LinkedlistQueue* Que)
{

}

void insertFrontQue(LinkedlistQueue* Que, element data)
{
	QueueNode* NewNode = { new QueueNode };
	NewNode->data = data;
	NewNode->next = nullptr;

	if (Que->capacity == 0) {
		Que->front = Que->rear = NewNode;
		Que->capacity++;
	}
	else {
		NewNode->next = Que->front;
		Que->front = NewNode;
		Que->rear->next = Que->front;
		Que->capacity++;
	}
}

void inserRearQue(LinkedlistQueue* Que, element data)
{
	QueueNode* NewNode = { new QueueNode };
	NewNode->data = data;
	NewNode->next = nullptr;

	if (Que->capacity == 0) {
		Que->front = Que->rear = NewNode;
		Que->capacity++;
	}
	else {
		Que->rear->next = NewNode;
		Que->rear = NewNode;
		NewNode->next = Que->front;
		Que->capacity++;
	}
}

element DeQueFront(LinkedlistQueue* Que)
{
	if (Que->capacity == 0) return;

	element tmp = Que->front->data;
	QueueNode* DeleteNode = Que->front;

	Que->front = Que->front->next;
	Que->rear->next = Que->front;

	delete DeleteNode;
	return tmp;
}

element DeQueRear(LinkedlistQueue* Que)
{
	if (Que->capacity == 0) return;

	element tmp = Que->rear->data;
	QueueNode* DeleteNode = Que->rear;

	QueueNode* CurNode = Que->front;
	while (CurNode->next = Que->rear) {
		CurNode = CurNode->next;
	}

	Que->rear = CurNode;
	CurNode->next = Que->front;

	delete DeleteNode;

	return tmp;
}

int main()
{

}


