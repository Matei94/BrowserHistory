/*	Autor: Matei Razvan Madalin
		   Facultatea de Automatica si Calculatoare
		   Grupa 313CA
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Structures.h"

int main() {
	char *command = new char[50];
	char *p;
	int current_day = 0;
	int max_days = 30;
	int vector_dim;
	LinkedList<struct entry> deque;
	
	// Reading vector dimension;
	fgets(command, 20, stdin);
	vector_dim = atoi(command);
	deque.setLength(vector_dim);
	
	while(fgets(command, 50, stdin) != NULL) {
		// Ignore empty lines;
		if(strcmp(command, "\n")==0) {
			continue;
		}
		
		p = strtok(command, " \n");
		
		if(strcmp(command, "DAY_PASSES") == 0) {
			current_day++;
			
			while(1) { // Delete elements older than max_days;
				if(deque.pLast == NULL) break; // Empty list;
				if(deque.pLast->tail - deque.pLast->head == 1) { // Last vector is 'empty';
					deque.removeLast();
					continue;
				}
				if(deque.pLast->info[deque.pLast->tail - 1].day <= (current_day - max_days)) {
					deque.pop_back();
				}
				else break;
			}
		}
		
		if(strcmp(command, "ACCESS_PAGE") == 0) {
			struct entry myEntry;
			
			p = strtok(NULL, "\n");
			myEntry.day = current_day;
			myEntry.url = strdup(p);
			
			deque.push_front(myEntry);
		}
		
		if(strcmp(command, "CLEAR_RECENT_HISTORY") == 0) {
			int no_days;
			
			p = strtok(NULL, "\n");
			no_days = atoi(p);
			
			while(1) { // Delete elements newer than no_days;
				if(deque.pFirst == NULL) break; // Empty list;
				if(deque.pFirst->tail - deque.pFirst->head == 1) { // First vector is 'empty';
					deque.removeFirst();
					continue;
				}	
				if(deque.pFirst->info[deque.pFirst->head + 1].day > (current_day - no_days)) {
					deque.pop_front();
				}
				else break;
			}
		}
		
		if(strcmp(command, "SET_MAX_DAYS") == 0) {
			int no_days;
			
			p = strtok(NULL, "\n");
			no_days = atoi(p);
			
			max_days = no_days;
			
			while(1) { // Delete elements older than max_days;
				if(deque.pLast == NULL) break; // Empty list;
				if(deque.pLast->tail - deque.pLast->head == 1) { // Last vector is 'empty';
					deque.removeLast();
					continue;
				}
				if(deque.pLast->info[deque.pLast->tail - 1].day <= (current_day - max_days)) {
					deque.pop_back();
				}
				else break;
			}
		}
		
		if(strcmp(command, "SHOW_ENTRY") == 0) {
			int index;
			struct entry myEntry;
			
			p = strtok(NULL, "\n");
			index = atoi(p);
			
			printf("ENTRY %d:\n", index);
			
			myEntry = deque.get(index);
			printf("%d %s\n", myEntry.day, myEntry.url);
		}
		
		if(strcmp(command, "DELETE_ENTRY") == 0) {
			int index;
			
			p = strtok(NULL, "\n");
			index = atoi(p);
			
			deque.erase(index);
		}
		
		if(strcmp(command, "SHOW_HISTORY") == 0) {
			printf("HISTORY:\n");
			printf("Current day: %d\n", current_day);
			
			while(1) { // Delete elements older than max_days;
				if(deque.pLast == NULL) break; // Empty list;
				if(deque.pLast->tail - deque.pLast->head == 1) { // Last vector is 'empty';
					deque.removeLast();
					continue;
				}
				if(deque.pLast->info[deque.pLast->tail - 1].day <= (current_day - max_days)) {
					deque.pop_back();
				}
				else break;
			}
			
			deque.Sdump();
		}
		
		if(strcmp(command, "RECOVER_HISTORY") == 0) {
			struct entry myEntry;
			int no_reads, i;
			FILE *f;
			
			p = strtok(NULL, "\n");
			if((f = fopen(p, "r")) == NULL) {
				printf("Error 1: Could not open file!\n");
				continue;
			}
			
			fgets(command, 40, f);
			no_reads = atoi(command);
			
			for(i=0; i<no_reads; i++) {
				fgets(command, 40, f);
				
				// get day;
				p = strtok(command, " ");
				myEntry.day = atoi(p);
				
				// get url;
				p = strtok(NULL, "\n");
				myEntry.url = strdup(p);
				
				deque.push_back(myEntry);
			}
		} 	
	}
	
	delete[] command;
	return 0;
}

