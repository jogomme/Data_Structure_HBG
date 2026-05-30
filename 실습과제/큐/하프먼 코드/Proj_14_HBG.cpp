#include<iostream>

using namespace std;

#define MAX_ELEMENT 100

struct TreeNode
{
	int weight;
	char ch{'\0'};
	TreeNode* left = nullptr;
	TreeNode* right = nullptr;
};

struct element
{
	int key;
	char ch{ '\0' };
	TreeNode* pTree;
};

struct HeapType
{
	element heap[MAX_ELEMENT];
	int heap_size{ 0 };
};

HeapType* creat()
{
	return new HeapType;
}

void insert_min_heap(HeapType* h, element item)
{
	int i{};
	i = ++(h->heap_size);

	// 트리를 거슬러 올라가면서 부모 노드와 비교하는 과정
	while ((i != 1) && (item.key < h->heap[i / 2].key)) {
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i] = item;
}

element delete_min_heap(HeapType* h)
{
	int parent, child;
	element item, temp;

	item = h->heap[1]; // root Node를 item에 저장함
	temp = h->heap[(h->heap_size)--]; // temp에 마지막에 저장된 element를 저장함
	
	parent = 1; // root Node
	child = 2; // root의 다음 노드

	// 현재 TreeNode에 root는 가장 '작은' 값이 있음
	// min heap이기 때문에

	while (child <= h->heap_size) { // child 가 힙의 사이즈보다 작으면 반복
		// 현재 노드의 자식노드중 더 작은 자식노드를 찾는다
		if ((child < h->heap_size) && (h->heap[child].key) > h->heap[child + 1].key) {
			// child가 heap의 사이즈보다 작고 child의 key가 child의 다음 키보다 크면 
			// child에 1 추가
			child++;
		}

		// 이 때 child는 heap의 가장 작은 값의 idx임

		// temp의 key가 child의 key보다 작으면 중단
		if (temp.key < h->heap[child].key) break;
		// 왜?
		// temp는 가장 마지막 값을 지님 하지만 저장할 때 1을 뺌
		// 가장 작은 값이 temp면 그 값대로 하면 되니까?

		// child가 가장 작은 값임으로 parent자리에 child를 넣음
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}

	h->heap[parent] = temp;
	return item;
}

TreeNode* makeTree(TreeNode* left, TreeNode* right)
{
	TreeNode* NewNode{ new TreeNode };
	NewNode->left = left;
	NewNode->right = right;
	return NewNode;
}

void destroy_Tree(TreeNode* root)
{
	if (root == NULL) return;
	destroy_Tree(root->left);
	destroy_Tree(root->right);
	delete root;
}

int is_leaf(TreeNode* root) 
{
	return !(root->left) && !(root->right);
}

void print_array(int codes[], int n)
{
	for (int i = 0; i < n; i++)
		printf("%d", codes[i]);
	printf("\n");
}

void print_codes(TreeNode* root, int codes[], int top)
{
	// 1을 저장하고 순환호출한다.
	if (root->left) {
		codes[top] = 1;
		print_codes(root->left, codes, top + 1);
	}
	// 0을 저장하고 순환호출한다.
	if (root->right) {
		codes[top] = 0;
		print_codes(root->right, codes, top + 1);
	}
	// 단말노드이면 코드를 출력한다.
	if (is_leaf(root)) {
		printf("%c: ", root->ch);
		print_array(codes, top);
	}
}

TreeNode* make_huffman_tree(int freq[], char ch_list[], int n)
{
	int i{};
	TreeNode* node;
	TreeNode* x;
	HeapType* heap;
	element e1, e2, e3;
	int codes[100];
	int top = 0;

	heap = creat();

	// size 가 0 으로 초기화가 자동으로 됨으로 초기화는 안해준다

	for (int i = 0; i < n; ++i) { // 모든 문자에 대한 min_heap 작성
		node = makeTree(nullptr, nullptr);
		e1.ch = node->ch = ch_list[i];
		e1.key = node->weight = freq[i];
		e1.pTree = node;
		insert_min_heap(heap, e1);
	}

	for (i = 1; i < n; ++i) { // 최소노드 두개를 삭제 후 합친 노드 1개 추가 n-1 번 반복
		// 최소값을 지닌 두 노드 삭제
		e2 = delete_min_heap(heap);
		e3 = delete_min_heap(heap);
		
		// 노드 2개 합치기
		x = makeTree(e2.pTree, e3.pTree);
		e1.key = x->weight = e2.key + e3.key;
		e1.pTree = x;
		printf("%d+%d->%d \n", e2.key, e3.key, e1.key);
		insert_min_heap(heap, e1);
	}
	e1 = delete_min_heap(heap); // 최종 트리
	print_codes(e1.pTree, codes, top);
	delete heap;
	return e1.pTree;
}

void print_code(TreeNode* head, int num)
{

}

void huffman_decode(TreeNode* head, const char* str)
{
	TreeNode* CurNode = head;

	cout << "Decode : " << str << '\n';

	char code[MAX_ELEMENT]{ '\0' };
	int code_idx = 0;
	
	int len = strlen(str);
	for (int i = 0; i < len; ++i) {

		int num = str[i] - '0';

		if (num == 1) {
			CurNode = CurNode->left;
			code[code_idx++] = '1';
		}

		if (num == 0) {
			CurNode = CurNode->right;
			code[code_idx++] = '0';
		}

		if (is_leaf(CurNode)) {
			code[code_idx] = '\0';
			cout << code << " ==> " << CurNode->ch << '\n';
			CurNode = head;
			code_idx = 0;
		}

	}

	if (CurNode != head) {
		code[code_idx] = '\0';
		cout <<code << " == > 입력문자열 모두 스캔 후 디코딩 미완성" << '\n';
	}
}

int main()
{
	char ch_list[] = { 's', 'i', 'n', 't', 'e' };
	int freq[] = { 4, 6, 8, 12, 15 };
	TreeNode* head;
	printf("허프만 코드를 위한 트래 생성\n");
	const char* str{ "1110101010000101" };
	head = make_huffman_tree(freq, ch_list, 5);
	printf("\n허프만 코드를 이용한 디코딩 :\n");
	huffman_decode(head, str);
	printf("\n허프만 코드를 이용한 디코딩 :\n");
	const char* str2{"11111111111"};
	huffman_decode(head, str2);
	destroy_Tree(head);
}