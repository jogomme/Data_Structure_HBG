#define _CRT_SECURE_NO_WARNINGS
#include<iostream>

using namespace std;

typedef struct ELEMENT {
	int id_num;
	char name[10];
}element;

typedef struct TreeNode {
	element std;
	struct TreeNode* left, * right, *pre;
} TreeNode;

TreeNode* insert_node(TreeNode* root, element item);

int get_node_count(TreeNode* root);

int get_leaf_count(TreeNode* root);

int get_height(TreeNode* root);

void PrintLevel(TreeNode* root, int level);

void level_order(TreeNode* root);

void inorder(TreeNode* root);

TreeNode* search(TreeNode* root, int studentNum);

TreeNode* delete_node(TreeNode* root, int studentNum);

TreeNode* delete_tree(TreeNode* root);

TreeNode* MinimumNode(TreeNode* root);

//---------------------------------------------------------------------
int main(void)
//---------------------------------------------------------------------
{
	TreeNode* root = nullptr;
	TreeNode* tmp = nullptr;
	element item;
	item.id_num = 2021006; strcpy(item.name, "name6");
	root = insert_node(root, item);
	item.id_num = 2021001; strcpy(item.name, "name1");
	root = insert_node(root, item);
	item.id_num = 2021009; strcpy(item.name, "name9");
	root = insert_node(root, item);
	item.id_num = 2021007; strcpy(item.name, "name7");
	root = insert_node(root, item);
	item.id_num = 2021003; strcpy(item.name, "name3");
	root = insert_node(root, item);
	item.id_num = 2021002; strcpy(item.name, "name2");
	root = insert_node(root, item);
	item.id_num = 2021005; strcpy(item.name, "name5");
	root = insert_node(root, item);
	item.id_num = 2021004; strcpy(item.name, "name4");
	root = insert_node(root, item);
	item.id_num = 2021008; strcpy(item.name, "name8");
	root = insert_node(root, item);
	item.id_num = 2021010; strcpy(item.name, "name10");
	root = insert_node(root, item);
	printf("이진 탐색 트리의 노드 수, leaf노드 수, 높이 구하기\n");
	printf("노드 수 = %d \nleaf 노드 수 = %d \n높이 = %d \n\n", 
		get_node_count(root), get_leaf_count(root), get_height(root));
	printf("이진 탐색 트리 레벨 탐색 순회 결과\n");
	level_order(root);
	printf("\n\n");
	printf("이진 탐색 트리 중위 순회 결과 \n");
	inorder(root);
	printf("\n\n이진 탐색 트리에서 2021010 검색\n");
	tmp = search(root, 2021010);
	if (tmp != nullptr)
		printf("검색 성공 : 학번 %d, 이름  %s \n", tmp->std.id_num, tmp->std.name);
	else
		printf("이진 탐색 트리에서 검색 학생을 발견못함 \n");
			
	printf("\n이진 탐색 트리에서 2021006 삭제\n");
	delete_node(root, 2021006);
	
	printf("\n\n이진 탐색 트리에서 2021006 검색\n");
	tmp = search(root, 2021006);
	if (tmp != nullptr)
		printf("검색 성공 : 학번 %d, 이름 % s \n", tmp->std.id_num, tmp->std.name);
	else
		printf("이진 탐색 트리에서 검색 학생을 발견못함 \n");
	
	printf("\n\n이진 탐색 트리 중위 순회 결과 \n");
	inorder(root);
	printf("\n\n");
	
	printf("\n\n이진 탐색 트리 전체 삭제 \n");
	root = delete_tree(root);
	
	printf("\n\n이진 탐색 트리 레벨 탐색 순회 결과\n");
	level_order(root);
	printf("\n\n");
}
// 메인 함수 여기서 끝남

TreeNode* delete_tree(TreeNode* root)
{
	if (root == nullptr) return nullptr;
	
	delete_tree(root->right);
	delete_tree(root->left);
	delete root;
	return nullptr;
}

