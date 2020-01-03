#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<iostream>
#include <unistd.h>
#include <cstdlib>
#include <time.h>
#include <ctime>

using namespace std;

struct Node{
	int data;
	struct Node* prev;
	struct Node* next;
};

struct Node* newNode(int data){
	struct Node* N = (struct Node*)malloc(sizeof(struct Node));
	N->data = data;
	N->prev = NULL;
	N->next = NULL;
	return(N);
}

struct List{
	struct Node* head;
	struct Node* tail;
};

struct List* newList(void){
	struct List* L = (struct List*)malloc(sizeof(struct List));
	L->head = NULL;
	L->tail = NULL;
	return(L);
}

int length(struct List* L){
	int size = 0;
	struct Node* N = L->head;
	while(N != NULL){
		size = size + 1;
		N = N->next;
	}
	return(size);
}

int frontValue(struct List* L){
	if(L->head != NULL){
		return(L->head->data);
	}
	cout << "ERROR: attempted to call frontValue() on an empty list\n";
	return -1;
}

int backValue(struct List* L){
	if(L->tail != NULL){
		return(L->tail->data);
	}
	cout << "ERROR: attempted to call backValue() on an empty list\n";
	return -1;
}

int getValue(struct Node* N){
	return(N->data);
}

struct Node* getFront(struct List* L){
	return(L->head);
}

struct Node* getBack(struct List* L){
	return(L->tail);
}

struct Node* getNextNode(struct Node* N){
	if(N->next == NULL){
		N = NULL;
		return N;
	}
	return(N->next);
}

struct Node* getPrevNode(struct Node* N){
	if(N->prev == NULL){
		N = NULL;
		return N;
	}
	return(N->prev);
}

void prepend(struct List* L, int data){
	struct Node* N = newNode(data);
	if(L->head == NULL){
		L->head = N;
		L->tail = N;
		return;
	}
	L->head->prev = N;
	N->next = L->head;
	N->prev = NULL;
	L->head = N;
	return;
}

void append(struct List* L, int data){
	struct Node* N = newNode(data);
	//if first Node in List
	if(L->tail == NULL){
		L->head = N;
		L->tail = N;
		return;
	}
	else{
		L->tail->next = N;
		N->prev = L->tail;
		N->next = NULL;
		L->tail = N;
		return;
	}
}

void deleteNode(struct List* L, struct Node* N){
	if(N == NULL){
		return;
	}
	if(N == L->head && N == L->tail){
		free(N);
		N = NULL;
	}
	else if(N == L->head && N != L->tail){
		L->head = N->next;
		free(N);
		N = NULL;
	}
	else if(N != L->head && N == L->tail){
		L->tail = N->prev;
		L->tail->next = NULL;
		free(N);
		N = NULL;
	}
	else{
		N->prev->next = N->next;
		N->next->prev = N->prev;
		free(N);
		N = NULL;
	}
}

void deleteFront(struct List* L){
	struct Node* front = getFront(L);
	deleteNode(L, front);
	return;
}

void deleteBack(struct List* L){
	struct Node* back = getBack(L);
	deleteNode(L, back);
	return;
}

void printList(struct List* L){
	int value, toPrint;
	int size = length(L);
	// struct Node* N = getBack(L);
	struct Node* N = getFront(L);
	for(int i = 1; i < size; i++){
		toPrint = getValue(N);
		if(toPrint > 9){
			cout << toPrint << ", ";
		}
		else{
			cout << toPrint << " , ";
		}
		N = N->next;
	}
	cout << getValue(N) << "\n";
	return;
}

void moveToFront(struct List* L, struct Node* N){
	if(N == L->head){
		return;
	}
	if(N == L->tail){
		N->prev->next = NULL;
		L->tail = N->prev;
		N->next = L->head;
		N->prev = NULL;
		L->head = N;
	}
	else{
		N->next->prev = N->prev;
		N->prev->next = N->next;
		N->next = L->head;
		L->head->prev = N;
		L->head = N;
		N->prev = NULL;
	}
	return;
}

// perceived problem: you are calling ->next/prev too much and
//	seg faulting, other function work fine
// void shuffle(struct List* L){
// 	if(length(L) < 4){
// 		cout << "ERROR: the deck you are trying to shuffle is too small\n";
// 		return;
// 	}
// 	int twoCards, noCards, counter;
// 	struct Node* pile1;
// 	struct Node* pile2;

// 	srand(time(0));
// 	int random = rand() % 7;
// 	random = random + 6;

