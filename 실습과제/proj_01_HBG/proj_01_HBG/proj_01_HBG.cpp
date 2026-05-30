#include<iostream>
#include<chrono>
#include<time.h>

using namespace std;

struct LinkedList{
	int num;
	LinkedList* next;
};

void insertAry(int arr[], int& CurSize, int val) {
	int i = CurSize - 1;
	while (i >= 0 && arr[i] > val) {
		arr[i + 1] = arr[i];
		i--;
	}
	arr[i + 1] = val;
	CurSize += 1;
}

void insertList(LinkedList** head, int val) {
	LinkedList* newList = new LinkedList;
	newList->num = val;
	newList->next = nullptr;

	if (*head == nullptr || (*head)->num >= val) {
		newList->next = *head;
		*head = newList;
		return;
	}

	LinkedList* Cur = *head;
	
	while (Cur->next != nullptr && Cur->next->num < val) {
		Cur = Cur->next;
	}

	newList->next = Cur->next;
	Cur->next = newList;

}

void PrintLinkedList(LinkedList* head) {
	int Cnt{};
	if (head == nullptr) {
		cout << "NULL" << endl;
		return;
	}

	while (head != nullptr) {
		cout << head ->num << " ";
		head = head->next;
		Cnt += 1;
		if (Cnt > 10) {
			cout << endl;
		}
		Cnt = 0;
	}
	cout << endl;
	return;
}

int main() 
{
	srand(100); 
	int SizeOfNum{15'0000};
	//int seed{};

	unsigned int seed = (unsigned int)time(NULL);

	//cout << "시드값을 입력해주세요 : ";
	//cin >> seed;
	cout << endl;
	//cout << "몇개의 정수를 입력받으실 건가요? : ";
	//cin >> SizeOfNum;

	cout << "해당 결과의 시드 값은 : " << seed << "입니다" << endl;
	
	// ----------------------------------------------------------------------
	// 배열
	int* Array = new int[SizeOfNum];
	int CurSize = 0;
	srand(seed);	

	clock_t start = clock();

	for (int i = 0; i < SizeOfNum; i++) {
		insertAry(Array, CurSize, rand());
	}

	clock_t end = clock();   // 종료

	//출력부분
	//int CntOfR{};
	//for (int i = 0; i < SizeOfNum; ++i) {
	//	cout << Array[i] << " ";
	//	CntOfR += 1;
	//	if (CntOfR > 10) {
	//		cout << endl;
	//	}
	//	CntOfR = 0;
	//
	//}
	//CntOfR = 0;

	cout << endl;

	double result = (double)(end - start) / CLOCKS_PER_SEC;
	cout << "배열 소요 시간 : " <<  result << "초";
	cout << endl;

	
	// -----------------------------------------------------------------------
	// 연결리스트

	LinkedList* head = nullptr;

	srand(seed);

	start = clock();

	for (int i = 0; i < SizeOfNum; ++i) {
		insertList(&head, rand());
	}
	

	end = clock();  

	// 출력 ㅂ분
	//PrintLinkedList(head);

	cout << endl;
	result = (double)(end - start) / CLOCKS_PER_SEC;
	cout << "연결 리스트 소요 시간 : " << result << "초";


	delete[] Array;

	while (head != nullptr) { // 연결 리스트 노드 각각 해제
		LinkedList* temp = head;
		head = head->next;
		delete temp;
	}


}
