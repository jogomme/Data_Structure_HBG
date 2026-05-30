#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<random>

using namespace std;

#define PROB 2 // 각각의 문제를 구현하고 해당 문제 번호를 변경하여 테스트
#if PROB == 1
// 1번 문제를 해결하기 위한 프로그램 작성

struct Time
{
	const char* day;
	int period;
};

struct schdule
{
	int tm;
	Time time[10];
};

struct Data
{
	char subject[50];
	char name[50];

	schdule schdule;
};

struct deQueue
{
	int rear;
	int front;

	int capacity;

	Data* data;
};

void error(const char* message)
{
	cout << message << '\n';
	exit(2025180028);
}

void init_dequeue(deQueue* dq, int size)
{
	dq->rear = dq->front = 0;

	dq->capacity = size + 1;

	dq->data = new Data[dq->capacity];

}

int isFull(deQueue* dq)
{
	return ((dq->rear + 1 ) % dq->capacity == dq->front);
}

int isEmpty(deQueue* dq)
{
	return (dq->front == dq->rear);
}

void add_front(deQueue* dq, Data data)
{
	if (isFull(dq)) {
		error("큐가 포화상태 입니다. by add_front");
	}
	dq->data[dq->front] = data;

	for (int i = 0; i < data.schdule.tm; ++i) {
		dq->data[dq->front].schdule.time->day = data.schdule.time->day;
		dq->data[dq->front].schdule.time->period = data.schdule.time->period;
	}
	dq->front = (dq->front - 1 + dq->capacity) % dq->capacity;

	

}

void add_rear(deQueue* dq, Data data)
{
	if (isFull(dq)) {
		error("큐가 포화상태 입니다.by add_rear");
	}

	dq->rear = (dq->rear + 1) % dq->capacity;

	dq->data[dq->rear] = data;
}

Data delete_front(deQueue* dq)
{
	if (isEmpty(dq)) {
		error("큐가 공백상태 입니다. by delete_front");
	}

	dq->front = (dq->front + 1) % dq->capacity;

	return dq->data[dq->front];
}

Data delete_rear(deQueue* dq)
{
	if (isEmpty(dq)) {
		error("큐가 공백상태 입니다. by delete_rear");
	}

	dq->rear = ((dq->rear - 1 + dq->capacity) % dq->capacity);

	return dq->data[dq->rear];
}

void printDeQue(deQueue* q)
{

	printf("DEQUE(front=%d rear=%d) = ", q->front, q->rear);
	if (!isEmpty(q)) {
		int i = q->front;
		do {
			i = (i + 1) % (q->capacity);

			cout << "교과목 명 : " << q->data[i].subject;
			cout << " 담당 교수 : " << q->data[i].name;
			cout << ", 수업 시간 : ";
			
			for (int j = 0; j < q->data->schdule.tm; ++j) {
				cout  << q->data->schdule.time[j].day<<"요일 " << q->data[i].schdule.time[j].period << " 교시 ";
			}
			cout << '\n';
			
			if (i == q->rear)
				break;
		} while (i != q->front);
	}
	printf("\n");
}

int main()
{
	deQueue queue;
	Data data1 = { "자료구조","오황석", {4, {"화", 1, "화", 2, "수", 1, "수", 2}} };
	Data data2 = { "컴퓨터구조","김경철",{4, {"월", 3, "월", 4, "목", 6, "목", 7}} };
	Data data3 = { "선형대수","이용희",{3, {"월", 8, "월", 9, "금", 3}} };

	init_dequeue(&queue, 3);
	printDeQue(&queue);
	add_front(&queue, data1); printDeQue(&queue);
	add_rear(&queue, data2); printDeQue(&queue);
	add_front(&queue, data3); printDeQue(&queue);
	delete_rear(&queue); printDeQue(&queue);
	delete_front(&queue); printDeQue(&queue);
	delete_front(&queue); printDeQue(&queue);
	delete_rear(&queue); printDeQue(&queue);

}

#elif PROB == 2
// 2번 문제를 해결하기 위한 프로그램 작성

#define WORK_TIME 10000

random_device rd;
mt19937 gen(rd());
uniform_int_distribution<int> menu(0, 4);

struct Data
{
	int menu;
	int OrderTime;
	int processing_time;
};

struct DeQue
{
	int rear;
	int front;
	int capacity;

	Data* data;
};

void error(const char* message)
{
	cout << message << '\n';
	exit(2025180028);
}

void initQue(DeQue* dq, int Size)
{
	dq->rear = dq->front = 0;
	dq->capacity = Size + 1;

	dq->data = new Data[dq->capacity]{};
}

