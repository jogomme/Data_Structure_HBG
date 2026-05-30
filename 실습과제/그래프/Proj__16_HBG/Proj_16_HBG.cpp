#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

using namespace std;

#define MAX_VERTICES 100
#define INF 1000

#define PROB 2 // 각각의 문제를 구현하고 해당 문제 번호를 변경하여 테스트

#if PROB == 1
// 1번 문제를 해결하기 위한 프로그램 작성

struct Edge {
	int start, end, weight;
};// 간선을 나타내는 구조체


typedef struct GraphType {
	int en; // 간선의 개수
	int vn; // 정점의 개수
	struct Edge edges[2 * MAX_VERTICES];
} GraphType;

int Parent[MAX_VERTICES];

void graph_init(GraphType* g)
{
	g->en = 0;
	g->vn = 0;
	for (int i = 0; i < 2 * MAX_VERTICES; i++) {
		g->edges[i].start = 0;
		g->edges[i].end = 0;
		g->edges[i].weight = INF;
	}
}

void set_nodes(GraphType* g, int node)
{
	g->vn = node;
	for (int i = 0; i < node; ++i) {
		Parent[i] = -1;
	}
}

void insert_edge(GraphType* g, int start, int end, int dist)
{
	if (g->vn <= start || g->vn <= end) {
		cout << "정점 오류" << '\n';
		return;
	}

	g->edges[g->en].start = start;
	g->edges[g->en].end = end;
	g->edges[g->en++].weight = dist;

}

int compare(const void* a, const void* b)
{
	struct Edge* x = (struct Edge*)a;
	struct Edge* y = (struct Edge*)b;
	return (x->weight - y->weight);
}

int set_find(int v)
{
	if (Parent[v] == -1)
		return v; 
	while (Parent[v] != -1) {
		v = Parent[v];
	}
	return v;
}

void set_union(int a, int b)
{
	// 루트
	int root1 = set_find(a); // 노드 a의 루트를 찾는다. 
	int root2 = set_find(b);
	if (root1 != root2) { // 노드 b의 루트를 찾는다. 
		Parent[root1] = root2;	// 합한다.
	}
}

void kruskal(GraphType* g)
{
	int ConnectEdge = 0;
	int uset, vset;
	int sum{};
	Edge e;

	qsort(g->edges, g->en, sizeof(struct Edge), compare);
	printf("크루스칼 최소 신장 트리 알고리즘 \n");
	int i = 0;
	// 집합 초기화
	while (ConnectEdge < (g->vn - 1)) {
		e = g->edges[i];
		uset = set_find(e.start); // 간선의 수 < (n-1)
		// 정점 u의 집합 번호
		vset = set_find(e.end); if (uset != vset) { // 정점 v의 집합 번호
			// 서로 속한 집합이 다르면
			printf("간선 (%d,%d) %d 선택\n", e.start, e.end, e.weight);
			ConnectEdge++;
			set_union(uset, vset); // 두개의 집합을 합친다.
			sum += e.weight;
		}
		i++;
	}
	cout << "최소 비용 : " << sum << '\n';

}

int main(void)
{
	GraphType* g;
	g = new GraphType;
	graph_init(g);
	// test data 1 
	set_nodes(g, 7);
	insert_edge(g, 0, 1, 29);
	insert_edge(g, 1, 2, 16);
	insert_edge(g, 2, 3, 12);
	insert_edge(g, 3, 4, 22);
	insert_edge(g, 4, 5, 27);
	insert_edge(g, 5, 0, 10);
	insert_edge(g, 6, 1, 15);
	insert_edge(g, 6, 3, 18);
	insert_edge(g, 6, 4, 25);
	kruskal(g);

	cout << '\n' << '\n';

	// test data 2
	set_nodes(g, 8);
	insert_edge(g, 0, 1, 10);
	insert_edge(g, 0, 3, 6);
	insert_edge(g, 0, 7, 1);
	insert_edge(g, 1, 2, 4);
	insert_edge(g, 1, 5, 2);
	insert_edge(g, 2, 3, 11);
	insert_edge(g, 2, 5, 7);
	insert_edge(g, 3, 7, 3);
	insert_edge(g, 4, 5, 5);
	insert_edge(g, 4, 7, 8);
	insert_edge(g, 5, 6, 9);
	insert_edge(g, 6, 7, 12);
	kruskal(g);

	delete g;
	return 0;
}

