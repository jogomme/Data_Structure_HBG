#include<iostream>
#include<limits>
#define _CRT_SECURE_NO_WARNINGS

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define INF 10000 /* 무한대 (연결이 없는 경우) */


#define PROB 3 // 각각의 문제를 구현하고 해당 문제 번호를 변경하여 테스트
#if PROB == 1
// 1번 문제를 해결하기 위한 프로그램 작성'

typedef struct GraphType {
	int n; // 정점의 개수
	int weight[MAX_VERTICES][MAX_VERTICES];
} GraphType;

int distance[MAX_VERTICES];/* 시작정점으로부터의 최단경로 거리 */

int found[MAX_VERTICES];	/* 방문한 정점 표시 */
int path[MAX_VERTICES];		/* 경유 노드 */

int choose(int distance[], int n, int found[])
{
	int i, min, minpos;
	min = INT_MAX;
	minpos = -1;
	for (i = 0; i < n; i++)
		if (distance[i] < min && !found[i]) {
			min = distance[i];
			minpos = i;
		}
	return minpos;
}

void print_status_g(GraphType* g, int n)
{
	std::cout << "STEP " << n << " - distance : " << '\t';
	for (int i = 0; i < g->n; ++i) {
		std::cout << distance[i] << "  ";
	}

	std::cout << '\n' << '\t';

	std::cout << "found : " << '\t';

	for (int i = 0; i < g->n; ++i) {
		std::cout << found[i] << "  ";
	}

	std::cout << '\n' << '\n';
}

void Print_Path_Array(GraphType* g)
{
	std::cout << "Print Path Array" << '\n';
	std::cout << "Index" << '\t' << ":  ";
	for (int i = 0; i < g->n; ++i) {
		std::cout << i << "  ";
	}
	std::cout << '\n' << "Path[i]" << '\t' << ": ";
	for (int i = 0; i < g->n; ++i) {
		std::cout << path[i] << "  ";
	}

	std::cout << '\n' << '\n';
}

void shortest_path(GraphType* g, int s)
{
	int i, u, w;

	for (int i = 0; i < g->n; ++i) {
		distance[i] = g->weight[s][i];
		found[i] = false;

		if (g->weight[s][i] != INF && i != s) {
			path[i] = s;
		}
		else {
			path[i] = -1;
		}
	}
	found[s] = true; 	/* 시작 정점 방문 표시 */
	distance[s] = 0;
	for (i = 0; i < g->n - 1; i++) {
		print_status_g(g, i + 1);
		u = choose(distance, g->n, found);
		found[u] = true;
		for (int w = 0; w < g->n; ++w) {
			if (!found[w]) {
				if (distance[u] + g->weight[u][w] < distance[w]) {
					distance[w] = distance[u] + g->weight[u][w];
					path[w] = u;
				}
			}
		}
	}

	Print_Path_Array(g);

}

void print_path(GraphType* g, int s, int e)
{
	int index = e;
	int* PrintArray = new int[g->n];
	int cnt{};

	while(true) {
		if (index == s || index == -1) {
			break;
		}
		PrintArray[cnt++] = index;
		index = path[index];
	}
	PrintArray[cnt++] = s;

	for (int i = cnt - 1; i > 0; --i) {
		if (distance[PrintArray[i - 1]] == INF) {
			std::cout << "연결되어 있지 않은 정점 입니다.  ";
		}
		else {
			std::cout << "( " << PrintArray[i] << "->" << PrintArray[i - 1] << " ) ";
		}
	}


	delete[] PrintArray;
}

void 매크로(GraphType* g, int start, int end)
{
	shortest_path(g, start);
	printf("\n정점 %d에서 정점 %d까지의 경로 : ", start, end);

	print_path(g, start, end); // 정점 start에서 정점 end으로 가는 최단경로 출력

	printf(" , 최단 거리 합 = %d \n", distance[end]);
	printf("\n");
}

