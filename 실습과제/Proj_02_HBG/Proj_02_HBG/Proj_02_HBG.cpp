#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>

#include<iostream>

using namespace std;


int rec_count = 0; //재귀적 함수 호출 횟수를 저장하기 위한 함수

#define PROB 6

// 각각의 문제를 구현하고 해당 문제 번호를 변경하여 테스트

#if PROB == 1

/* Compute power(x, n) for int x, n */
// 1번 문제에 대한 반복, 재귀적 방법으로 구현하기 위한 각각의 함수 구현
// main 함수에서 데이터를 입력받아 호출하는 코드와 결과 출력 구현

int itr_power(int x, int n) 
{
	int result = 1;
	for (int i = 0; i < n; ++i) {
		result *= x;
	}
	return result;

};


int rec_power(int x, int n) 
{
	rec_count += 1;

	if (n == 0) {
		return 1;
	}

	else if (n%2 == 0) {
		return rec_power(x * x, n / 2);
	}

	else if (n % 2 == 1) {
		return x * rec_power(x * x, (n - 1) / 2);
	}

};


void main(void)
{
	int x, n;
	double result;
	clock_t start, end;
	printf("문제 1 \n");
	printf("x, n 입력(x^n) :");
	scanf("%d %d", &x, &n);
	start = clock();
	result = itr_power(x, n);
	end = clock();
	printf("ITR : %d^%d = %f, 수행시간 :%f\n", x, n, result, (double)(end - start) / CLOCKS_PER_SEC);
	start = clock();
	result = rec_power(x, n);
	end = clock();
	printf("REC : %d^%d = %f, 수행시간 :%f, 함수호출횟수 : %d\n", x, n, result, (double)(end - start) / CLOCKS_PER_SEC, rec_count);
	return;
}
#elif PROB == 2

/* Binomial Coef */
// 2번 문제에 대한 반복, 재귀적 방법으로 구현하기 위한 각각의 함수 구현
// main 함수에서 데이터를 입력받아 호출하는 코드와 결과 출력 구현



int itr_C(int n, int k)
{
	if (0 < k && k < n) {

		int factorialOfK{ 1 };
		int factorialOfN{ 1 };
		int factorialOfNUM{ 1 };


		for (int i = 1; i < n+1; i++) {
			factorialOfN *= i;
			if (i <= k) {
				factorialOfK *= i;
			}
			if (i <= (n - k)) {
				factorialOfNUM *= i;
			}
		}

		return factorialOfN / (factorialOfK * factorialOfNUM);

	}
	else if (k == 0 || k == n) {
		return 1;
	}

	return 0;
}

//n-1Ck-1 + n-1Ck
int rec_C(int n, int k)
{
	
	rec_count += 1;

	if (n == k || k == 0) {
		return 1;
	}
	
	return rec_C(n - 1, k - 1) + rec_C(n - 1, k); 
}

int main()
{
	int n{}, k{};
	clock_t start, end;
	int result{};

	cout << "이항 계수 C에 대하여 n 과 k를 입력하여 주세요 : ";
	cin >> n >> k;

	start = clock();
	result = itr_C(n, k);
	end = clock();

	cout << "ITR 이항계수 " << n << " by " << k << " = " << result << "입니다." << endl;
	cout << "소요 시간은 " << double(end - start) / CLOCKS_PER_SEC  << "초 입니다." << endl << endl;

	start = clock();
	result = rec_C(n, k);
	end = clock();

	cout << "REC 이항계수 " << n << " by " << k << " = " << result << "입니다." << rec_count << "번 실행되었습니다." << endl;
	cout << "소요 시간은 " << double(end - start) / CLOCKS_PER_SEC << "초 입니다." << endl << endl;


}

#elif PROB == 3
/* Ackerman function */

void itr_AckermanF(int m, int n)
{
	NULL;
}

int rec_AckermanF(int m, int n)
{
	++rec_count;

	if (m == 0) {
		return n + 1;
	}
	else if ( m != 0 && n == 0 ) {
		return rec_AckermanF(m - 1, 1);
	}
	else {
		return rec_AckermanF(m - 1, rec_AckermanF(m, n - 1));
	}
}

int main()
{
	int result{};

	int m{}, n{};

	clock_t start, end;

	cout << "Ackerman 함수의 m, n을 입력하여 주세요 : ";
	cin >> m >> n;

	start = clock();
	result = rec_AckermanF(m, n);
	end = clock();

	cout << "REC : Akerman 함수 " << m << " ," << n << "일때 값은 " << result << "입니다." << endl;
	cout << "소요 시간은 " << double(end - start) / CLOCKS_PER_SEC << "초 입니다." << "함수 호출 횟수는 " << rec_count << "입니다." << endl << endl;


}

#elif PROB == 4
/* 피보나치 수열 */

int itr_F(int n)
{
	if (n == 0) return 0;
	if (n == 1) return 1;

	int pp{};
	int p{1};

	int result{};

	for (int i = 2; i <= n; ++i) {
		result = pp + p;
		pp = p;
		p = result;
	}

	return result;

}

