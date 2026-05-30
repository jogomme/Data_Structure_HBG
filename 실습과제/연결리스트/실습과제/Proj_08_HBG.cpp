#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<random>
#include <conio.h> 
#include <cstdlib>

using namespace std;

#define PROB 2 // 각각의 문제를 구현하고 해당 문제 번호를 변경하여 테스트

#define MAX_LIST_SIZE 100




#if PROB == 1
// 1번 문제를 해결하기 위한 프로그램 작성

int 내림차순(const void* a, const void* b) {
	int x = *(int*)a;
	int y = *(int*)b;

	if (x < y)
		return 1;
	if (x > y)
		return -1;
	return 0;

}

struct SortedList
{
	int num[MAX_LIST_SIZE]{ -1 };
	int capacity = 0;
};

int is_full(SortedList* arr)
{
	return (MAX_LIST_SIZE == arr->capacity);
}
void add(SortedList* arr, int val)
{
	if (is_full(arr)) return; 

	int i = (arr->capacity) - 1;
	
	while (i >= 0 && arr->num[i] > val) {
		arr->num[i + 1] = arr->num[i];
		i--;
	}
	
	arr->num[i + 1] = val;
	arr->capacity += 1;
}

void display(SortedList* arr)
{
	for (int i = 0; i < arr->capacity; ++i) {
		cout << arr->num[i] << "->";
	}
	cout << '\n';
}

int get_length(SortedList* arr)
{
	return arr->capacity;
}

int is_emptyL(SortedList* arr)
{
	return (arr->capacity == 0);
}	


SortedList* reverse(SortedList* arr)
{
	qsort(arr->num, arr->capacity, sizeof(int), 내림차순 );
	return arr;
}

int get_entry(SortedList* arr, int num)
{
	if(num <= arr->capacity && num >= 0) 
		return arr->num[num-1];
	return -1;
}

int is_in_list(SortedList* arr, int num)
{
	for (int i = 0; i < arr->capacity; ++i) {
		if (arr->num[i] == num) {
			return i+1;
		}
	}

	return -1;
}

int deleteL(SortedList* arr, int num)
{
	for (int i = 0; i < arr->capacity; ++i) {
		if (arr->num[i] == num) {
			for (int j = i; j < arr->capacity-1; ++j) {
				arr->num[j] = arr->num[j + 1];
			}
			arr->capacity -= 1;
			return i + 1;
		}
	}
}

void clear(SortedList* arr) 
{
	arr->capacity = 0;
}


int main()
{
	int item;
	char ch;
	SortedList list;
	SortedList* rList;
	srand(100);
	//필요한 초기화 코드 추가
	while (1) {
		item = rand();
		add(&list, item);
		display(&list);
		ch = _getch();
		if (ch == 'q') break;
	}
	printf("get_length : %d \n", get_length(&list));
	printf("is_empty : %d, is_full : %d \n", is_emptyL(&list), is_full(&list));
	printf("get_entry : %d위치의 데이터는 %d\n", 5, get_entry(&list, 5));
	printf("is_in_list : %d의 위치는 %d \n", 5415, is_in_list(&list, 5415));
	printf("is_in_list : %d의 위치는 %d \n", 10, is_in_list(&list, 10));
	printf("delete : %d의 위치는 %d \n", 5415, deleteL(&list, 5415));
	display(&list);
	rList = reverse(&list);
	display(rList);
	printf("call clear\n");
	clear(&list);
	display(&list);
	printf("get_length : %d \n", get_length(&list));
	//종료하기 전에 수행해야 할 코드 추가

}

#elif PROB == 2
// 2번 문제를 해결하기 위한 프로그램 작성

class SortedList
{
private:
public:
	SortedList* next;
	int num;

	SortedList() {
		next = nullptr;
		num = 0;
	}
	~SortedList() {
		
	}
};

int is_full(SortedList* head) {
	SortedList* CurList = head;

	int Count{};

	int max = MAX_LIST_SIZE;

	while (CurList != nullptr) {
		if (Count == max) {
			return 1;
		}
		CurList = CurList->next;
		Count++;
	}

	return 0;

}

