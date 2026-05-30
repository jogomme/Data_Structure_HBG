#define _CRT_SECURE_NO_WARNINGS

#include<iostream>


#define PROB 2 // 각각의 문제를 구현하고 해당 문제 번호를 변경하여 테스트


#if PROB == 1
// 1번 문제를 해결하기 위한 프로그램 작성

//is_empty(), is_full(), push(), pop(), peek(), print_stack()

typedef struct WORLD_COORDINATE {
	int x;
	int y;
	int z;
} element;

typedef struct STACKNODE {

	element data;
	struct STACKNODE* link;

} StackNode;

void error(const char* c) 
{
	std::cout << c << "가 발생하였습니다.";
	exit(2025180028);
}

int is_empty(STACKNODE* head)
{
	return (head == nullptr);
}

int is_full()
{
	STACKNODE* temp{ new STACKNODE };

	if (temp == nullptr) {
		error("스택 포화");
	}
	else {
		delete temp;
		return 0;
	}
}

STACKNODE*  push(STACKNODE** head, element data)
{
	is_full();

	STACKNODE* newNode{ new STACKNODE };

	newNode->data = data;

	newNode->link = nullptr;

	if ((*head) == nullptr) {
		(*head) = newNode;
		return newNode;
	}
	else {
		newNode->link = (*head);
		(*head) = newNode;
	}
}

element pop(STACKNODE** head)
{
	if (is_empty(*head)) {
		return { INT_MIN, INT_MIN, INT_MIN };
	}
	else {
		STACKNODE* tmp = *head;
		element tmp2 = (*head)->data;
		*head = (*head)->link;
		
		delete tmp;
		return tmp2;
	}
}

element peek(STACKNODE* head)
{
	if (is_empty(head)) {
		return { INT_MIN, INT_MIN, INT_MIN };
	}
	else {
		return head->data;
	}
}

void  print_stack(STACKNODE* head)
{
	std::cout << "======= 스택내용 =======" << '\n';
	if (is_empty(head)) {
		std::cout << "(   NULL   ) < --- Top " << '\n' ;
	}
	else {
		STACKNODE* CurNode = head;

		int count{};

		while (CurNode != nullptr) {
			if (count == 0) {
				std::cout << "( " << CurNode->data.x << ", " << CurNode->data.y << ", "<<  CurNode->data.z << " ) <--- Top" << '\n';
			}
			else {
				std::cout << "( " << CurNode->data.x << ", " << CurNode->data.y << ", " << CurNode->data.z << " )" << '\n';
			}
			CurNode = CurNode->link;
			++count;
		}

	}
	std::cout << "========================" << '\n' << '\n';
}

//--------------------------------------------------------------------------
int main()
//--------------------------------------------------------------------------
{
	STACKNODE* head = nullptr;

	element item{};

	print_stack(head);
	item.x = 1; item.y = 1; item.z = 1;
	printf("Push item\n");
	push(&head, item); print_stack(head);
	item.x = 2; item.y = 2; item.z = 2;
	printf("Push item\n");
	push(&head, item); print_stack(head);
	item.x = 3; item.y = 3; item.z = 3;
	printf("Push item\n");
	push(&head, item); print_stack(head);
	item.x = 4; item.y = 4; item.z = 4;
	printf("Push item\n");
	push(&head, item); print_stack(head);
	printf("PoP item\n");
	item = pop(&head);
	printf("PoP된 data : (%d, %d, %d) \n", item.x, item.y, item.z);
	print_stack(head);
	printf("PoP item\n");
	item = pop(&head);
	printf("PoP된 data : (%d, %d, %d) \n", item.x, item.y, item.z);
	print_stack(head);
	printf("PoP item\n");
	item = pop(&head);
	printf("PoP된 data : (%d, %d, %d) \n", item.x, item.y, item.z);
	print_stack(head);
	printf("PoP item\n");
	item = pop(&head);
	printf("PoP된 data : (%d, %d, %d) \n", item.x, item.y, item.z);
	print_stack(head);
	printf("PoP item\n");
	item = pop(&head);
	printf("PoP data : (%d, %d, %d) \n", item.x, item.y, item.z);
	print_stack(head);
	printf("PoP item\n");
	item = pop(&head);
	printf("PoP된 data : (%d, %d, %d) \n", item.x, item.y, item.z);
	print_stack(head);
}

#elif PROB == 2
// 2번 문제를 해결하기 위한 프로그램 작성
//is_empty(), is_full(), enqueue(), dequeue(), print_queue()

typedef struct WORLD_COORDINATE {
	int x;
	int y;
	int z;
}element;

typedef struct QueueNode {
	element data;
	struct QueueNode* next;
} QueueNode;

