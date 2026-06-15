#include<iostream>
#include <stdio.h>  
#include <stdlib.h>

#define MAX_QUEUE_SIZE 100

typedef struct TreeNode {
	int data;
	struct TreeNode* left, * right;
} TreeNode;

typedef TreeNode* element;

typedef struct { // 큐 타입
	element data[MAX_QUEUE_SIZE];
	int front, rear;
} QueueType;

// 오류 함수
void error(const char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}
// 공백 상태 검출 함수
void init_queue(QueueType* q)
{
	q->front = q->rear = 0;
}
// 공백 상태 검출 함수
int is_empty(QueueType* q)
{
	return (q->front == q->rear);
}

// 포화 상태 검출 함수
int is_full(QueueType* q)
{
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}
// 삽입 함수
void enqueue(QueueType* q, element item)
{
	if (is_full(q))
		error("큐가 포화상태입니다");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = item;
}
// 삭제 함수
element dequeue(QueueType* q)
{
	if (is_empty(q))
		error("큐가 공백상태입니다");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->data[q->front];
}

// 리스트, 스택, 큐 등은 선형 구조이다.
// 트리는 계층적 구조를 나타내는 자료구조이다.

/*
 =========================================
 [트리 구조]
			 [ 60 ]
			/      \
	     [ 20 ]    [ 80 ]
		 /    \     /    \
	  [10]  [40]  [70]    [90]
	 /
  [35]
 =========================================
 */

// 트리는 Root 노드와 자식 노드로 이루어져 있다.
// 또한 서브트리는 트리의 부분집합으로 트리의 노드와 그 자손 노드로 이루어진다.



//레벨(level): 트리의 각층의 번호
//높이(height) : 트리의 최대 레벨 ( 4 )
//차수(degree) : 노드가 가지고 있는 자식 노드의 개수



// 이진 트리
// - 각 노드가 2개 이하의 서브트리를 가지는 트리
// - 서브트리는 공집합일수 있다



// 이진 트리의 성질
// - 노드의 개수가 n 이면 간선의 개수는 n - 1 이다.
// - 높이가 h인 이진 트리인 경우, 최소 h개의 노드를 가지며 최대 2^(h+1) - 1 개의 노드를 가진다.
// - n개의 노드를 가지는 이진 트리의 높이는 최소 log2(n+1) 이며 최대 n - 1 이다.



// 이진 트리의 분류
// 1. 포화 이진 트리
// 2. 완전 이진 트리
// 3. 기타 이진 트리



// 포화 이진 트리 vs 완전 이진 트리
// 포화 이진 트리 - 리프 노드를 제외한 모든 노드가 자식 노드를 2개 다 가지고 있는 이진 트리
// 완전 이진 트리 - 마지막 레벨을 제외한 모든 레벨이 완전히 채워져 있고, 
//					마지막 레벨의 노드가 왼쪽부터 채워져 있는 이진 트리


// 트리를 배열로 표현하는 방법
// 부모는 번호를 나누고 소숫점을 버리면 된다
// ex) 5 / 2 = 2
// 
// 자식은 부모의 번호를 x2 하고 오른쪽은
// 1을 더한다

// 트리를 포인터로 표현하는 방법
// 노드 구조체를 정의하여 각 노드가 자식 노드를 가리키도록 하는 방식이다.


// 이진트리 순회
// - 전위 순회 ( VLR )
//		자식 노드보다 루트노드를 먼저 방문한다. ( 루트 -> 왼쪽 -> 오른쪽 )
// - 중위 순회 ( LVR )
//		왼쪽 자손, 루트, 오른쪽 자손 순으로 방문한다. ( 왼쪽 -> 루트 -> 오른쪽 )
// - 후위 순회 ( LRV )
//		자식 노드보다 루트노드를 나중에 방문한다. ( 왼쪽 -> 오른쪽 -> 루트 )


// 포인터 이진 트리 재귀적 함수들
// 중위
void inorder_rec(TreeNode* root)
{
	if (root != nullptr) {
		inorder_rec(root->left);
		printf("[%d] ", root->data);
		inorder_rec(root->right);
	}
}

// 전위
void preorder_rec(TreeNode* root)
{
	if (root != nullptr) {
		printf("[%d] ", root->data);
		preorder_rec(root->left);
		preorder_rec(root->right);
	}
}

// 후위
void postorder_rec(TreeNode* root)
{
	if (root != nullptr) {
		postorder_rec(root->left);
		postorder_rec(root->right);
		printf("[%d] ", root->data);
	}
}

// 레벨 순회 
// - 큐를 이용하여 트리를 레벨 순회하는 방법이다.

void level_order(TreeNode* ptr)
{
	QueueType q;
	init_queue(&q); // 큐 초기화
	if (ptr == NULL) return;
	enqueue(&q, ptr);
	while (!is_empty(&q)) {
		ptr = dequeue(&q);
		printf(" [%d] ", ptr->data);
		if (ptr->left)
			enqueue(&q, ptr->left);
		if (ptr->right)
			enqueue(&q, ptr->right);
	}
}

// 트리의 높이 계산
// 트리의 높이는 루트 노드에서 가장 먼 리프 노드까지의 경로의 길이로 정의된다.
// 트리의 높이를 계산하는 함수는 다음과 같이 구현할 수 있다.

int get_height(TreeNode* root)
{
	int height = 0;

	if (root != nullptr) {
		int left_height = get_height(root->left); // 왼쪽 서브트리의 높이 계산
		int right_height = get_height(root->right); // 오른쪽 서브트리의 높이 계산
		height = std::max(left_height, right_height) + 1; // 현재 노드의 높이는 왼쪽과 오른쪽 서브트리의 높이 중 큰 값에 1을 더한 값
	}
	return height;
}

// 트리의 노드 개수 계산
// 트리의 노드 개수는 트리의 모든 노드를 방문하여 계산할 수 있다.
// 트리의 노드 개수를 계산하는 함수는 다음과 같이 구현할 수 있다.

int count_nodes(TreeNode* root)
{
	int count = 0;
	if (root != nullptr) {
		int left_count = count_nodes(root->left); // 왼쪽 서브트리의 노드 개수 계산
		int right_count = count_nodes(root->right); // 오른쪽 서브트리의 노드 개수 계산
		count = left_count + right_count + 1; // 현재 노드의 개수는 왼쪽과 오른쪽 서브트리의 노드 개수의 합에 1을 더한 값
	}
	return count;
}

// 트리의 리프 노드 개수 계산
// 트리의 리프 노드 개수는 트리의 모든 노드를 방문하여 계산할 수 있다.
// 트리의 리프 노드 개수를 계산하는 함수는 다음과 같이 구현할 수 있다.

int count_leaf_nodes(TreeNode* root)
{
	int count = 0;
	if (root != nullptr) {
		if (root->left == nullptr && root->right == nullptr) {
			count = 1; // 현재 노드가 리프 노드인 경우
		}
		else {
			int left_count = count_leaf_nodes(root->left); // 왼쪽 서브트리의 리프 노드 개수 계산
			int right_count = count_leaf_nodes(root->right); // 오른쪽 서브트리의 리프 노드 개수 계산
			count = left_count + right_count; // 현재 노드의 리프 노드 개수는 왼쪽과 오른쪽 서브트리의 리프 노드 개수의 합
		}
	}
	return count;
}

int main()
{
	return 0;
}