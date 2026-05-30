#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

#include<iostream>
#include<string>

using namespace std;

#define PROB 2 // 다항식 저장 방법 선택

#if PROB == 1
// 배열을 이용한 다항식 표현 및 덧셈, 곱셈

#define MAX_TERM 101 //최대 차수 100
#define MAX_DEGREE 101 // 다항식의 최대차수 + 1


typedef struct polynomial {
	int degree;
	int coef[MAX_TERM];
}POLY;
// 여기에 필요한 함수 구현

void printPoly(const char* a, POLY b) {
	cout << a << " = ";
	for (int i = b.degree; i > 0; --i) {
		cout << b.coef[b.degree - i] << "^" << i << " + ";
	}
	cout << b.coef[b.degree] << endl;
}

int MAX(int a, int b)
{
	if (a >= b) return a;
	else
	{
		return b;
	}
}

POLY addPoly(POLY A, POLY B) {
	POLY C;

	int Apos = 0, Bpos = 0, Cpos = 0; // 배열 인덱스 변수
	int degree_a = A.degree;
	int degree_b = B.degree;

	C.degree = MAX(A.degree, B.degree); // 결과 다항식 차수

	while (Apos <= A.degree && Bpos <= B.degree) {

		if (degree_a > degree_b) { // A항 > B항
			C.coef[Cpos++] = A.coef[Apos++];
			degree_a--;
		}
		else if (degree_a == degree_b) { // A항 == B항
			C.coef[Cpos++] = A.coef[Apos++] + B.coef[Bpos++];
			degree_a--; degree_b--;
		}
		else { // B항 > A항
			C.coef[Cpos++] = B.coef[Bpos++];
			degree_b--;
		}
	}
	return C;
}




POLY mulPoly(POLY A, POLY B) {
	POLY C;

	C.degree = A.degree + B.degree;

	for (int i = 0; i <= C.degree; ++i) {
		C.coef[i] = 0;
	}

	for (int i = 0; i <= A.degree; ++i) {
		for (int j = 0; j <= B.degree; ++j) {
			C.coef[i + j] += A.coef[i] * B.coef[j];
		}
	}

	return C;
}



int main(void) {
	POLY a = { 5, {3, 0, 4, -2, 1, 7} }; // a(x) = 3x5 + 4x3 - 2x2 + 1x + 7
	POLY b = { 3, {4, 2, -6, -3} }; // b(x) = 4x3 + 2x2 - 6x - 3
	POLY c, d; //for result
	printPoly("a(x)", a);
	printPoly("b(x)", b);
	c = addPoly(a, b);
	printPoly("c(x) = a(x) + b(x) ", c);
	d = mulPoly(a, b);
	printPoly("d(x) = a(x) x b(x) ", d);
	return 0;
}




#elif PROB == 2
#define MAX_TERM 101 //최대 차수 100
typedef struct term { int coef; int exp; } TERM;

typedef struct polynomial {
	int num_of_terms;
	TERM terms[MAX_TERM];
}POLY;
// 여기에 필요한 함수 구현

void printPoly(const char* name, POLY p) {
	cout << name << " = ";
	for (int i = 0; i < p.num_of_terms; i++) {
		cout << p.terms[i].coef << "x^" << p.terms[i].exp;
		if (i < p.num_of_terms - 1) cout << " + ";
	}
	cout << endl;
}

void attach(POLY* p, int coef, int exp) {
	if (coef == 0) return;
	p->terms[p->num_of_terms].coef = coef;
	p->terms[p->num_of_terms].exp = exp;
	p->num_of_terms++;
}

