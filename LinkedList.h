/* DEQUE implementat cu o 
   lista circulara dubla inlantuita 
   ce contine un vector in fiecare nod */

#ifndef __LINKEDLIST_H
#define __LINKEDLIST_H

template<typename T>
struct Node {
	T* info;
	int head, tail;
	struct Node *next, *prev;
};

template<typename T>
class LinkedList {
public:
	struct Node<T> *pFirst, *pLast;
	int length;
	
	//Constructor
	LinkedList() {
		pFirst = NULL;
		pLast = NULL;
	}
	
	//Destructor
	~LinkedList() { 
		struct Node<T> *aux1, *aux2;
		aux1 = pFirst;
		if(aux1 != NULL) {
			delete aux1->info;
		}
		else return;
		
		aux2 = pFirst->next;
		while(1) {
			if(aux2 != pFirst) {
				delete aux2->info;
			}
			else return;
			aux1 = aux2->next;
			if(aux1 != pFirst) {
				delete aux1->info;
			}
			else return;
			aux2 = aux1->next;
		}
	}
	
	void setLength(int n) {
		length = n;
	}
	
	void push_front(T x) {
		if(pFirst == NULL) { // Empty list;
			struct Node<T> *aux;
			aux = new struct Node<T>;
			aux->info = new T[length];
			
			aux->head = length-1;
			aux->tail = length-1;
			
			aux->info[aux->head] = x;
			(aux->head)--;
			(aux->tail)++;
			
			pFirst = aux;
			pLast = aux; 
			aux->prev = aux;
			aux->next = aux;
			return;
		}
		
		if(pFirst != NULL) { // NOT empty list;
			if(pFirst->head != -1) { // Not full list;
				pFirst->info[pFirst->head] = x;
				pFirst->head--;
				return;
			}
			else { // FULL list;
				struct Node<T> *aux;
				aux = new struct Node<T>;
				aux->info = new T[length];
			
				aux->head = length-1;
				aux->tail = length-1;
			
				aux->info[aux->head] = x;
				aux->head--;
				aux->tail++;
				
				pFirst->prev = aux;
				aux->next = pFirst;
				aux->prev = pLast;
				pFirst = aux;
				pLast->next = pFirst;
				return;
			}
		}
	}
	
	T pop_front() {
		if(pFirst == NULL) { // Empty list;
			printf("Error 1: List is empty\n");
			T x;
			return x;
		}
		
		if(pFirst != NULL) { // NOT empty list;
			if(pFirst->tail - pFirst->head != 1) { // pFirst vector is not empty;
				pFirst->head++;
				return pFirst->info[pFirst->head];
			}
			else { // pFirst vector is empty;
				removeFirst();
				pFirst->head++;
				return pFirst->info[pFirst->head];
			}
		}
	}
	
	void push_back(T x) {
		if(pLast == NULL) { // Empty list;
			struct Node<T> *aux;
			aux = new struct Node<T>;
			aux->info = new T[length];
			
			aux->head = 0;
			aux->tail = 0;
			
			aux->info[aux->tail] = x;
			aux->tail++;
			aux->head--;
			
			pFirst = aux;
			pLast = aux; 
			aux->prev = aux;
			aux->next = aux;
			return;
		}
		
		if(pLast != NULL) { // NOT empty list;
			if(pLast->tail != length) { // NOT full list;
				pLast->info[pLast->tail] = x;
				pLast->tail++;
				return;
			}
			else { // Full list;
				struct Node<T> *aux;
				aux = new struct Node<T>;
				aux->info = new T[length];
			
				aux->head = 0;
				aux->tail = 0;
			
				aux->info[aux->tail] = x;
				aux->tail++;
				aux->head--;
				
				pLast->next = aux;
				aux->prev = pLast;
				aux->next = pFirst;
				pLast = aux;
				pFirst->prev = pLast;
				return;
			}
		}
	}
	
	T pop_back() {
		if(pLast == NULL) { // Empty list;
			printf("Error 2: List is empty\n");
			T x;
			return x;
		}
		
		if(pLast != NULL) { // NOT empty list;
			if(pLast->tail - pLast->head != 1) { // pLast vector is not empty;
				pLast->tail--;
				return pLast->info[pLast->tail];
			}
			else { // pFirst vector is empty;
				removeLast();
				pLast->tail--;
				return pLast->info[pLast->tail];
			}
		}
	}
	
