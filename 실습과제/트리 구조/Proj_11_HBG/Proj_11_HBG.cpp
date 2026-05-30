#include<iostream>

using namespace std;

// 포인터로 이진 트리 구성
typedef struct TreeNode {
	int data;
	struct TreeNode* left, * right;
} TreeNode;

// Full Binary Tree node number 1~15(root : 1)
TreeNode n15 = { 15, NULL, NULL };
TreeNode n14 = { 14, NULL, NULL };
TreeNode n13 = { 13, NULL, NULL };
TreeNode n12 = { 12, NULL, NULL };
TreeNode n11 = { 11, NULL, NULL };
TreeNode n10 = { 10, NULL, NULL };
TreeNode n9 = { 9, NULL, NULL };
TreeNode n8 = { 8, NULL, NULL };
TreeNode n7 = { 7, &n14, &n15 };
TreeNode n6 = { 6, &n12, &n13 };
TreeNode n5 = { 5, &n10, &n11 };
TreeNode n4 = { 4, &n8, &n9 };
TreeNode n3 = { 3, &n6, &n7 };
TreeNode n2 = { 2, &n4, &n5 };
TreeNode n1 = { 1, &n2, &n3 };
TreeNode* root = &n1;

// 배열로 이진트리 구성
typedef struct NODE 
{ 
	int data; 
	int leaf; 
} node; // leaf의 값이 1이면 child가 있음



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

// 포인터 이진 트리 반복적 함수들을 만들기 위한 스택 구현
struct TreeStackNode
{
	TreeNode* data;
	TreeStackNode* next = nullptr;
};

TreeStackNode* head = nullptr;

void push(TreeNode* root, int num = 0)
{
	TreeStackNode* newNode{ new TreeStackNode };
	newNode->data = root;
	newNode->next = nullptr;

	if (head == nullptr) {
		head = newNode;
	}
	else {
		newNode->next = head;
		head = newNode;
	}
	

}

TreeNode* pop()
{
	TreeNode* p = nullptr;
	if (head != nullptr) {
		p = head->data;
		TreeStackNode* tmp = head;
		head = head->next;
		delete tmp;
	}
	return p;

}

TreeNode* peek()
{
	if (head != nullptr) {
		return head->data;
	}
	return nullptr;
}

// 포인터 이진 트리 반복적 함수들

//								   [ 1 ]
//                             /         \
//                 /---------/             \---------\
//             [ 2 ]                               [ 3 ]
//           /       \                           /       \
//       [ 4 ]       [ 5 ]                   [ 6 ]       [ 7 ]
//      /     \     /     \                 /     \     /     \
//    [8]     [9] [10]   [11]             [12]   [13] [14]   [15]

//중위
void inorder_iter(TreeNode* root)
{
	while (true) {
		while (root != nullptr) {
			push(root);
			root = root->left;
		}
		root = pop();
		if (!root) break;
		printf("[%d] ", root->data);
		root = root->right;
	}
}

// 전위
void preorder_iter(TreeNode* root)
{
	while (true) {
		for (; root; root = root->left) {
			printf("[%d] ", root->data);
			push(root);
		}
		root = pop();
		if (!root) break;
		root = root->right;
	}
}

// 후위 * 얘는 다시 공부하기 *
void postorder_iter(TreeNode* root)
{
	TreeNode* curr = root;           // 현재 내 위치
	TreeNode* lastVisited = nullptr; // 방금 도장 찍고 온(출력한) 녀석의 기억

	while (curr != nullptr || head != nullptr) {

		// 1단계: 일단 왼쪽으로 묻지도 따지지도 않고 끝까지 파고듭니다!
		if (curr != nullptr) {
			push(curr);
			curr = curr->left;
		}
		// 2단계: 더 이상 갈 왼쪽이 없으면 스택 맨 위를 "살짝 쳐다만 봅니다." (pop 금지!)
		else {
			TreeNode* peekNode = peek();

			// 3단계: 오른쪽 길이 있고 && 아직 오른쪽을 다녀오지 않았다면? -> 오른쪽으로 꺾어!
			if (peekNode->right != nullptr && lastVisited != peekNode->right) {
				curr = peekNode->right;
			}
			// 4단계: 오른쪽 길이 없거나 || 이미 오른쪽을 다녀왔다면? -> 드디어 내 차례!
			else {
				printf("[%d] ", peekNode->data); // 도장 쾅!
				lastVisited = pop();             // 스택에서 진짜로 빼고, 방금 다녀왔다고 기억함
			}
		}
	}
}


// 배열 이진 트리
node arr[] = { {0,0}, {1,1}, {2,1}, {3,1}, {4,1}, {5,1}, {6,1}, {7,1}, {8,0}, {9,0}, {10,0}, {11,0},
{12,0}, {13,0}, {14,0}, {15,0} };

// 배열 이진 트리 함수들
// 중위
void inorder_rec_arr(node* arr,int idx)
{
	if (idx > 15) return;

	if (arr[idx].leaf == 1) {
		inorder_rec_arr(arr, idx * 2);
	}
	printf("[%d] ", arr[idx].data);
	if (arr[idx].leaf == 1) {
		inorder_rec_arr(arr, idx * 2 + 1);
	}
}

// 전위
void preorder_rec_arr(node* arr, int idx)
{
	if (idx > 15) return;

	printf("[%d] ", arr[idx].data);
	if (arr[idx].leaf == 1) {
		preorder_rec_arr(arr, idx * 2);
		preorder_rec_arr(arr, idx * 2 + 1);
	}
}

// 후위
void postorder_rec_arr(node* arr, int idx)
{
	if (idx > 15) return;

	if (arr[idx].leaf == 1) {
		postorder_rec_arr(arr, idx * 2);
		postorder_rec_arr(arr, idx * 2 + 1);
	}
	printf("[%d] ", arr[idx].data);
}

int main(void)
{
	printf("중위 순회(rec)	= ");
	inorder_rec(root);
	printf("\n");

	printf("중위 순회(itr)  = ");
	inorder_iter(root);
	printf("\n");

	printf("배열 중위 순회(rec)  = ");
	inorder_rec_arr(arr, 1);
	printf("\n\n");
	


	printf("전위 순회(rec)	= "); 
	preorder_rec(root);
	printf("\n");
	
	printf("전위 순회(itr)  = ");
	preorder_iter(root);
	printf("\n");
	
	printf("배열 전위 순회(rec)=");
	preorder_rec_arr(arr, 1);
	printf("\n\n");


	
	printf("후위 순회(rec) 	= "); 
	postorder_rec(root);
	printf("\n");
	
	printf("후위 순회(itr)  = ");
	postorder_iter(root);
	printf("\n");
	
	printf("배열 후위 순회(rec)=");
	postorder_rec_arr(arr, 1);
	printf("\n\n");

}