SortedList* add(SortedList* head, int num) {

	if (!is_full(head)) {
		SortedList* newList{new SortedList};
		newList->num = num;
		if (head == nullptr) {
			head = newList;
			return newList;
		}
		else if (head->num >= num) {
			newList->next = head;
			return newList;
		}

		SortedList* CurList = head;
		SortedList* preList = nullptr;

		while (CurList != nullptr && CurList->num < num) {
			preList = CurList;
			CurList = CurList->next;
		}
		newList->next = CurList;
		preList->next = newList;
	}
	return head;
}

int deleteL(SortedList* head, int item)
{
	SortedList* CurList = head;

	SortedList* preList = nullptr;

	int order{-1};

	while (CurList != nullptr) {
		order++;
		if (CurList ->num == item) {
			if (preList == nullptr) {
				head = CurList->next;
			}
			else {
				preList->next = CurList->next;
			}
			delete CurList;
			return order;
		}
		preList = CurList;
		CurList = CurList->next;
	}

	cout << item << "은(는) 존재하지 않는 item입니다. " << '\n';
	return -1;

}


void clear(SortedList* head) {
	
	SortedList* CurList = head->next;
	SortedList* preList = nullptr;

	while (CurList != nullptr) {
		preList = CurList;
		CurList = CurList->next;
		delete preList;
	}
	
	head->next = nullptr;

}

int is_in_list(SortedList* head, int item) 
{
	SortedList* CurList = head;

	int order{-1};

	while (CurList != nullptr) {
		order++;
		if (CurList->num == item) {
			return order;
		}
		CurList = CurList->next;
	}
	return -1;
}

int get_length(SortedList* head) {
	SortedList* CurList = head;

	int order{-1};

	while (CurList != nullptr) {
		order++;
		CurList = CurList->next;
	}
	return order;
}

int get_entry(SortedList* head, int pos)
{
	SortedList* CurList = head;

	if (CurList == nullptr) {
		return -1;
	}

	for (int i = 0; i < pos; ++i) {
		CurList = CurList->next;
		if (CurList == nullptr) {
			return -1;
		}
	}

	if (CurList != nullptr) {
		return CurList->num;
	}
	else {
		return -1;
	}

}

int is_emptyL(SortedList* head)
{
	if (head == nullptr) {
		return 1;
	}
	else return 0;
}



SortedList* reverse(SortedList* head)
{
	SortedList* q = nullptr;
	SortedList* r = head->next;
	SortedList* p;

	while (r != nullptr) {
		p = q;
		q = r;
		r = r->next;

		q->next = p;

	}

	head->next = q;


	return head;

}

void display(SortedList* head)
{
	SortedList* CurList = head->next;

	if (head == nullptr)return;

	while (CurList != nullptr) {
		cout << CurList->num << " -> ";
		CurList = CurList->next;
	}
	cout << '\n';

}

int main(void) {
	int item;
	char ch;
	SortedList list;
	SortedList* rList;

	srand(100);
	//필요한 초기화 코드 추가
	while (1) {
		item = rand();
		add(&list, item);
		display(&list);
		ch = _getch();
		if (ch == 'q') break;
	}
	printf("get_length : %d \n", get_length(&list));
	printf("is_empty : %d, is_full : %d \n", is_emptyL(&list), is_full(&list));
	printf("get_entry : %d위치의 데이터는 %d\n", 5, get_entry(&list, 5));
	printf("is_in_list : %d의 위치는 %d \n", 5415, is_in_list(&list, 5415));
	printf("is_in_list : %d의 위치는 %d \n", 10, is_in_list(&list, 10));
	printf("delete : %d의 위치는 %d \n", 5415, deleteL(&list, 5415));
	display(&list);
	
	
	rList = reverse(&list);
	
	
	display(rList);
	printf("call clear\n");
	clear(&list);
	display(&list);
	printf("get_length : %d \n", get_length(&list));
	//종료하기 전에 수행해야 할 코드 추가
	
	
return 0;
}
#endif