int rec_F(int n)
{
	++rec_count;

	if (n == 0) return 0;
	if (n == 1) return 1;
	return (rec_F(n - 1) + rec_F(n - 2));
}


int main()
{
	int result{};
	int n{};

	cout << "원하는 수열의 수를 입력해 주세요 : ";
	
	cin >> n;

	clock_t start, end;

	start = clock();
	result = itr_F(n);
	end = clock();

	cout << "ITR 피보나치 " << n  << " 번 째 수열의 값 = " << result << "입니다." << endl;
	cout << "소요 시간은 " << double(end - start) / CLOCKS_PER_SEC << "초 입니다." << endl << endl;

	start = clock();
	result = rec_F(n);
	end = clock();

	cout << "REC 이항계수 " << n << " 번 째 수열의 값 = " << result << "입니다." << rec_count << "번 실행되었습니다." << endl;
	cout << "소요 시간은 " << double(end - start) / CLOCKS_PER_SEC << "초 입니다." << endl << endl;
}


#elif PROB == 5
/* Binary Search */

#define SIZE 100000


int itr_serch(int num , int ary[])
{
	int result{};

	int initial = SIZE / 2;
	int highest{1000};
	int lowest{0};

	while (true) {
		
		if (num > ary[initial]) {
			lowest = initial;
			initial = (highest + initial) / 2;
		}
		else if (num < ary[initial]) {
			highest = initial;
			initial = (lowest + initial) / 2;
		}
		else if (num == ary[initial]){
			result = initial;
			break;
		}
		else {
			cout << "값이 존재하지 않습니다." << endl;
			break;
		}
	}

	return result;
}

int rec_serch(int num, int ary[], int high = SIZE,int low = 0)
{
	++rec_count;

	int middle = (high + low) / 2;

	if (num == ary[middle]) {
		return middle;
	}
	if (num > ary[middle]) {
		rec_serch(num, ary,high,middle );
	}
	else if (num < ary[middle]) {
		rec_serch(num, ary, middle, low );
	}

}

int main()
{	
	int* Ary = new int[SIZE];

	for (int i = 0; i < SIZE; ++i) {
		Ary[i] = i + 1;
	}

	clock_t start, end;
	
	int result{};

	// 출력 확인
	//for (int i = 0; i < SIZE; ++i) {
	//	cout << Ary[i] << " ";
	//}

	int num{};

	cout << "찾을 숫자를 입력해 주세요 : ";
	cin >> num;

	start = clock();
	result = itr_serch(num, Ary);
	end = clock();

	cout << "ITR : 값 " << num << "의 INDEX : " << result << "입니다." << endl;
	cout << "소요 시간은 " << double(end - start) / CLOCKS_PER_SEC << "초 입니다." << endl << endl;

	start = clock();
	result = rec_serch(num, Ary);
	end = clock();

	cout << "REC : 값 " << num << "의 INDEX : " << result << "입니다. 함수 호출 횟수 " << rec_count << "입니다." << endl;
	cout << "소요 시간은 " << double(end - start) / CLOCKS_PER_SEC << "초 입니다." << endl << endl;

}

#elif PROB == 6 // 선택
/* Hanoi Tower */

void rec_hanoi_tower(int n, char from, char tmp, char to)
{
	rec_count++;
	//cout << rec_count << endl << endl;
	cout << endl;
	if (n == 1) printf("원판 1을 %c 에서 %c으로 옮긴다.\n", from, to);
	else {
		rec_hanoi_tower(n - 1, from, to, tmp);
		printf("원판 %d을 %c에서 %c으로 옮긴다.\n", n, from, to);

		rec_hanoi_tower(n - 1, tmp, from, to);	// disk가 3이 들어올 경우 2번만 반복하면 끝남
	}
}

void itrHanoiTower(int disk, char from, char tmp, char to)
{

	char m_from{ from };
	char m_tmp{ tmp };
	char m_to{ to };
	char m_pp{};

	int total = disk * disk - 1;

	int cnt{};

	for (int i = 1; i < total; ++i) {

		if ((i % 2) == 1) {
			cout << "원판 1을 " << m_from << "에서 " << m_to << "로 옮긴다." << endl;
			m_pp = m_tmp;
			m_tmp = m_to;
			m_to = m_pp;
			cout << "원판 2을 " << m_from << "에서 " << m_to << "로 옮긴다." << endl;
			m_pp = m_from;
			m_from = m_tmp;
			m_tmp = m_to;
			m_to = m_pp;
			cout << "원판 1을 " << m_from << "에서 " << m_to << "로 옮긴다." << endl;
			i += 3;
		}
		else {
		
		}

	}

}



int main()
{
	int NumOfDisk{};

	cout << "disk 수를 입력해 주세요 : ";
	cin >> NumOfDisk;
	cout << endl;

	rec_hanoi_tower(NumOfDisk, 'A', 'B', 'C');

	cout << endl << endl;

	itrHanoiTower(NumOfDisk, 'A', 'B', 'C');
}

#endif