#include<iostream>
#include<time.h>

using namespace std;

#define _CRT_SECURE_NO_WARNINGS
#define PROB 2 // 각각의 문제를 구현하고 해당 문제 번호를 변경하여 테스트
#if PROB == 1
// 1번 문제를 해결하기 위한 프로그램 작성

#define SIZE 1000000000 // 저장된 데이터의 갯수
#define DATA 802 // 찾는 키 값

// 순차탐색
int  seqsearch(int* list, int low, int high, int key, int* count)
{
	for (int i = low; i <= high; i++)
	{
		(*count)++;
		if (list[i] == key)
			return i;
	}
	return -1;
}

// 이진탐색
int  binsearch(int* list, int low, int high, int key, int* count)
{

	while (low <= high)
	{
		int mid{ (low + high) / 2 };

		(*count)++;
		if (list[mid] == key)
			return mid;
		else if (list[mid] < key)
			low = mid + 1;
		else
			high = mid - 1;
	}
	return -1;

}

// 보간탐색
int search_interpolation(int* list, int low, int high, int key, int* count)
{
	int j;
	while ((list[high] >= key) && (list[low] < key)) {

		(*count)++;

		j = ((float)(key - list[low]) / (list[high] - list[low]) * (high - low)) + low;

		if(key > list[j]){
			low = j + 1;
		}
		else if(key < list[j]){
			high = j - 1;
		}
		else low = j;

	}

	if (list[low] == key) {
		return low;
	}
	else return -1;
}

int main(void)
{
	int i, s_time, e_time, count{}, result;
	int* list = (int*)malloc(sizeof(int) * SIZE);
	if (list == NULL) { printf("메모리 할당 오류 \n"); exit(-1); }
	// 오름차순으로 정수 데이터 생성 및 저장
	list[0] = 0;
	for (i = 1; i < SIZE; i++)
		list[i] = list[i - 1] + (rand() % 3);
	printf("Data 크기 : %d, 검색 데이터 : %d \n", SIZE, DATA);
	printf("----------------------------------------------\n");
	s_time = clock();
	result = seqsearch(list, 0, SIZE - 1, DATA, &count); //순차탐색 호출 
	e_time = clock();
	if (result == -1) printf("검색 결과 : 검색 데이터 없음 \n");
	else printf("검색결과 : %d 위치에서 찾음 \n", result);
	printf("순차탐색 소요시간 %d, 비교횟수 : %d\n\n", e_time - s_time, count);

	count = 0;
	s_time = clock();
	result = binsearch(list, 0, SIZE - 1, DATA, &count); //이진탐색 호출 
	e_time = clock();
	if (result == -1) printf("검색 결과 : 검색 데이터 없음 \n");
	else printf("검색결과 : %d 위치에서 찾음 \n", result);
	printf("이진탐색 소요시간 %d, 비교횟수 : %d\n\n", e_time - s_time, count);
	
	count = 0;
	s_time = clock();
	result = search_interpolation(list, 0, SIZE - 1, DATA, &count);//보간탐색 호출 
	e_time = clock();
	if (result == -1) printf("검색 결과 : 검색 데이터 없음 \n");
	else printf("검색결과 : %d 위치에서 찾음 \n", result);
	printf("보간탐색 소요시간 %d, 비교횟수 : %d\n\n", e_time - s_time, count);
	free(list);
	return 0;
}


#elif PROB == 2
// 2번 문제를 해결하기 위한 프로그램 작성

// AVL 트리 노드 정의
typedef struct AVLNode
{
	int key;
	struct AVLNode* left;
	struct AVLNode* right;
} AVLNode;

int get_height(AVLNode* root)
{
	if (root == nullptr) {
		return 0;
	}

	int LeftHeight{};
	int RightHeight{};

	if (root->left != nullptr) {
		LeftHeight = get_height(root->left);
	}

	if (root->right != nullptr) {
		RightHeight = get_height(root->right);
	}

	if (RightHeight >= LeftHeight) {
		return RightHeight + 1;
	}
	else {
		return LeftHeight + 1;
	}

}

void PrintLevel(AVLNode* root,AVLNode* ParentNode, int level)
{
	if (root == nullptr) return;

	if (level == 0) {
		if (ParentNode == nullptr) {
			cout << "[" << root->key << "] ";
		}
		else {
			cout << "(" << ParentNode->key << ")->[" << root->key << "] ";
		}
	}
	else {
		PrintLevel(root->left, root,level - 1);
		PrintLevel(root->right, root,level - 1);
	}

}

void level_order(AVLNode* root)
{
	if (root == nullptr) {
		cout << "공백 노드입니다 " << '\n';
		return;
	}

	AVLNode* CurNode = root;

	for (int i = 0; i < get_height(root); i++) {
		PrintLevel(root, nullptr,i);
		cout << '\n';
	}

}

int GetBalance(AVLNode* root)
{
	if (root == nullptr) return 0;

	return get_height(root->left) - get_height(root->right);
}

AVLNode* rotate_right(AVLNode* parent) {
	AVLNode* child = parent->left;
	parent->left = child->right;
	child->right = parent;

	return child;
}