int main(void)
{
	int start, end;
	std::cout << "--------------------------------------------------------------" << '\n';
	std::cout << "test data 1" << '\n';
	std::cout << "--------------------------------------------------------------" << '\n';
	GraphType g = { 7,
		{
			{ 0, 7, INF, INF, 3, 10, INF	},
			{ 7, 0, 4, 10, 2, 6, INF		},
			{ INF, 4, 0, 2, INF, INF, INF	},
			{ INF, 10, 2, 0, 11, 9, 4		},
			{ 3, 2, INF, 11, 0, INF, 5		},
			{ 10, 6, INF, 9, INF, 0, INF	},
			{ INF, INF, INF, 4,	5, INF, 0	}
		}
	};

	매크로(&g, 0 ,6);

	// 방향성 그래프에도 적용 가능
	std::cout << "--------------------------------------------------------------" << '\n';
	std::cout << "test data 2" << '\n';
	std::cout << "--------------------------------------------------------------" << '\n';
	g = {6,
	{{ 0, 50, 45, 10, INF, INF},
	{ INF, 0, 10, 15, INF, INF},
	{ INF, INF, 0, INF, 30, INF},
	{ 20, INF, INF, 0, 15, INF},
	{ INF, 20, 35, INF, 0, INF},
	{ INF, INF, INF, INF, 3, 0}}
	};
	
	매크로(&g, 0 ,5);
	std::cout << "--------------------------------------------------------------" << '\n';
	std::cout << "test data 3" << '\n';
	std::cout << "--------------------------------------------------------------" << '\n';
	g = { 7,
	{{ 0, 7, INF, 5,INF, INF, INF},
	{ 7, 0, 8, 9, 7, INF, INF},
	{ INF, 8, 0, INF, 5, INF, INF},
	{ 5, 9, INF, 0, 15, 6, INF },
	{ INF, 7, 5, 15, 0, 8, 9},
	{ INF, INF, INF, 6, 8, 0, 11 },
	{ INF, INF, INF, INF, 9, 11, 0 } }
	};

	매크로(&g, 0, 6);

	return 0;
}
#elif PROB == 2

typedef struct GraphType {
	int n; // 정점의 개수
	int weight[MAX_VERTICES][MAX_VERTICES];
} GraphType;

int A[MAX_VERTICES][MAX_VERTICES];
int path[MAX_VERTICES][MAX_VERTICES];

void printPathMap(GraphType* g)
{
	std::cout << "         ";
	for (int i = 0; i < g->n; ++i) {
		std::cout << "  " << i << " ";
	}
	std::cout << "\n==========================================\n";

	for (int i = 0; i < g->n; ++i) {
		std::cout << "  " << i << " |";
		for (int j = 0; j < g->n; ++j) {
			if (path[i][j] == -1) {
				std::cout << "  -1 ";
			}
			else {
				if (path[i][j] < 10 && path[i][j] >= 0) {
					std::cout << "   " << path[i][j] << " ";
				}
				else {
					std::cout << "  " << path[i][j] << " ";
				}
			}
		}
		std::cout << '\n';
	}
	std::cout << "==========================================\n";
}

void find_path(int p[MAX_VERTICES][MAX_VERTICES], int s, int e)
{
	if (p[s][e] != -1) {
		int k = p[s][e];

		if (k == s || k == e) return;

		find_path(p, s, k);
		std::cout << "->" << k;
		find_path(p, k, e);
	}
}

void print_path(GraphType* g, int p[MAX_VERTICES][MAX_VERTICES], int start, int end)
{
	std::cout << start;
	find_path(p, start, end);
	std::cout << "->" << end;
}