// 	for(int i = 0; i < random; i++){
// 		counter = 1;
// 		pile1 = getFront(L);
// 		pile2 = getBack(L);
// 		// cout << "   1\n";
// 		while(counter < length(L)/2){
// 			pile2 = pile2->prev;
// 			counter = counter + 1;
// 		}
// 		// cout << "   2\n" << "   pile1->data = " << pile1->data << "\n   pile2->data = " << pile2->data << "\n";
// 		//pile1 = top card of first half of deck
// 		//pile2 = first half of second half of deck
// 		int pile1index = 1;
// 		int pile2index = counter + 1;
// 		for(int j = 0; j < counter; j++){
// 			// cout << "      j = " << j << "\n";
// 			twoCards = rand() % 4;
// 			if(pile1->next == NULL){
// 				// cout << "   pile1->next = NULL, pile1->data = " << pile1->data << "\n";
// 				break;
// 			}
// 			// cout << "         3\n";
// 			if(pile2->next == NULL){
// 				// cout << "   pile2->next = NULL, pile2->data = " << pile2->data << "\n";
// 				break;
// 			}
// 			// cout << "         3.3\n";
// 			pile1 = pile1->next;
// 			// cout << "         3.5\n";
// 			// cout << "         pile1 = " << pile1->data << "\n         ";
// 			printList(L);
// 			// cout << "         pile1->prev = " << pile1->prev->data << "\n";
// 			moveToFront(L, pile1->prev);
// 			// cout << "         3.7\n";
// 			if(pile1->next == NULL){
// 				// cout << "   pile1->next = NULL, pile1->data = " << pile1->data << "\n";
// 				break;
// 			}
// 			// cout << "         4\n";
// 			if(twoCards == 0){
// 				pile1 = pile1->next;
// 				moveToFront(L, pile1->prev);
// 			}
// 			sleep(0.1);

// 			twoCards = rand() % 4;
// 			pile2 = pile2->next;
// 			moveToFront(L, pile2->prev);

// 			if(pile2->next == NULL){
// 				// cout << "   pile2->next = NULL, pile2->data = " << pile2->data << "\n";
// 				break;
// 			}
// 			if(twoCards == 0){
// 				pile1 = pile1->next;
// 				moveToFront(L, pile1->prev);
// 			}
// 			sleep(0.2);
// 		}
// 		// moveToFront(L,L->tail);
// 		// cout << "   L->head->next = " << L->head->next->data << "\n";
// 		printList(L);
// 	}

// 	return;
// }

//common causes of segfault: calling N->prev/next
//	on front/back of list respectivly
int main(int argc, char const *argv[]){
	
	struct List* L = newList();
	for(int i = 0; i < 10; i++){
		append(L, i);
	}
	printList(L);
	append(L, 7);
	append(L, 7);
	append(L, 7);
	append(L, 7);
	moveToFront(L, L->tail);
	moveToFront(L, L->head);
	shuffle(L);shuffle(L);shuffle(L);
	shuffle(L);
	// printList(L);

	return 1;
}









// void insertBefore(List L, int index, int data){
// 	int counter = 1;
// 	int size = length(L);
// 	Node N = getFront(L);
// 	if(index > size || index < 0){
// 		cout << "ERROR: tried to insert a node to an index larger than list\n";
// 		return;
// 	}
// 	while(counter != index){
// 		N = N->next;
// 		counter = counter + 1;
// 	}
// 	Node temp = newNode(data);
// 	N->prev->next = temp;
// 	temp->next = N;
// 	temp->prev = N->prev;
// 	N->prev = temp;
// 	return;
// }

// void insertAfter(List L, int index, int data){
// 	int counter = 1;
// 	int size = length(L);
// 	Node N = getFront(L);
// 	if(index > size || index < 0){
// 		cout << "ERROR: tried to insert a node to an index larger than list\n";
// 		return;
// 	}
// 	while(counter != index){
// 		N = N->next;
// 		counter = counter + 1;
// 	}
// 	Node temp = newNode(data);
// 	N->next->prev = temp;
// 	temp->next = N->next;
// 	temp->prev = N;
// 	N->next = temp;
// 	return;
// }

// void clear(List L){
// 	if(L == NULL){
// 		cout << "ERROR: tried to clear a NULL list\n";
// 		return;
// 	}
// 	if(L->head == NULL && L->tail == NULL){
// 		cout << "ERROR: tried to clear a list with no Node Objects\n";
// 		return;
// 	}
// 	while(getFront(L) != NULL){
// 		deleteFront(L);
// 	}
// 	return;
// }

// void freeList(List* pL){
// 	clear(*pL);
// 	free(*pL);
// 	pL = NULL;
// }