TreeNode* delete_node(TreeNode* root, int studentNum)
{
	if (root == nullptr) return nullptr;

	if (root->std.id_num < studentNum) {
		root -> right = delete_node(root->right, studentNum);
	}
	else if (root->std.id_num > studentNum) {
		root->left= delete_node(root->left, studentNum);
	}
	else if (root->std.id_num == studentNum) {
		if (root->left == nullptr) {
			TreeNode* tmp = root->right;
			delete root;
			return tmp;
		}
		else if (root->right == nullptr) {
			TreeNode* tmp = root->left;
			delete root;
			return tmp;
		}

		TreeNode* tmp = MinimumNode(root->right);

		root->std = tmp->std;

		root->right = delete_node(root->right, tmp->std.id_num);

	}
	return root;
}

TreeNode* MinimumNode(TreeNode* root)
{
	TreeNode* CurNode = root;

	while (CurNode->left != nullptr) {
		CurNode = CurNode->left;
	}
	return CurNode;
}

TreeNode* search(TreeNode* root, int studentNum)
{
	if (root == nullptr) return nullptr;

	if (root->std.id_num == studentNum) return root;

	if (studentNum > root->std.id_num) {
		return search(root->right, studentNum);
	}
	else if (studentNum <= root->std.id_num) {
		return search(root->left, studentNum);
	}
}

void inorder(TreeNode* root)
{

	if (root != nullptr) {
		inorder(root->left);
		cout << "[" << root->std.id_num << "] ";
		inorder(root->right);
	}
}

void level_order(TreeNode* root)
{
	if (root == nullptr) {
		cout << "공백 트리입니다." << '\n';
		return;
	}

	TreeNode* CurNode = root;

	for (int i = 0; i < get_height(root); ++i)
	{
		cout << "LEVEL " << i + 1;
		PrintLevel(root, i);
		cout << '\n';
	}


}

void PrintLevel(TreeNode* root, int level)
{
	if (root == nullptr) return;

	if (level == 0) {
		if (root->pre == nullptr) {
			cout << "[" << root->std.id_num << "] ";
		}
		else {
			cout << "(" << root->pre->std.id_num << ")->[" << root->std.id_num << "] ";
		}
	}
	else {
		PrintLevel(root->left, level - 1);
		PrintLevel(root->right, level - 1);
	}

}

int get_height(TreeNode* root)
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

int get_leaf_count(TreeNode* root)
{
	int cnt{};

	if (root == nullptr) {
		return 0;
	}

	if (root->left == nullptr && root->right == nullptr) {
		return 1;
	}
	else {
		cnt += get_leaf_count(root->left) + get_leaf_count(root->right);
	}
	return cnt;
}

int get_node_count(TreeNode* root)
{
	int cnt = 0;

	if (root != nullptr) {
		if (root->left == nullptr && root->right == nullptr) {
			return 1;
		}
		else {
			cnt += 1 + get_node_count(root->left) + get_node_count(root->right);
		}
	}

	return cnt;
}

TreeNode* insert_node(TreeNode* root, element item)
{

	if (search(root, item.id_num) != nullptr) {
		return root;
	}

	TreeNode* NewNode{ new TreeNode };
	NewNode->left = nullptr;
	NewNode->right = nullptr;
	NewNode->pre = nullptr;
	NewNode->std = item;

	// 첫 노드 ( 뿌리 라면 )
	if (root == nullptr) {
		root = NewNode;
		return NewNode;
	}

	TreeNode* CurNode = root;

	while (true) {
		if (CurNode->std.id_num >= item.id_num) {

			if (CurNode->left != nullptr) {
				CurNode = CurNode->left;
			}
			else {
				NewNode->pre = CurNode;
				CurNode->left = NewNode;
				break;
			}
		}
		else if (CurNode->std.id_num < item.id_num) {

			if (CurNode->right != nullptr) {
				CurNode = CurNode->right;
			}
			else {
				NewNode->pre = CurNode;
				CurNode->right = NewNode;
				break;
			}
		}
	}

	return root;

}