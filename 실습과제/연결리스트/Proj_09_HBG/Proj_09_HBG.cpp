#define _CRT_SECURE_NO_WARNINGS


#include<iostream>

using namespace std;

// ----------------------------------------------------------------------------------
// 공통 함수 구현
// ----------------------------------------------------------------------------------
void print_playlist_menu(void)
{
	printf("\n\n---- Playlist Menu ---- \n");
	printf(" a : print all playlist \n");
	printf(" c : print current playlist\n");
	printf(" n : new playlist \n");
	printf(" d : delete playlist \n");
	printf(" > : next playlist \n");
	printf(" < : previous playlist \n");
	printf(" s : song menu \n");
	printf(" q : quit \n");
	return;
}

void print_song_menu(void)
{
	printf("\n\n---- Song Menu ---- \n");
	printf(" a : print all songs \n");
	printf(" c : print current song\n");
	printf(" n : add new song in playlist \n");
	printf(" d : delete current song \n");
	printf(" > : next song \n");
	printf(" < : previous song \n");
	printf(" b : quit \n");
	return;
}


// ----------------------------------------------------------------------------------
//  구조체 선언
// ----------------------------------------------------------------------------------
struct DSongNode
{
	char* sName;
	DSongNode* next;
	DSongNode* pre;
};

struct DPlaylistNode
{
	char* pName;
	DPlaylistNode* next;
	DPlaylistNode* pre;
	DSongNode* Nsong;
};

// ----------------------------------------------------------------------------------
// Song 구현
// ----------------------------------------------------------------------------------


void print_aSong(DPlaylistNode* head, DSongNode* CurList)
{
	if (head->Nsong == nullptr) {
		cout << "NULL" << '\n';
		return;
	}
	DSongNode* LeadList = head->Nsong->next;

	do {
		if (LeadList == CurList) {
			cout << " <- [ *" << LeadList->sName << "* ] -> ";
		}
		else {
			cout << " <- [ " << LeadList->sName << " ] -> ";
		}
		LeadList = LeadList->next;
	} while (LeadList != head->Nsong->next);
	cout << '\n';
}

void insert_nSongList(DPlaylistNode* head, const char* buf, DSongNode** CurList)
{
	DSongNode* newList{ new DSongNode };

	if (newList == nullptr) exit(2025180028);

	int len = strlen(buf) + 1;

	newList->sName = new char[len];

	strcpy(newList->sName, buf);

	if (head->Nsong == nullptr) {
		head->Nsong = newList;
		newList->next = newList;
		newList->pre = newList;
	}
	else {
		newList->next = head->Nsong->next;
		newList->pre = head->Nsong;
		head->Nsong->next->pre = newList;
		head->Nsong->next = newList;
	}

	head->Nsong = newList;
	(*CurList) = newList;
}

DSongNode* delete_cSong(DPlaylistNode* head, DSongNode** CurList)
{
	DSongNode* temp = (*CurList);

	if (head==nullptr || head->Nsong == nullptr || *CurList == nullptr) {
		return nullptr;
	}
	else if ((*CurList) == head->Nsong) {
		if (head->Nsong->next == head->Nsong) {
			delete[] temp->sName;
			delete temp;

			(*CurList) = nullptr;
			head->Nsong = nullptr;
		}
		else {
			head->Nsong = head->Nsong->next;
			(*CurList)->pre->next = (*CurList)->next;
			(*CurList)->next->pre = (*CurList)->pre;

			(*CurList) = (*CurList)->next;

			delete[] temp->sName;
			delete temp;
		}
	}
	else {
		(*CurList)->pre->next = (*CurList)->next;
		(*CurList)->next->pre = (*CurList)->pre;

		(*CurList) = (*CurList)->next;

		delete[] temp->sName;
		delete temp;
	}
	return head->Nsong;
}

void clearSong(DPlaylistNode* head)
{
	if (head == nullptr || head->Nsong == nullptr) return;

	DSongNode* curr = head->Nsong;

	// 원형을 단순 선형 연결 리스트처럼 끊기
	curr->pre->next = nullptr;

	while (curr != nullptr) {
		DSongNode* nextNode = curr->next;
		delete[] curr->sName;
		delete curr;
		curr = nextNode;
	}

	head->Nsong = nullptr;
}


void change_cSong(DSongNode** CurList,int num) 
{
	if ((*CurList) == nullptr) {
		return;
	}
	else if (num == 1) {
		*CurList = (*CurList)->next;
	}
	else if (num == 2) {
		(*CurList) = (*CurList)->pre;
	}
}

// ----------------------------------------------------------------------------------
// PlatList 구현
// ----------------------------------------------------------------------------------


void print_aPlaylist(DPlaylistNode* head, DPlaylistNode* CurList)
{
	if (head == nullptr) {
		cout << "NULL" << '\n';
		return;
	}
	DPlaylistNode* LeadList = head->next;

	do {
		if (LeadList == CurList) {
			std::cout << " <- [ *" << LeadList->pName << "* ] -> ";
		}
		else {
			cout << " <- [ " << LeadList->pName << " ] -> ";
		}
		LeadList = LeadList->next;
	} while (LeadList != head->next);
	cout << '\n';
}