POLY addPoly(POLY A, POLY B) {
	POLY C;
	C.num_of_terms = 0;
	int a = 0, b = 0;
	while (a < A.num_of_terms && b < B.num_of_terms) {
		switch (compare(A.terms[a].exp, B.terms[b].exp)) {
		case '>': attach(&C, A.terms[a].coef, A.terms[a].exp); a++; break;
		case '=':
			int sum;
			sum = A.terms[a].coef + B.terms[b].coef;
			if (sum != 0) attach(&C, sum, A.terms[a].exp);
			a++; b++; break;
		case '<': attach(&C, B.terms[b].coef, B.terms[b].exp); b++; break;
		}
	}
	for (; a < A.num_of_terms; a++) attach(&C, A.terms[a].coef, A.terms[a].exp);
	for (; b < B.num_of_terms; b++) attach(&C, B.terms[b].coef, B.terms[b].exp);
	return C;
}

POLY mulPoly(POLY A, POLY B) {
	POLY C;
	C.num_of_terms = 0;
	// 임시 배열을 사용하여 차수별 계수 합산 (최대 차수는 200으로 가정)
	int temp_coef[201] = { 0 };
	int max_exp = 0;

	for (int i = 0; i < A.num_of_terms; i++) {
		for (int j = 0; j < B.num_of_terms; j++) {
			int e = A.terms[i].exp + B.terms[j].exp;
			temp_coef[e] += A.terms[i].coef * B.terms[j].coef;
			if (e > max_exp) max_exp = e;
		}
	}
	for (int i = max_exp; i >= 0; i--) {
		if (temp_coef[i] != 0) attach(&C, temp_coef[i], i);
	}
	return C;
}

int main(void) {
	POLY a = { 5, {3,5, 4,3, -2,2, 1,1, 7,0} }; // a(x) = 3x5 + 4x3 - 2x2 + 1x + 7
	POLY b = { 4, {4,3, 2,2, -6,1, -3,0} }; // b(x) = 4x3 + 2x2 - 6x - 3
	POLY c, d; //for result
	printPoly("a(x)", a);
	printPoly("b(x)", b);
	c = addPoly(a, b);
	printPoly("c(x) = a(x) + b(x) ", c);
	d = mulPoly(a, b);
	printPoly("d(x) = a(x) x b(x) ", d);
	return 0;
}



#elif PROB == 3
// 0이 아닌 계수를 연결리스트로 다항식 표현
typedef struct poly {
	int coef;
	int exp;
	struct poly* link;
}POLY;
// 여기에 필요한 함수 구현
POLY* add(POLY* head, POLY* newNode) {
	if (head == NULL) return newNode;
	POLY* p = head;
	while (p->link != NULL) p = p->link;
	p->link = newNode;
	return head;
}

void printPoly(const char* name, POLY* head) {
	cout << name << " = ";
	for (POLY* p = head; p != NULL; p = p->link) {
		cout << p->coef << "x^" << p->exp;
		if (p->link != NULL) cout << " + ";
	}
	cout << endl;
}

POLY* addPoly(POLY* A, POLY* B) {
	POLY* C = NULL;
	POLY* pA = A, * pB = B;
	while (pA && pB) {
		POLY* temp = (POLY*)malloc(sizeof(POLY));
		temp->link = NULL;
		if (pA->exp > pB->exp) {
			temp->coef = pA->coef; temp->exp = pA->exp;
			C = add(C, temp); pA = pA->link;
		}
		else if (pA->exp == pB->exp) {
			int sum = pA->coef + pB->coef;
			if (sum != 0) {
				temp->coef = sum; temp->exp = pA->exp;
				C = add(C, temp);
			}
			else free(temp);
			pA = pA->link; pB = pB->link;
		}
		else {
			temp->coef = pB->coef; temp->exp = pB->exp;
			C = add(C, temp); pB = pB->link;
		}
	}
	while (pA) {
		POLY* temp = (POLY*)malloc(sizeof(POLY));
		temp->coef = pA->coef; temp->exp = pA->exp; temp->link = NULL;
		C = add(C, temp); pA = pA->link;
	}
	while (pB) {
		POLY* temp = (POLY*)malloc(sizeof(POLY));
		temp->coef = pB->coef; temp->exp = pB->exp; temp->link = NULL;
		C = add(C, temp); pB = pB->link;
	}
	return C;
}