AVLNode* rotate_left(AVLNode* parent) {
	AVLNode* child = parent->right;
	parent->right = child->left;
	child->left = parent;

	return child;
}

AVLNode* AVL_insert(AVLNode* root, int key) 
{
	AVLNode* newNode{ new AVLNode };
	newNode->key = key;
	newNode->left = nullptr;
	newNode->right = nullptr;

	if(root == nullptr){
		return newNode;
	}

	AVLNode* CurNode = root;
	AVLNode* ParentNode = nullptr;

	AVLNode* dangerNode = root;
	AVLNode* dangerParent = nullptr;

	while (true) {

		if (GetBalance(CurNode) != 0) {
			dangerNode = CurNode;
			dangerParent = ParentNode;
		}

		if (key < CurNode->key) {
			if (CurNode->left == nullptr) {
				CurNode->left = newNode;
				break;
			}
			else {
				ParentNode = CurNode;
				CurNode = CurNode->left;
			}
		}
		else if (key > CurNode->key) {
			if (CurNode->right == nullptr) {
				CurNode->right = newNode;
				break;
			}
			else {
				ParentNode = CurNode;
				CurNode = CurNode->right;
			}
		}
		else {
			delete newNode;
			return root;
		}
	}

	AVLNode* temp = dangerNode;

	if (GetBalance(dangerNode) > 1) {
		if (key < dangerNode->left->key) {
			temp = rotate_right(dangerNode);
		}
		else {
			dangerNode->left = rotate_left(dangerNode->left);
			temp = rotate_right(dangerNode);
		}
	}
	else if (GetBalance(dangerNode) < -1) {
		if (key > dangerNode->right->key) {
			temp = rotate_left(dangerNode);
		}
		else {
			dangerNode->right = rotate_right(dangerNode->right);
			temp = rotate_left(dangerNode);
		}
	}

	if (dangerParent == nullptr) {
		root = temp;
	}
	else {
		if (dangerParent->left == dangerNode) {
			dangerParent->left = temp;
		}
		else {
			dangerParent->right = temp;
		}

	}

	return root;
}

AVLNode* MinimumNode(AVLNode* root)
{
	AVLNode* CurNode = root;

	while (CurNode->left != nullptr) {
		CurNode = CurNode->left;
	}
	return CurNode;
}

AVLNode* AVL_remove(AVLNode* root, int key)
{
	if (root == nullptr) return root;
	
	if(root->key <key){
		root->right = AVL_remove(root->right, key);
	}
	else if (root->key > key){
		root->left = AVL_remove(root->left, key);
	}
	else if(root->key == key){
		if (root->left == nullptr) {
			AVLNode* tmp = root->right;
			delete root;
			return tmp;
		}
		else if (root->right == nullptr) {
			AVLNode* tmp = root->left;
			delete root;
			return tmp;
		}

		AVLNode* tmp = MinimumNode(root->right);

		root->key = tmp->key;

		root->right = AVL_remove(root->right, tmp->key);
	}

	int balance = GetBalance(root);

	AVLNode* temp = root;

	if (balance > 1){
		int leftBalance = GetBalance(root->left);

		if (leftBalance >= 0) {
			temp = rotate_right(root);
		}
		else if (leftBalance < 0) {
			root->left = rotate_left(root->left);
			temp = rotate_right(root);
		}
	}
	else if (balance < -1) {
		int rightBalance = GetBalance(root->right);

		if (rightBalance <= 0) {
			temp = rotate_left(root);
		}
		else if (rightBalance > 0) {
			root->right = rotate_right(root->right);
			temp = rotate_left(root);
		}
	}


	return temp;

}

// 테스트를 위한 main 함수
int main(void)
{
	AVLNode* root = NULL;
	// 60 50 20 80 90 70 55 10 40 35
	// 예제 트리 구축
	printf("Insert %d\n", 60); 
	root = AVL_insert(root, 60);
	printf("Insert %d\n", 50); 
	root = AVL_insert(root, 50);
	printf("Insert %d\n", 20); 
	root = AVL_insert(root, 20);
	level_order(root);
	printf("Insert %d\n", 80); 
	root = AVL_insert(root, 80);
	level_order(root);
	printf("Insert %d\n", 90); 
	root = AVL_insert(root, 90);
	level_order(root);
	printf("Insert %d\n", 70); 
	root = AVL_insert(root, 70);
	level_order(root);
	printf("Insert %d\n", 55); 
	root = AVL_insert(root, 55);
	level_order(root);
	printf("Insert %d\n", 10); 
	root = AVL_insert(root, 10);
	level_order(root);
	printf("Insert %d\n", 40); 
	root = AVL_insert(root, 40);
	level_order(root);
	printf("Insert %d\n", 35); 
	root = AVL_insert(root, 35);
	level_order(root);
	printf("Remove %d\n", 50); 
	root = AVL_remove(root, 50);
	level_order(root);
	printf("Remove %d\n", 55); 
	root = AVL_remove(root, 55);
	level_order(root);
	return 0;
}
#endif