#elif PROB == 2
// 2번 문제를 해결하기 위한 프로그램 작성

typedef struct GraphType {

	int n; // 정점의 개수
	int weight[MAX_VERTICES][MAX_VERTICES];

} GraphType;

int selected[MAX_VERTICES];
int dist[MAX_VERTICES];

struct element
{
	int key;
	int u; // 시작 정점
	int v; // 도착 정점
};

struct HeapType
{
	element heap[MAX_VERTICES];
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

void prim(GraphType* g, int start)
{
	int i, u, v;

	int visited[MAX_VERTICES] = { 0 };
	int connect_edge = 0;

	HeapType* h = creat();

	for (u = 0; u < g->n; ++u) {
		dist[u] = INF; 
		selected[u] = false;
	}

	dist[start] = 0;
	selected[start] = true;

	element e; 
	for (int i = 0; i < g->n; ++i) {
		if (g->weight[start][i] != 0 && g->weight[start][i] != INF) {
			e.key = g->weight[start][i];
			e.u = start;
			e.v = i;
			insert_min_heap(h, e);
		}
	}

	cout << "시작 정점 " << e.u << "추가 " << '\n';

	while (connect_edge < g->n - 1) {

		if (h->heap_size == 0) {
			break;
		}

		element min_e = delete_min_heap(h);

		if (selected[min_e.v]) continue;

		selected[min_e.v] = true;
		connect_edge++;

		cout << "정점 " << min_e.v << "추가, 간선 ( " << min_e.u << ", " << min_e.v
			<< " ), distance : " << min_e.key << '\n';

		for (int w = 0; w < g->n; w++) {
			if (g->weight[min_e.v][w] != 0 && g->weight[min_e.v][w] != INF && !selected[w]) {
				element new_e;
				new_e.key = g->weight[min_e.v][w];
				new_e.u = min_e.v; // 새로운 출발지는 방금 정복한 땅
				new_e.v = w;       // 도착지는 미개척지
				insert_min_heap(h, new_e);
			}
		}

	}

	delete h;

}

int main(void)
{
	int i;

	element* list;

	cout << "test data1" << '\n';
	//test data1
	GraphType g = { 7,
	{
		{ 0, 29, INF, INF, INF, 10, INF },
		{ 29, 0, 16, INF, INF, INF, 15 },
		{ INF, 16, 0, 12, INF, INF, INF },
		{ INF, INF, 12, 0, 22, INF, 18 },
		{ INF, INF, INF, 22, 0, 27, 25 },
		{ 10, INF, INF, INF, 27, 0, INF },
		{ INF, 15, INF, 18, 25, INF, 0 } }
	};
	prim(&g, 0);

	 cout << '\n' << '\n';
	 cout << "test data2 " <<'\n';
	//test data2
	GraphType g2 = { 8,
	{ { 0, 10, INF, 6, INF, INF, INF, 1 },
	{ 10, 0, 4, INF, INF, 2, INF, INF },
	{ INF, 4, 0, 11, INF, 7, INF, INF },
	{ 6, INF, 11, 0, INF, INF, INF, 3 },
	{ INF, INF, INF, INF, 0, 5, INF, 8},
	{ INF, 2, 7, INF, 5, 0, 9, INF },
	{ INF, INF, INF, INF, INF, 9, 0, 12 },
	{ 1, INF, INF, 3, 8, INF, 12, 0 }
	}
	};
	prim(&g2, 0);
	return 0;
}
#endif