	T front() {
		if(pFirst == NULL) { // Empty list;
			printf("Error 3: list is empty!\n");
			T x;
			return x;
		}
		if(pFirst != NULL) { // Not empty list;
			if(pFirst->head != length-1) { // pFirst vector is not empty;
				return pFirst->info[pFirst->head + 1];
			}
			else { // pFirst vector is empty;
				return (pFirst->next)->info[pFirst->next->head + 1];
			}
		}
	}
	
	T back() {
		if(pLast == NULL) { // Empty list;
			printf("Error 4: list is empty!\n");
			T x;
			return x;
		}
		if(pLast != NULL) { // NOT empty list;
			if(pLast->tail != 0) { // pLast vector is not empty;
				return pLast->info[pLast->tail - 1];
			}
			else { // pFirst vector is empty;
				return (pLast->prev)->info[pLast->prev->tail - 1];
			}
		}
	}
	
	void erase(int position) {
		struct Node<T> *aux;
		aux = new struct Node<T>;
		int nr_elem, i;
		
		aux = pFirst;
		
		// get bucket;
		while(1) {
			nr_elem = aux->tail - aux->head - 1;
			if(nr_elem > position) { 
				break;
			}
			else {
				position = position - nr_elem;
				aux = aux->next;
			}
		}
		
		// erase entry;
		for(i = aux->head + position + 1; i <= aux->tail-2; i++) {
			aux->info[i] = aux->info[i+1];
		}
		aux->tail--;
	}
	
	T get(int position) {
		struct Node<T> *aux;
		aux = new struct Node<T>;
		int nr_elem;
		
		aux = pFirst;
		
		// get bucket;
		while(1) {
			nr_elem = aux->tail - aux->head - 1;
			if(nr_elem > position) { 
				break;
			}
			else {
				position = position - nr_elem;
				aux = aux->next;
			}
		}
		
		// return entry;
		return aux->info[aux->head + position + 1];
	}	
	
	void removeFirst() {
		if(pFirst == NULL) {
			printf("Error 5: List is empty!\n");
			return;
		}
		if(pFirst == pLast) { // 1 element;
			delete pFirst->info;
			delete pFirst;
			pFirst = NULL;
			pLast = NULL;
			return;
		}
		if(pFirst != pLast) { // More elements;
			struct Node<T> *aux;
			aux = pFirst;
			pFirst = aux->next;
			pFirst->prev = pLast;
			pLast->next = pFirst;
			delete aux->info;
			delete aux;
			return;
		}
	}
	
	void removeLast() {
		if(pFirst == NULL) {
			printf("Error 6: Queue is empty!\n");
			return;
		}
		if(pFirst == pLast) { // 1 element;
			delete pLast->info;
			delete pLast;
			pLast = NULL;
			pFirst = NULL;
			return;
		}
		if(pFirst != pLast) { // More elements;
			struct Node<T> *aux;
			aux = pLast;
			pLast = aux->prev;
			pLast->next = pFirst;
			pFirst->prev = pLast;
			delete aux->info;
			delete aux;
			return;
		}
	}
			
	int isEmpty() {
		if (pFirst == NULL) {
			return 1; // 1 = empty;
		}
		return 0;
	}
	
	void Sdump() { // Dump for _entry_ structure;
		int i;
		struct Node<T> *aux;
		
		if(isEmpty() == 1) {
			return;
		}

		aux = pFirst;
		do {
			for(i=0; i <= aux->head; i++) {
	//			printf("|X|");
			}
			for(i = (aux->head)+1; i < aux->tail; i++) {
				printf("%d %s", aux->info[i].day, aux->info[i].url);
				if(i != aux->tail - 1) {
					printf("\n");
				}
				if((i == aux->tail - 1) && (aux != pLast)) {
					printf("\n");
				}
			}
			for(i = (aux->tail); i<length; i++) {
	//			printf("|X|");
			}
			aux = aux->next;
		} while(aux != pFirst);
		
		printf("\n");
	}	
};

#endif //__LINKEDLIST_H