typedef struct {
	QueueNode* front, * rear;
} LinkedlistQueue;

void error(const char* c)
{
	std::cout << c << "가 발생하였습니다.";
	exit(2025180028);
}

void init(LinkedlistQueue* queue)
{
	queue->front = nullptr;
	queue->rear =  nullptr;
}

int is_empty(LinkedlistQueue* queue) 
{
	return queue->front == nullptr;
}

int is_full()
{
	QueueNode* temp{ new QueueNode };

	if (temp == nullptr) {
		error("스택 포화");
	}
	else {
		delete temp;
		return 0;
	}

}

void enqueue(LinkedlistQueue* que, element data)
{
	QueueNode* newNode{ new QueueNode };

	newNode->data = data;
	newNode->next = nullptr;

	if (que->front == nullptr) {
		que->front = newNode;
		que->rear = newNode;
	}
	else {
		que->rear->next = newNode;
		que->rear = newNode;
	}
}

element dequeue(LinkedlistQueue* que)
{
	if (is_empty(que)) {
		return { INT_MIN, INT_MIN, INT_MIN };
	}
	else {
		QueueNode* temp = que->front;
		element tmp = temp->data;

		que->front = que->front->next;

		if (que->front == nullptr) {
			que->rear = nullptr;
		}
		
		delete temp;

		return tmp;

	}
}

void print_queue(LinkedlistQueue* que)
{
	std::cout << "======= 큐 내용 =======" << '\n';
	if (is_empty(que)) {
		std::cout << "(   NULL   ) < --- Front, Rear " << '\n';
	}
	else {
		QueueNode* CurNode = que->front;

		int count{};

		while (CurNode != nullptr) {
			if (que->front == que->rear) {
				std::cout << "( " << CurNode->data.x << ", " << CurNode->data.y << ", " << CurNode->data.z << " ) <--- Front, Rear" << '\n';
			}
			else if (count == 0) {
				std::cout << "( " << CurNode->data.x << ", " << CurNode->data.y << ", " << CurNode->data.z << " ) <--- Front" << '\n';

			}
			else if (CurNode == que->rear)
			{
				std::cout << "( " << CurNode->data.x << ", " << CurNode->data.y << ", " << CurNode->data.z << " ) <--- Rear" << '\n';
			}
			else {
				std::cout << "( " << CurNode->data.x << ", " << CurNode->data.y << ", " << CurNode->data.z << " )" << '\n';
			}
			CurNode = CurNode->next;
			++count;
		}

	}
	std::cout << "========================" << '\n' << '\n';
}

//--------------------------------------------------------------------------
int main()
//--------------------------------------------------------------------------
{
	LinkedlistQueue queue;

	element item;

	init(&queue);
	print_queue(&queue);
	// 큐 초기화
	printf("enqueue item \n");
	item.x = 1, item.y = 1, item.z = 1;
	enqueue(&queue, item); print_queue(&queue);
	printf("enqueue item \n");
	item.x = 2, item.y = 2, item.z = 2;
	enqueue(&queue, item); print_queue(&queue);
	printf("enqueue item \n");
	item.x = 3, item.y = 3, item.z = 3;
	enqueue(&queue, item); print_queue(&queue);
	printf("enqueue item \n");
	item.x = 4, item.y = 4, item.z = 4;
	enqueue(&queue, item); print_queue(&queue);
	printf("enqueue item \n");
	item.x = 5, item.y = 5, item.z = 5;
	enqueue(&queue, item); print_queue(&queue);
	printf("dequeue item\n");
	item = dequeue(&queue);
	printf("Dequeue된 data : (%d, %d, %d) \n", item.x, item.y, item.z);
	print_queue(&queue);
	printf("dequeue item\n");
	item = dequeue(&queue);
	printf("Dequeue된 data : (%d, %d, %d) \n", item.x, item.y, item.z);
	print_queue(&queue);
	printf("dequeue item\n");
	item = dequeue(&queue);
	printf("Dequeue된 data : (%d, %d, %d) \n", item.x, item.y, item.z);
	print_queue(&queue);
	printf("dequeue item\n");
	item = dequeue(&queue);
	printf("Dequeue된 data : (%d, %d, %d) \n", item.x, item.y, item.z);
	print_queue(&queue);
	printf("dequeue item\n");
	item = dequeue(&queue);
	printf("Dequeue된 data : (%d, %d, %d) \n", item.x, item.y, item.z);
	print_queue(&queue);
	printf("dequeue item\n");
	item = dequeue(&queue);
	printf("Dequeue된 data : (%d, %d, %d) \n", item.x, item.y, item.z);
	print_queue(&queue);
}

#endif