void printA(GraphType* g)
{
	std::cout << "         ";
	for (int i = 0; i < g->n; i++) {
		std::cout << "  " << i << " ";
	}
	std::cout << "\n==========================================\n";

	for (int i = 0; i < g->n; i++) {
		std::cout << "  " << i << " |";
		for (int j = 0; j < g->n; j++) {
			if (A[i][j] == INF) {
				std::cout << "   * ";
			}
			else {
				if (A[i][j] < 10) {
					std::cout << "   " << A[i][j] << " ";
				}
				else if (A[i][j] < 100) {
					std::cout << "  " << A[i][j] << " ";
				}
				else {
					std::cout << " " << A[i][j] << " ";
				}
			}
		}
		std::cout << '\n';
	}
	std::cout << "==========================================\n";
}

void floyd(GraphType* g)
{
	int i, j, k;

	for (i = 0; i < g->n; i++) {
		for (j = 0; j < g->n; j++) {
			A[i][j] = g->weight[i][j];
			path[i][j] = -1;
		}
	}

	printA(g);

	for (k = 0; k < g->n; k++) {
		for (i = 0; i < g->n; i++) {
			for (j = 0; j < g->n; j++) {
				if (A[i][k] + A[k][j] < A[i][j]) {
					A[i][j] = A[i][k] + A[k][j];
					path[i][j] = k;
				}
			}
		}
		std::cout << "\nk=" << k << '\n';
		printA(g);
	}
}

int main(void)
{
	int start, end;
	/*
	std::cout << "--------------------------------------------------------------" << '\n';
	std::cout << "test data 1" << '\n';
	std::cout << "--------------------------------------------------------------" << '\n';
	GraphType g = { 7,
		{
			{ 0, 7, INF, INF, 3, 10, INF    },
			{ 7, 0, 4, 10, 2, 6, INF        },
			{ INF, 4, 0, 2, INF, INF, INF   },
			{ INF, 10, 2, 0, 11, 9, 4       },
			{ 3, 2, INF, 11, 0, INF, 5      },
			{ 10, 6, INF, 9, INF, 0, INF    },
			{ INF, INF, INF, 4, 5, INF, 0   }
		}
	};
	*/
	// 방향성 그래프에도 적용 가능
	std::cout << "--------------------------------------------------------------" << '\n';
	std::cout << "test data 2" << '\n';
	std::cout << "--------------------------------------------------------------" << '\n';
	GraphType g = { 7,
{{ 0, 7, INF, 5,INF, INF, INF},
{ 7, 0, 8, 9, 7, INF, INF},
{ INF, 8, 0, INF, 5, INF, INF},
{ 5, 9, INF, 0, 15, 6, INF },
{ INF, 7, 5, 15, 0, 8, 9},
{ INF, INF, INF, 6, 8, 0, 11 },
{ INF, INF, INF, INF, 9, 11, 0 } }
	};

	/*
	std::cout << "--------------------------------------------------------------" << '\n';
	std::cout << "test data 3" << '\n';
	std::cout << "--------------------------------------------------------------" << '\n';
	g = { 7,
		{ { 0, 7, INF, 5, INF, INF, INF },
		  { 7, 0, 8, 9, 7, INF, INF },
		  { INF, 8, 0, INF, 5, INF, INF },
		  { 5, 9, INF, 0, 15, 6, INF },
		  { INF, 7, 5, 15, 0, 8, 9 },
		  { INF, INF, INF, 6, 8, 0, 11 },
		  { INF, INF, INF, INF, 9, 11, 0 } }
	};
	*/

	floyd(&g);
	printf("\n경로 맵\n");
	printPathMap(&g);
	start = 6; end = 1;
	printf("\n정점 %d에서 정점 %d까지의 경로 : ", start, end);
	print_path(&g, path, start, end); // 정점 start에서 정점 end으로 가는 최단경로 출력
	printf("\n");

	return 0;
}
#elif PROB == 3
// 3번 문제를 해결하기 위한 프로그램 작성
struct DATA
{
	int vertex;
};

struct STACK
{
	DATA* data;
	int top;
	int capacity;
};

void error(const char* c)
{
	std::cout << c << std::endl;
	exit(2025180028);
}

void Init(STACK* s, int capa)
{
	s->top = -1;
	s->capacity = capa;

	s->data = new DATA[capa];
}

