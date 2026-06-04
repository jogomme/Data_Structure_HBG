#include <stdlib.h>
#include<iostream>
#include<string>

#define TABLE_SIZE 10000 // 가능하면 해싱 테이블의 크기를 소수로 설정 
#define SIZE TABLE_SIZE/2 //적재율을 SIZE/TABLE_SIZE로 계산
#define SEARCH_COUNT 1000000

#define INF 999999

typedef struct {
	int key;
} element;

struct list
{
	element item;
	struct list* link;
};

//struct list* Chash_table[TABLE_SIZE]; 체이닝 기법
struct list** Chash_table; 

//element Lhash_table[TABLE_SIZE]; 선형기법
element* Lhash_table; 

// 선형 해쉬 테이블 초기화
void init_Lhash_table(element Lhash_table[], int TableSize)
{
	for (int i = 0; i < TableSize; ++i) {
		Lhash_table[i].key = INF;
	}
}

// 체이스 해쉬 테이블 초기화
void init_Chash_table(struct list* Chash_table[], int TableSize)
{
	for (int i = 0; i < TableSize; ++i) {
		Chash_table[i] = nullptr;
	}
}


// 소수인지 판별하는 방법
bool isPrime(int num)
{
	for (int i = 2; i * i <= num; ++i) {
		if (num % i == 0) {
			return false;
		}
	}
	return true;
}

// TableSize보다 작은 최대 소수 구하기
int get_prime_number(int TableSize)
{
	// 1이하면 소수가 없음
	if (TableSize <= 1) {
		return -1;
	}


	for (int i = TableSize - 1; i >= 2; --i) {
		if (isPrime(i)) {
			return i;
		}
	}

	return -1;

}

// 제산 함수를 사용한 해싱 함수
int hash_function(int key)
{
	return key % TABLE_SIZE;
}

// 이중해시를 도입한 선형적 기법 해시 삽입
void hash_linear_add(element item, element Lhash_table[], int hPrime)
{
	int hash_index;
	int value;

	hash_index = value = hash_function(item.key);

	int doubleHash = hPrime - (item.key % hPrime);

	do {
		if (Lhash_table[hash_index].key == INF) {
			Lhash_table[hash_index] = item;
			return;
		}

		hash_index = (hash_index + doubleHash)%TABLE_SIZE;



	} while (value != hash_index);

	std::cout << "해시 포화" << '\n';

}

// 선형적 기법을 이용한 해시 탐색
element hash_linear_search(element item, element Lhash_table[], int hPrime)
{
	int hash_index;
	int value;

	hash_index = value = hash_function(item.key);

	int doubleHash = hPrime - (item.key % hPrime);

	do {
		if (Lhash_table[hash_index].key == item.key) {
			//std::cout << item.key << "탐색 위치 " << hash_index << '\n';
			return Lhash_table[hash_index];
		}

		hash_index = (hash_index + doubleHash) % TABLE_SIZE;

		if (Lhash_table[hash_index].key == INF) {
			break;
		}

	} while (value != hash_index);

	element e;
	e.key = INF;

	//std::cout << "찾는 값이 테이블에 없습니다.";
	return e;
}

// 체이닝 기법을 활용한 해시 삽입
void hash_chain_add(element item, list* Chash_table[])
{
	int hash_index;

	hash_index =  hash_function(item.key);

	list* newNode = new list;

	newNode->item = item;
	
	newNode->link = Chash_table[hash_index];

	Chash_table[hash_index] = newNode;

}

element hash_chain_search(element item, list* Chash_table[])
{
	int hash_index;

	hash_index = hash_function(item.key);

	list* CurNode = Chash_table[hash_index];

	while (CurNode != nullptr) {
		if (CurNode->item.key == item.key) {
			//std::cout << item.key << " 탐색 위치 : " << hash_index << '\n';
			return CurNode->item;
		}
		CurNode = CurNode->link;
	}

	element e;
	e.key = INF;

	//std::cout << "데이터에 해당 키 값을 지닌 데이터는 없습니다" << '\n';

	return e;

}


int main(void)
{
	int s_time, e_time;
	int h_prime;
	element e;
	Lhash_table = (element*)malloc(sizeof(element) * TABLE_SIZE);
	Chash_table = (struct list**)malloc(sizeof(struct list*) * TABLE_SIZE);
	init_Lhash_table(Lhash_table, TABLE_SIZE);
	init_Chash_table(Chash_table, TABLE_SIZE);
	srand(100);

	//이중 해시법을 적용하기 위한 버킷 사이즈보다 작은 가장 큰 소수 구하기
	h_prime = get_prime_number(TABLE_SIZE); 

	for (int i = 0; i < SIZE; i++) { //적재율까지만 저장
		e.key = rand();
		hash_linear_add(e, Lhash_table, h_prime);
		hash_chain_add(e, Chash_table);
	}

	srand(200);
	s_time = clock();
	for (int i = 0; i < SEARCH_COUNT; i++) {
		e.key = rand();
		hash_linear_search(e, Lhash_table, h_prime);
	}
	e_time = clock();

	printf("선형기법\n");
	std::cout << "적재율이 " << (float)SIZE / TABLE_SIZE << "인경우 " << SEARCH_COUNT << "회 검색 시 소요시간 "
		<< e_time - s_time << '\n';

	srand(200);
	s_time = clock();
	for (int i = 0; i < SEARCH_COUNT; i++) {
		e.key = rand();
		hash_chain_search(e, Chash_table);
	}
	e_time = clock();
	printf("체인기법\n");

	std::cout << "적재율이 " << (float)SIZE / TABLE_SIZE << "인경우 " << SEARCH_COUNT << "회 검색 시 소요시간 "
		<< e_time - s_time << '\n';

	return 0;
}