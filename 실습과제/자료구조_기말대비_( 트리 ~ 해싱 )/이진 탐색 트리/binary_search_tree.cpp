#include<iostream>
#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
	int key;
	struct TreeNode* left, * right;
} TreeNode;

// 이진 탐색 트리
// 각 노드에 데이터를 저장하며 데이터의 키 값이 다음 조건 만족
// key(왼쪽서브트리)≤key(루트노드)≤key(오른쪽서브트리)
// 이진탐색를 '중위순회'하면 오름차순으로 정렬된 값을 얻을 수 있음

// 중위순회 - (LVR) 로 왼 중 오 순서로 순회하는 방법


// 이진 트리의 탐색
TreeNode* search(TreeNode* node, int key)
{
	// nullptr이면 탐색 실패
	if (node == nullptr) return nullptr;

	// 키 값이 같으면 탐색 성공
	if (key == node->key) return node; 
	
	// 키 값이 현재 노드의 값보다 작은 경우
	else if (key < node->key)
		// 왼쪽으로
		return search(node->left, key); 
	else
		// 크거나 같은 경우 왼쪽으로
		return search(node->right, key); 
}


// 이진 탐색 트리의 삽입
// 삽입하기 위해서는 먼저 '탐색'을 진행해야함
// 탐색에 '실패한 위치'가 바로 '새로운 노드를 삽입'하는 위치


TreeNode* insert_node(TreeNode* root, int key)
{
	// root가 nullptr이면 새로운 노드 반환
	if (root == nullptr) {
		TreeNode* newNode = new TreeNode;
		newNode->key = key;
		newNode->left = newNode->right = nullptr;
		return newNode;
	}

	// 그렇지 않으면 순환적으로 트리를 내려간다.
	if (key < root->key) {
		// 왼쪽 서브트리에 삽입
		root->left = insert_node(root->left, key);

	}
	else if (key > root->key) {
		// 오른쪽 서브트리에 삽입
		root->right = insert_node(root->right, key);
	}
	// 변경된 루트 노드 반환
	return root;
}

// 이진 탐색 트리의 삭제
// 삭제인 경우 case가 3가지로 나뉜다.

// case 1 : 삭제할 노드가 리프 노드인 경우
//			이 경우 이 노드의 부모 노드를 찾아서 부모 노드와 연결을 끊으면 된다.

// case 2 : 삭제할 노드가 하나의 서브 트리를 가지는 경우
//          이 경우 그 노드는 삭제하고 서브 트리는 삭제된 노드의 부모 노드에 붙여준다.

// case 3 : 삭제하려는 노드가 두 개의 서브 트리를 가지는 경우
//			삭제노드와 가장 비슷한 값을 지닌 노드를 삭제노드 위치로 가져온다
//          가장 비슷한 값을 지닌 노드 -> 왼쪽 1번 나머지 오른쪽 or 오른쪽 1번 나머지 왼쪽

// case 3에서 가장 비슷한 값을 지닌 노드를 찾는 방법 / 오른쪽 1번 나머지 왼쪽
TreeNode* min_value_node(TreeNode* node)
{
	TreeNode* current = node;
	// 맨 왼쪽 단말 노드를 찾으러 내려감
	while (current->left != NULL)
		current = current->left;
	return current;
}

// 삭제 함수
TreeNode* delete_node(TreeNode* root, int key)
{
	if (root == NULL) return root;

	// 만약 키가 루트보다 작으면 왼쪽 서브 트리에 있는 것임
	if (key < root->key)
		root->left = delete_node(root->left, key);
	// 만약 키가 루트보다 크면 오른쪽 서브 트리에 있는 것임
	else if (key > root->key)
		root->right = delete_node(root->right, key);
	else { // 키가 같으면 이 노드를 삭제하면 됌
		
		// case 1 or case 2 인 경우

		// Node의 오른쪽 노드만 있는 경우
		if (root->left == nullptr) {
			TreeNode* temp = root->right;
			delete root;
			return temp;
		}
		// Node의 왼쪽 노드만 있는 경우
		else if (root->right == nullptr) {
			TreeNode* temp = root->left;
			delete root;
			return temp;
		}

		// case 3
		TreeNode* temp = min_value_node(root->right); // 오른쪽 서브 트리에서 가장 작은 노드를 찾는다.

		// 중외 순회시 후계 노드를 복사한다. 
		root->key = temp->key;
		// 중외 순회시 후계 노드를 삭제한다. 
		root->right = delete_node(root->right, temp->key);

	}
	return root;
}

// 이진 탐색 트리에서의 탐색, 삽입, 삭제 연산의 시간 복잡도는 
// 트리의 높이를 h 라고 했을 때 h 에 비례한다

// 최선의 경우
// - 이진 트리가 균형 적으로  생성되어 있는 경우
// - h = log2(n)
// - 시간 복잡도 O(log n)

// 최악의 경우
// - 이진 트리가 한쪽으로 치우쳐서 생성되어 있는 경우
// - h = n
// - 시간 복잡도 O(n)


void inorder(TreeNode* root)
{
	if (root != nullptr) {
		inorder(root->left);
		printf("[%d] ", root->key);
		inorder(root->right);
	}
}

int main()
{
	TreeNode* root = NULL;
	TreeNode* tmp = NULL;
	root = insert_node(root, 30);
	root = insert_node(root, 20);
	root = insert_node(root, 10);
	root = insert_node(root, 40);
	root = insert_node(root, 50);
	root = insert_node(root, 60);
	printf("이진 탐색 트리 중위 순회 결과 \n");
	inorder(root);
	printf("\n\n");
	if (search(root, 30) != NULL)
		printf("이진 탐색 트리에서 30을 발견함 \n");
	else
		printf("이진 탐색 트리에서 30을 발견못함 \n");
	return 0;
}