POLY* mulPoly(POLY* A, POLY* B) {
	int temp_res[201] = { 0 };
	for (POLY* pA = A; pA != NULL; pA = pA->link) {
		for (POLY* pB = B; pB != NULL; pB = pB->link) {
			temp_res[pA->exp + pB->exp] += pA->coef * pB->coef;
		}
	}
	POLY* D = NULL;
	for (int i = 200; i >= 0; i--) {
		if (temp_res[i] != 0) {
			POLY* temp = (POLY*)malloc(sizeof(POLY));
			temp->coef = temp_res[i]; temp->exp = i; temp->link = NULL;
			D = add(D, temp);
		}
	}
	return D;
}

void del(POLY* head) {
	POLY* p = head;
	while (p) {
		POLY* next = p->link;
		free(p);
		p = next;
	}
}


int main(void) {
	POLY* a = NULL; // a(x) = 3x5 + 4x3 - 2x2 + 1x + 7
	POLY* b = NULL; // b(x) = 4x3 + 2x2 - 6x - 3
	POLY* c = NULL, * d = NULL, * tmp = NULL; //for result

	//A 초기화 a(x) = 3x5 + 4x3 - 2x2 + 1x + 7
	tmp = (POLY*)malloc(sizeof(POLY));
	if (tmp == NULL) { printf("Memory Allocation Error"); exit(-1); }
	tmp->coef = 3; tmp->exp = 5; tmp->link = NULL;
	a = add(a, tmp);
	tmp = (POLY*)malloc(sizeof(POLY));
	if (tmp == NULL) { printf("Memory Allocation Error"); exit(-1); }
	tmp->coef = 4; tmp->exp = 3; tmp->link = NULL;
	a = add(a, tmp);
	tmp = (POLY*)malloc(sizeof(POLY));
	if (tmp == NULL) { printf("Memory Allocation Error"); exit(-1); }
	tmp->coef = -2; tmp->exp = 2; tmp->link = NULL;
	a = add(a, tmp);
	tmp = (POLY*)malloc(sizeof(POLY));
	if (tmp == NULL) { printf("Memory Allocation Error"); exit(-1); }
	tmp->coef = 1; tmp->exp = 1; tmp->link = NULL;
	a = add(a, tmp);
	tmp = (POLY*)malloc(sizeof(POLY));
	if (tmp == NULL) { printf("Memory Allocation Error"); exit(-1); }
	tmp->coef = 7; tmp->exp = 0; tmp->link = NULL;
	a = add(a, tmp);
	printPoly("a(x)", a);
	//B 초기화 b(x) = 4x3 + 2x2 - 6x - 3
	tmp = (POLY*)malloc(sizeof(POLY));
	if (tmp == NULL) { printf("Memory Allocation Error"); exit(-1); }
	tmp->coef = 4; tmp->exp = 3; tmp->link = NULL;
	b = add(b, tmp);
	tmp = (POLY*)malloc(sizeof(POLY));
	if (tmp == NULL) { printf("Memory Allocation Error"); exit(-1); }
	tmp->coef = 2; tmp->exp = 2; tmp->link = NULL;
	b = add(b, tmp);
	tmp = (POLY*)malloc(sizeof(POLY));
	if (tmp == NULL) { printf("Memory Allocation Error"); exit(-1); }
	tmp->coef = -6; tmp->exp = 1; tmp->link = NULL;
	b = add(b, tmp);
	tmp = (POLY*)malloc(sizeof(POLY));
	if (tmp == NULL) { printf("Memory Allocation Error"); exit(-1); }
	tmp->coef = -3; tmp->exp = 0; tmp->link = NULL;
	b = add(b, tmp);
	printPoly("b(x)", b);
	// 다항식 합
	c = addPoly(a, b);
	printPoly("c(x) = a(x) + b(x) ", c);
	// 다항식 곱
	d = mulPoly(a, b);
	printPoly("d(x) = a(x) x b(x) ", d);
	// 연결리스트 삭제
	del(a); del(b); del(c); del(d);
	return 0;
}
#endif