void insert_nPlaylist(DPlaylistNode** head, const char* buf, DPlaylistNode** CurList)
{
	DPlaylistNode* newList{ new DPlaylistNode };

	if (newList == nullptr) exit(2025180028);

	int len = strlen(buf) + 1;
	
	newList->pName = new char[len];

	strcpy(newList->pName, buf);

	if ((*head) == nullptr) {
		(*head) = newList;
		newList->next = newList;
		newList->pre =	newList;
		
	}
	else {
		newList->next = (*head) ->next;
		newList->pre = (*head);
		(*head)->next->pre = newList;
		(*head)->next = newList;
	}

	newList->Nsong = nullptr;

	(*head) = newList;
	(*CurList) = newList;	
}

DPlaylistNode* delete_cPlaylist(DPlaylistNode** head, DPlaylistNode** CurList)
{
	DPlaylistNode* temp = *CurList;
	
	if (*head == nullptr) { 
		return nullptr; 
	}
	else if ((*CurList) == (*head)) {
		if ((*head)->next == (*head)) {
			clearSong(*CurList);

			delete[] temp->pName;
			delete temp;

			(*CurList) = nullptr;
			(*head) = nullptr;
		}
		else {
			(*head) = (*head)->next;
			(*CurList)->pre->next = (*CurList)->next;
			(*CurList)->next->pre = (*CurList)->pre;
			clearSong(*CurList);

			(*CurList) = (*CurList)->next;

			delete[] temp->pName;
			delete temp;
		}
	}
	else {
		(*CurList)->pre->next = (*CurList)->next;
		(*CurList)->next->pre = (*CurList)->pre;
		clearSong(*CurList);

		(*CurList) = (*CurList)->next;

		delete[] temp->pName;
		delete temp;
	}


	return (*head);
}

void change_cPlaylist(DPlaylistNode** CurList, int num)
{
	if ((*CurList) == nullptr) {
		return;
	}
	else if (num == 1) {
		*CurList = (*CurList)->next;
	}
	else if (num == 2) {
		(*CurList) = (*CurList)->pre;
	}
}



// ----------------------------------------------------------------------------------
// 초기화 함수
// ----------------------------------------------------------------------------------

// 헤드를 공백 헤드로 만드는 과정
void initList(DPlaylistNode** Phead, DSongNode** Shead)
{
	(*Phead) = new DPlaylistNode;
	(*Shead) = new DSongNode;

	(*Phead)->next = (*Phead);
	(*Phead)->pre = (*Phead);
	
	(*Shead)->next = (*Shead);
	(*Shead)->pre = (*Shead);
}

// ----------------------------------------------------------------------------------
int main(void)
// ----------------------------------------------------------------------------------
{
	DPlaylistNode* head = nullptr;
	char buf[30];
	
	// currentPlatlist 는 선택된 노래이다.
	DPlaylistNode* currentPlaylist = nullptr;

	DSongNode* currentSong = nullptr;
	char menu, sub_menu;

	//initList(&head, &currentSong);

	do {
		//printf("메뉴 선택");
		print_playlist_menu();
		printf("Select Menu : ");
		scanf(" %c", &menu);
		printf("--------------------------\n");
		printf("Selected playlist menu : %c \n", menu);
		switch (menu) {
		case 'a':
			print_aPlaylist(head, currentPlaylist);
			break;
		case 'c':
			if (currentPlaylist != nullptr){
				printf("Current playlist : %s\n", currentPlaylist->pName);
			}
			else {
				cout << "NULL" << '\n';
			}
			break;
		case 'n':
			printf("Playlist name : ");
			scanf("%s", buf);
			insert_nPlaylist(&head, buf, &currentPlaylist);
			print_aPlaylist(head, currentPlaylist);
			break;
		case 'd':
			delete_cPlaylist(&head, &currentPlaylist);
			print_aPlaylist(head, currentPlaylist);
			break;
		case '<':
			change_cPlaylist(&currentPlaylist, 2);
			print_aPlaylist(head, currentPlaylist);
			break;
		case '>':
			change_cPlaylist(&currentPlaylist, 1);
			print_aPlaylist(head, currentPlaylist);
			break;
		case 's':
			if (currentPlaylist == nullptr) {
				cout << "CurrentPlayList is NULL" << '\n' << "Pleas Make PlayList";
				break;
			}
			currentSong = currentPlaylist->Nsong;
			do {
				//printf("Cur PL : %s, Cur Song : %s \n",
				//	currentPlaylist->pName,
				//	currentSong->sName);
				print_song_menu();
				printf("Select Menu : ");
				scanf(" %c", &sub_menu);
				printf("Selected song menu : %c \n", sub_menu);
				switch (sub_menu) {
				case 'a':
					print_aSong(currentPlaylist, currentSong);
					break;
				case 'c':
					printf("current song : %s\n",
						currentSong->sName);
					break;
				case 'n':
					printf("Song name : ");
					scanf("%s", buf);
					insert_nSongList(currentPlaylist, buf,&currentSong);
					print_aSong(currentPlaylist, currentSong);
					break;
				case 'd':
					delete_cSong(currentPlaylist, &currentSong);
					print_aSong(currentPlaylist, currentSong);
					break;
				case '<':
					change_cSong(&currentSong, 2);
					print_aSong(currentPlaylist, currentSong);
					break;
				case '>':
					change_cSong(&currentSong, 1);
					print_aSong(currentPlaylist, currentSong);
					break;
				}
			} while (sub_menu != 'b');
			break;
		}
	} while (menu != 'q');
	return 0;
}