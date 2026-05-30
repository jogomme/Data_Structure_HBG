#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>

using namespace std;

#define SIZE 1000000 // 데이터크기를 변경하며 테스트
#define SWAP(x, y, t) ( (t)=(x), (x)=(y), (y)=(t) )

// 병합 정렬을 위한 전역 변수 선언
int* sorted;

// --- 기수 정렬을 위한 교재 스타일 원형 큐(Queue) 구현 ---
#define MAX_QUEUE_SIZE 100000

typedef int element;
typedef struct {
	element data[MAX_QUEUE_SIZE];
	int front, rear;
} QueueType;

void error(const char* message) {
	cout << message << '\n';
	exit(1);
}

void init(QueueType* q) {
	q->front = q->rear = 0;
}

int Is_empty(QueueType* q) {
	return (q->front == q->rear);
}

int is_full(QueueType* q) {
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

void enqueue(QueueType* q, element item) {
	if (is_full(q)) {
		error("큐가 포화상태입니다");
	}
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = item;
}

element dequeue(QueueType* q) {
	if (Is_empty(q)) {
		error("큐가 공백상태입니다");
	}
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->data[q->front];
}
// ----------------------------------------------------

void selection_sort(int list[], int n)
{
	int i, j, least, temp;
	for (i = 0; i < n - 1; i++) {
		least = i;
		for (j = i + 1; j < n; j++) if (list[j] < list[least]) least = j;
		SWAP(list[i], list[least], temp);
	}
}

void insertion_sort(int list[], int n)
{
	int i, j, key;
	for (i = 1; i < n; i++) {
		key = list[i];
		for (j = i - 1; j >= 0 && list[j] > key; j--)
			list[j + 1] = list[j];
		list[j + 1] = key;
	}
}

// gap 만큼 떨어진 요소들을 삽입 정렬
void inc_insertion_sort(int list[], int first, int last, int gap)
{
	int i, j, key;
	for (i = first + gap; i <= last; i = i + gap) {
		key = list[i];
		for (j = i - gap; j >= first && key < list[j]; j = j - gap)
			list[j + gap] = list[j];
		list[j + gap] = key;
	}
}

void shell_sort(int list[], int n)
{
	int i, gap;
	for (gap = n / 2; gap > 0; gap = gap / 2) {
		if ((gap % 2) == 0) gap++;
		for (i = 0; i < gap; i++)
			inc_insertion_sort(list, i, n - 1, gap);
	}
}

void bubble_sort(int list[], int n)
{
	int i, j, temp;
	for (i = n - 1; i > 0; i--) {
		for (j = 0; j < i; j++)
			if (list[j] > list[j + 1])
				SWAP(list[j], list[j + 1], temp);
	}
}

void merge(int list[], int left, int mid, int right)
{
	int i, j, k, l;
	i = left; j = mid + 1; k = left;

	while (i <= mid && j <= right) {
		if (list[i] <= list[j]) sorted[k++] = list[i++];
		else sorted[k++] = list[j++];
	}
	if (i > mid)
		for (l = j; l <= right; l++)
			sorted[k++] = list[l];
	else
		for (l = i; l <= mid; l++)
			sorted[k++] = list[l];

	for (l = left; l <= right; l++)
		list[l] = sorted[l];
}

void merge_sort(int list[], int left, int right)
{
	int mid;
	if (left < right)
	{
		mid = (left + right) / 2;
		merge_sort(list, left, mid);
		merge_sort(list, mid + 1, right);
		merge(list, left, mid, right);
	}
}

int partition(int list[], int left, int right) {
	int pivot, temp;
	int low, high;
	low = left;
	high = right + 1;
	pivot = list[left];
	do {
		do
			low++;
		while (low <= right && list[low] < pivot);
		do
			high--;
		while (high >= left && list[high] > pivot);
		if (low < high) SWAP(list[low], list[high], temp);
	} while (low < high);
	SWAP(list[left], list[high], temp);
	return high;
}

void quick_sort(int list[], int left, int right)
{
	if (left < right) {
		int q = partition(list, left, right);
		quick_sort(list, left, q - 1);
		quick_sort(list, q + 1, right);
	}
}

void heapify(int list[], int n, int i) {
	int largest = i;
	int left_child = 2 * i + 1;
	int right_child = 2 * i + 2;
	int temp;

	if (left_child < n && list[left_child] > list[largest]) {
		largest = left_child;
	}
	if (right_child < n && list[right_child] > list[largest]) {
		largest = right_child;
	}

	if (largest != i) {
		SWAP(list[i], list[largest], temp);
		heapify(list, n, largest);
	}
}

void heap_sort(int list[], int n) {
	int temp;
	for (int i = n / 2 - 1; i >= 0; i--) {
		heapify(list, n, i);
	}
	for (int i = n - 1; i > 0; i--) {
		SWAP(list[0], list[i], temp);
		heapify(list, i, 0);
	}
}

#define BUCKETS 10
#define DIGITS 5 

void radix_sort(int list[], int n)
{
	int i, b, d, factor = 1;
	QueueType queues[BUCKETS];
	for (b = 0; b < BUCKETS; b++) init(&queues[b]);
	for (d = 0; d < DIGITS; d++) {
		for (i = 0; i < n; i++) enqueue(&queues[(list[i] / factor) % 10], list[i]);
		for (b = i = 0; b < BUCKETS; b++) while (!Is_empty(&queues[b]))
			list[i++] = dequeue(&queues[b]);
		factor *= 10;
	}
}

int main(void)
{
	int i, s_time, e_time;
	int* data = (int*)malloc(sizeof(int) * SIZE);
	int* list = (int*)malloc(sizeof(int) * SIZE);
	sorted = (int*)malloc(sizeof(int) * SIZE);

	if (data == NULL || list == NULL || sorted == NULL) {
		cout << "데이터 저장을 위한 메모리 할당 오류\n";
		exit(-1);
	}

	cout << "정렬 기법 비교 \n";
	cout << "Data 크기 : " << SIZE << " \n\n";

	srand(100);
	for (i = 0; i < SIZE; i++) data[i] = rand();

	memcpy(list, data, sizeof(int) * SIZE);
	s_time = clock();
	selection_sort(list, SIZE);
	e_time = clock();
	cout << "선택정렬 시간 : " << e_time - s_time << "\n";
	if (SIZE <= 100) {
		for (i = 0; i < SIZE; i++)
			cout << list[i] << " ";
		cout << "\n\n";
	}

	memcpy(list, data, sizeof(int) * SIZE);
	s_time = clock();
	insertion_sort(list, SIZE);
	e_time = clock();
	cout << "삽입정렬 시간 : " << e_time - s_time << "\n";
	if (SIZE <= 100) {
		for (i = 0; i < SIZE; i++)
			cout << list[i] << " ";
		cout << "\n\n";
	}

	memcpy(list, data, sizeof(int) * SIZE);
	s_time = clock();
	bubble_sort(list, SIZE);
	e_time = clock();
	cout << "버블정렬 시간 : " << e_time - s_time << "\n";
	if (SIZE <= 100) {
		for (i = 0; i < SIZE; i++)
			cout << list[i] << " ";
		cout << "\n\n";
	}

	memcpy(list, data, sizeof(int) * SIZE);
	s_time = clock();
	shell_sort(list, SIZE);
	e_time = clock();
	cout << "셸정렬 시간 : " << e_time - s_time << "\n";
	if (SIZE <= 100) {
		for (i = 0; i < SIZE; i++)
			cout << list[i] << " ";
		cout << "\n\n";
	}

	memcpy(list, data, sizeof(int) * SIZE);
	s_time = clock();
	merge_sort(list, 0, SIZE - 1);
	e_time = clock();
	cout << "병합정렬 시간 : " << e_time - s_time << "\n";
	if (SIZE <= 100) {
		for (i = 0; i < SIZE; i++)
			cout << list[i] << " ";
		cout << "\n\n";
	}

	memcpy(list, data, sizeof(int) * SIZE);
	s_time = clock();
	quick_sort(list, 0, SIZE - 1);
	e_time = clock();
	cout << "퀵정렬 시간 : " << e_time - s_time << "\n";
	if (SIZE <= 100) {
		for (i = 0; i < SIZE; i++)
			cout << list[i] << " ";
		cout << "\n\n";
	}

	memcpy(list, data, sizeof(int) * SIZE);
	s_time = clock();
	heap_sort(list, SIZE);
	e_time = clock();
	cout << "힙정렬 시간 : " << e_time - s_time << "\n";
	if (SIZE <= 100) {
		for (i = 0; i < SIZE; i++)
			cout << list[i] << " ";
		cout << "\n\n";
	}

	memcpy(list, data, sizeof(int) * SIZE);
	s_time = clock();
	radix_sort(list, SIZE);
	e_time = clock();
	cout << "기수정렬 시간 : " << e_time - s_time << "\n";
	if (SIZE <= 100) {
		for (i = 0; i < SIZE; i++)
			cout << list[i] << " ";
		cout << "\n\n";
	}

	free(data); free(list); free(sorted);
	return 0;
}