int isFull(STACK* s)
{
	return (s->capacity - 1 == s->top);
}

int isEmpty(STACK* s)
{
	return (s->top == -1);
}

void push(STACK* s, DATA data)
{
	if (!isFull(s)) {
		s->top++;
		s->data[s->top] = data;
	}
	else {
		std::cout << "스택이 포화상태 입니다" << '\n';
	}
}

DATA peek(STACK* s)
{
	if (!isEmpty(s)) {
		return s->data[s->top];
	}

	error("스택에 데이터가 없습니다.");
}

DATA pop(STACK* s)
{
	if (!isEmpty(s)) {
		DATA tmp = s->data[s->top];
		s->top--;
		return tmp;
	}
	error("스택에 데이터가 없습니다.");
}



typedef struct GraphNode
{
	int vertex;
	struct GraphNode* link;
} GraphNode;

typedef struct GraphType {
	int n; // 정점의 개수
	GraphNode* adj_list[MAX_VERTICES];
} GraphType;

void graph_init(GraphType* g)
{
	g->n = 0;
	for (int i = 0; i < MAX_VERTICES; ++i) {
		g->adj_list[i] = nullptr;
	}
}

void set_vertex(GraphType* g, int num)
{
	g->n = num;
}

void insert_edge(GraphType* g, int s, int e)
{
	GraphNode* newNode{ new GraphNode };
	newNode->vertex = e;
	newNode->link = g->adj_list[s];
	g->adj_list[s] = newNode;
}

void topo_sort(GraphType* g)
{
	int in_degree[MAX_VERTICES] = { 0 };

	STACK s;
	Init(&s, g->n);

	for (int i = 0; i < g->n; ++i) {
		GraphNode* node = g->adj_list[i];
		while (node != nullptr) {
			in_degree[node->vertex]++;
			node = node->link;
		}
	}

	for (int i = 0; i < g->n; ++i) {
		if (in_degree[i] == 0) {
			DATA d;
			d.vertex = i;
			push(&s, d);
		}
	}

	while (!isEmpty(&s)) {
		DATA d = pop(&s);
		int w = d.vertex;

		std::cout << "정점 " << w << " ->  ";

		GraphNode* node = g->adj_list[w];
		while (node != nullptr) {
			int u = node->vertex;
			in_degree[u]--;

			if (in_degree[u] == 0) {
				DATA next_d;
				next_d.vertex = u;
				push(&s, next_d);
			}
			node = node->link;
		}
	}
	std::cout << '\n';

	delete[] s.data;
}

void delete_graph(GraphType* g)
{
	for (int i = 0; i < g->n; ++i) {
		GraphNode* curr = g->adj_list[i];
		while (curr != nullptr) {
			GraphNode* next = curr->link;
			delete curr;
			curr = next;
		}
	}
}

int main(void)
{
	GraphType g;
	graph_init(&g);
	// test data 1
	set_vertex(&g, 6);
	insert_edge(&g, 0, 2);
	insert_edge(&g, 0, 3);
	insert_edge(&g, 1, 3);
	insert_edge(&g, 1, 4);
	insert_edge(&g, 2, 3);
	insert_edge(&g, 2, 5);
	insert_edge(&g, 3, 5);
	insert_edge(&g, 4, 5);

	/*
	// test data 2
	set_vertex(&g, 8);
	insert_edge(&g, 0, 1);
	insert_edge(&g, 1, 2);
	insert_edge(&g, 1, 3);
	insert_edge(&g, 1, 4);
	insert_edge(&g, 2, 7);
	insert_edge(&g, 3, 6);
	insert_edge(&g, 4, 5);
	insert_edge(&g, 4, 6);
	insert_edge(&g, 5, 7);
	insert_edge(&g, 6, 7);
	*/
	//위상 정렬 
	topo_sort(&g);
	// 동적 메모리 반환 코드
	delete_graph(&g);
	return 0;
}
#endif