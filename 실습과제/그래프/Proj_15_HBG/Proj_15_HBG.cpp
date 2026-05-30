#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

using namespace std;

#define MAX_VERTICES 50

#define PROB 2 // 각각의 문제를 구현하고 해당 문제 번호를 변경하여 테스트

struct Queue
{
	int data[MAX_VERTICES];
	int front;
	int rear;
};

void Init(Queue* que)
{
	que->front = que->rear = 0;
}

int isfull(Queue* que)
{
	return ((que->rear + 1) % MAX_VERTICES) == que->front;
}

int isEmpty(Queue* que)
{
	return que->front == que->rear;
}

void insertFrontQue(Queue* que, int n)
{
	if (!isfull(que)) {
		que->data[que->front] = n;
		que->front = (que->front - 1 + MAX_VERTICES) % MAX_VERTICES;
	}
	else {
		cout << "큐가 포화상태 입니다." << '\n';
	}
}


void insertRearQue(Queue* que)
{
	if (!isfull(que)) {
		cout << "값 입력 : ";
		int data;
		cin >> data;
		que->rear = (que->rear + 1) % MAX_VERTICES;
		que->data[que->rear] = data;
	}
	else {
		cout << "큐가 포화상태 입니다." << '\n';
	}
}

int popFrontQue(Queue* que)
{
	if (!isEmpty(que)) {
		que->front = (que->front + 1) % MAX_VERTICES;
		int data = que->data[que->front];
		return data;
	}
	else {
		cout << "큐가 공백상태 입니다." << '\n';
	}
}

int popRearQue(Queue* que)
{
	if (!isEmpty(que)) {
		int data = que->data[que->rear];
		que->rear = (que->rear - 1 + MAX_VERTICES) % MAX_VERTICES;
		return data;
	}
	else {
		cout << "큐가 공백상태 입니다." << '\n';
	}
}

// 인접 행렬로 푸는거
#if PROB == 1
// 1번 문제를 해결하기 위한 프로그램 작성

typedef struct GraphType {
	int n; // 정점의 개수
	int adj_mat[MAX_VERTICES][MAX_VERTICES];
	// n x n 행렬
} GraphType;

void init(GraphType* g)
{
	for (int i = 0; i < MAX_VERTICES; ++i) {
		for (int j = 0; j < MAX_VERTICES; ++j) {
			g->adj_mat[i][j] = 0;
		}
	}
}

void set_vertex(GraphType* g, int i)
{
	g->n = i;
}

void insert_edge(GraphType* g, int start, int end)
{
	if (start >= g->n || end >= g->n) {
		cout << "정점 설정 오류" << '\n';
		return;
	}

	g->adj_mat[start][end] = 1;
	g->adj_mat[end][start] = 1;
}

void printf_graph_matrix(GraphType* g)
{
	cout << '\t' << "|";
	for (int i = 0; i < g->n; ++i) {
		cout << i << '\t';
	}

	cout << '\n';

	for (int i = 0; i < g->n; ++i) {
		cout << "---------";
	}

	for (int i = 0; i < g->n; ++i) {
		cout <<'\n' << i << '\t' << "|";
		for (int j = 0; j < g->n; ++j) {
			cout << g->adj_mat[i][j] << '\t';
		}
	}
	cout << '\n';
}

void dfs_mat(GraphType* g, int n, int* visited)
{
	int w{};
	visited[n] = true;
	cout << "[ " << n << " ] -> ";

	for (w = 0; w < g->n; ++w) {
		if (g->adj_mat[n][w] && !visited[w]) {
			dfs_mat(g, w, visited);
		}
	}

}

void bfs_mat(GraphType* g, int n, int* visited)
{
	int w;
	Queue q;
	Init(&q); // 큐 초기화
	visited[n] = true; // 정점 v 방문 표시
	cout << "[ " << n << " ] -> ";
	insertFrontQue(&q, n);				// 시작 정점을 큐에 저장
	while (!isEmpty(&q)) {
		n = popRearQue(&q);			// 큐에 정점 추출
		for (w = 0; w < g->n; w++) {	// 인접 정점 탐색
			if (g->adj_mat[n][w] && !visited[w]) {
				visited[w] = true;		// 방문 표시
				cout << "[ " << w << " ] -> ";
				insertFrontQue(&q, w);	// 방문한 정점을 큐에 저장
			}
		}
	}
}