int isFull(DeQue* dq)
{
	return ((dq->rear + 1) % dq->capacity == dq->front);
}

int isEmpty(DeQue* dq)
{
	return (dq->front == dq->rear);
}

void AddFront(DeQue* dq, Data data)
{
	if (isFull(dq)) {
		error("큐가 포화상태 입니다 by AddFront");
	}

	dq->data[dq->front] = data;
	dq->front = (dq->front - 1 + dq->capacity) % dq->capacity;

}

void AddRear(DeQue* dq, Data data)
{
	if (isFull(dq)) {
		error("큐가 포화상태 입니다 by AddRear");
	}

	dq->rear = (dq->rear + 1) % dq->capacity;

	dq->data[dq->rear] = data;

}

Data DeleteFront(DeQue* dq)
{
	if (isEmpty(dq)) {
		error("큐가 공백상태 입니다. by DeleteFront");
	}

	dq->front = (dq->front + 1) % dq->capacity;

	return dq->data[dq->front];
}

Data DeleteRear(DeQue* dq)
{
	if (isEmpty(dq)) {
		error("큐가 공백상태 입니다. by DeleteRear");
	}
	int pre = dq->rear;

	dq->rear = (dq->rear - 1 + dq->capacity) % dq->capacity;

	return dq->data[pre];
	
}

int isbusyServer1(Data* data)
{
	return (data->processing_time > 0);
}

int isbusyServer2(Data* data)
{
	return (data->processing_time > 0);
}

int main()
{
	cout << "큐 의 갯수 : ";
	int Size{};
	cin >> Size;
	DeQue Que;
	initQue(&Que, Size);

	Data server1{ -1,0,0 }, server2{-1,0,0};

	// 메뉴 몇 번 왔는지 세기
	int CountMenu[5]{};

	int time{};

	// 누적 대기시간
	double AveDelayTime[5]{};
	
	int count[5]{};

	// 거절된 수
	int RejectOrder{};

	// 노는 시간
	int NoneWorkTime[2]{};

	// 총 딜레이 시간
	int TotalDelayTime[5]{};

	while (time < WORK_TIME) {
		if (time % 5 == 0) { // 새로운 손님 5시간 마다 와서 메뉴 주문
			if (!isFull(&Que)) {

				Data order;
				order.menu = menu(gen);
				order.OrderTime = time;

				switch (order.menu) {
				case 0:
					order.processing_time = 10;
					break;
				case 1:
					order.processing_time = 15;
					break;
				case 2:
					order.processing_time = 20;
					break;
				case 3:
					order.processing_time = 25;
					break;
				case 4:
					order.processing_time = 30;
					break;
				}


				AddRear(&Que, order);
			}
			else {
				RejectOrder++;
			}
		}
		
		if (!isbusyServer1(&server1)) {
			if (!isEmpty(&Que)) {
				server1 = DeleteFront(&Que);
			}
			else {
				NoneWorkTime[0]++;
			}
		}
		else if (isbusyServer1(&server1)) {
			server1.processing_time -= 1;
			if (server1.processing_time == 0) {
				CountMenu[server1.menu]++;
				AveDelayTime[server1.menu] += time - server1.OrderTime;
			}
		}
		
		if (!isbusyServer2(&server2)) {
			if (!isEmpty(&Que)) {
				server2 = DeleteFront(&Que);
			}
			else {
				NoneWorkTime[1]++;
			}
		}
		else if (isbusyServer2(&server2)) {
			server2.processing_time -= 1;
			if (server2.processing_time == 0) {
				CountMenu[server2.menu]++;
				AveDelayTime[server2.menu] += time - server2.OrderTime;
			}
		}
		time++;

		//if (isbusyServer1(&server1)) {
		//	server1.processing_time -= 1;
		//}
		//if (isbusyServer2(&server2)) {
		//	server2.processing_time -= 1;
		//}

	}


	printf("=========== Results ============\n");
	for (int i = 0; i < 5; i++) {
		TotalDelayTime[i] = AveDelayTime[i];
		AveDelayTime[i] = AveDelayTime[i] / CountMenu[i];
		printf("MENU %d %d개 서비스, 누적대기시간 %d, 평균서비스시간 %f\n", i, CountMenu[i], TotalDelayTime[i],AveDelayTime[i]);
	}
	printf("취소된 주문 %d 개\n",RejectOrder);
	cout << "서버 1과 서버 2의 휴식 시간 : " << NoneWorkTime[0] << ", " << NoneWorkTime[1] << '\n';
	printf("================================\n");
	
}
#endif