#include<iostream>
#include<cstdlib>
#include<ctime>

using namespace std;

#define SIZE 50000

struct element
{
	int key;
};

void insert_max_heap(element* list, element item, int& heap_size)
{
	heap_size++; 
	int i = heap_size; 

	while ((i != 1) && (item.key > list[i / 2].key)) {
		list[i] = list[i / 2];
		i /= 2;
	}
	list[i] = item; 
}

element delete_max_heap(element* list, int& heap_size)
{
	int parent, child;
	element item, temp;

	item = list[1];            
	temp = list[heap_size];    
	heap_size--;               

	parent = 1;
	child = 2;

	while (child <= heap_size) {
		if ((child < heap_size) && (list[child].key < list[child + 1].key)) {
			child++;
		}
		if (temp.key >= list[child].key) break; 

		list[parent] = list[child];
		parent = child; 
		child *= 2;
	}
	list[parent] = temp;
	return item; 
}

void heap_sort(element* list, element* sorted_list, int size)
{
	int heap_size = 0; 

	element* h = new element[size + 1];

	for (int i = 0; i < size; i++) {
		insert_max_heap(h, list[i], heap_size);
	}

	
	for (int i = (size - 1); i >= 0; i--) {
		sorted_list[i] = delete_max_heap(h, heap_size);
	}

	delete[] h; 
}

void selection_sort(element* list, element* sorted_list, int size)
{
	for (int i = 0; i < size; i++) {
		sorted_list[i] = list[i];
	}

	for (int i = 0; i < size - 1; i++) {
		int minimun = i;
		for (int j = i + 1; j < size; j++) {
			if (sorted_list[j].key < sorted_list[minimun].key) {
				minimun = j;
			}
		}
		element temp = sorted_list[i];
		sorted_list[i] = sorted_list[minimun];
		sorted_list[minimun] = temp;
	}
}

//-------------------------------------------------------------------------
int main()
//-------------------------------------------------------------------------
{
	element* list, * sorted_list; //원데이터와 정렬된 데이터 각각 저장용

	int i, s_time, e_time;
	srand(100);
	list = new element[SIZE];
	sorted_list = new element[SIZE];

	for (i = 0; i < SIZE; i++) list[i].key = rand();

	printf("정수형 데이터 %d개 정렬 \n", SIZE);

	if (SIZE < 100) {
		for (int i = 0; i < SIZE; i++) printf("%d ", list[i].key);
		printf("\n\n");
	}

	s_time = clock();

	heap_sort(list, sorted_list, SIZE);

	e_time = clock();

	printf("Heap Sort 걸린 시간 : %d msec\n", e_time - s_time);
	if (SIZE < 100) {
		for (int i = 0; i < SIZE; i++) printf("%d ", sorted_list[i].key);
		printf("\n\n");
	}

	s_time = clock();

	selection_sort(list, sorted_list, SIZE);

	e_time = clock();

	printf("Selection Sort 걸린 시간 : %d msec\n", e_time - s_time);


	if (SIZE < 100) {
		for (int i = 0; i < SIZE; i++) printf("%d ", sorted_list[i].key);
		printf("\n");
	}


	return 0;
}