// 인접 행렬로 푸는거
int main(void)
{
	GraphType* g;
	int i;
	int visited[MAX_VERTICES];
	g = new GraphType;
	init(g);
	//그래프 초기화 및 간선 추가 : 에지 u, v가 입력되면 (u,v), (v,u)에 모두 간선 추가
	set_vertex(g, 11); // 정점의 개수 설정
	insert_edge(g, 0, 1);
	insert_edge(g, 0, 2);
	insert_edge(g, 0, 3);
	insert_edge(g, 1, 2);
	insert_edge(g, 1, 3);
	insert_edge(g, 2, 3);
	insert_edge(g, 2, 4);
	insert_edge(g, 4, 5);
	insert_edge(g, 4, 7);
	insert_edge(g, 4, 8);
	insert_edge(g, 5, 6);
	insert_edge(g, 6, 7);
	insert_edge(g, 6, 10);
	insert_edge(g, 7, 9);
	insert_edge(g, 7, 10);
	insert_edge(g, 8, 9);
	//print matrix of graph
	printf_graph_matrix(g);
	//깊이 우선 탐색
	for (i = 0; i < MAX_VERTICES; i++) visited[i] = 0;
	printf("깊이 우선 탐색\n");
	dfs_mat(g, 0, visited);
	printf("\n\n");
	//너비 우선 탐색
	for (i = 0; i < MAX_VERTICES; i++) visited[i] = 0;
	printf("너비 우선 탐색\n");
	bfs_mat(g, 0, visited);
	printf("\n");
	delete g;
	return 0;
}

#elif PROB == 2
// 2번 문제를 해결하기 위한 프로그램 작성

typedef struct GraphNode
{
	int vertex;
	struct GraphNode* link = nullptr;
} GraphNode;

typedef struct GraphType {
	int n; // 정점의 개수
	GraphNode* adj_list[MAX_VERTICES];
} GraphType;

void init(GraphType* g)
{
	g->n = 0;
	for (int i = 0; i < MAX_VERTICES; i++) {
		g->adj_list[i] = nullptr;
	}
}

void set_vertex(GraphType* g, int i)
{
	g->n = i;
}

void insert_edge(GraphType* g, int start, int end)
{
	if (g->n <= start || g->n <= end) {
		cout << "그래프 정점 오류" << '\n';
		return;
	}

	GraphNode* node = new GraphNode;
	node->vertex = end;
	node->link = g->adj_list[start];
	g->adj_list[start] = node;

	GraphNode* node2 = new GraphNode;
	node2->vertex = start;
	node2->link = g->adj_list[end];
	g->adj_list[end] = node2;

}

void dfs_list(GraphType* g, int v, int* visited)
{
	GraphNode* w;
	visited[v] = true;
	cout << "[ " << v << " ] -> ";
	for (w = g->adj_list[v]; w != nullptr; w = w->link) {
		if (!visited[w->vertex]) {
			dfs_list(g, w->vertex, visited);
		}
	}
}

void bfs_list(GraphType* g, int v, int* visited)
{
	GraphNode* w;
	Queue q;

	Init(&q);
	visited[v] = true;
	cout << "[ " << v << " ] -> ";

	insertFrontQue(&q, v);

	while (!isEmpty(&q)) {
		v = popRearQue(&q);
		for (w = g->adj_list[v]; w != nullptr; w = w->link) {
			if (!visited[w->vertex]) {
				visited[w->vertex] = true;
				cout << "[ " << w->vertex << " ] -> ";
				insertFrontQue(&q, w->vertex);
			}
		}
	}
}

void print_adj_list(GraphType* g)
{
	cout << "그래프 인접 리스트 " << '\n';
	for (int i = 0; i < g->n; ++i) {
		GraphNode* p = g->adj_list[i];
		cout << i << " : ";
		while (p != nullptr) {
			cout << p->vertex << " -> ";
			p = p->link;
		}
		if (p == nullptr) {
			cout << "nullptr";
		}
		cout << '\n';
	}
}

int main(void)
{
	GraphType* g;
	int i;
	int visited[MAX_VERTICES];
	g = new GraphType;
	init(g);
	//그래프 초기화 및 간선 추가, 에지 u, v가 입력되면 (u,v), (v,u)에 모두 간선 추가
	set_vertex(g, 11); //정점의 개수 설정
	insert_edge(g, 0, 1);
	insert_edge(g, 0, 2);
	insert_edge(g, 0, 3);
	insert_edge(g, 1, 2);
	insert_edge(g, 1, 3);
	insert_edge(g, 2, 3);
	insert_edge(g, 2, 4);
	insert_edge(g, 4, 5);
	insert_edge(g, 4, 7);
	insert_edge(g, 4, 8);
	insert_edge(g, 5, 6);
	insert_edge(g, 6, 7);
	insert_edge(g, 6, 10);
	insert_edge(g, 7, 9);
	insert_edge(g, 7, 10);
	insert_edge(g, 8, 9);
	// 그래프 출력
	print_adj_list(g);
	// 깊이 우선 탐색
	for (i = 0; i < MAX_VERTICES; i++) visited[i] = 0;
	printf("깊이 우선 탐색\n");
	dfs_list(g, 0, visited);
	printf("\n\n");
	// 너비 우선 탐색
	for (i = 0; i < MAX_VERTICES; i++) visited[i] = 0;
	printf("너비 우선 탐색\n");
	bfs_list(g, 0, visited);
	printf("\n");
	delete g;
	return 0;
}


#endif