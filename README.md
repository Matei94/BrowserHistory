BrowserHistory
==============

	***********************
	**** Tema 2 la SD *****
	*** Browser History ***
	***********************
	

In inplementarea temei a fost folosita structura de date numita _deque_.
Deque-ul a fost implementat in mod hibrid: fiecare nod contine un vector.

Operatii deque:
	
	push_front: Inserare la începutul structurii

	pop_front: Ștergere a primului element

	push_back: Inserare la finalul structurii

	pop_back: Ștergere a ultimului element

	front: Întoarce primul element

	back: Întoarce ultimul element

	erase: Se gaseste mai intai nodul(vectorul) in care se afla
	elementul de sters. Apoi se sterge mutand mai "sus"
	cu o pozitie elementele de "dedesubtul" pozitiei de sters.
	   
	get: Se gaseste mai intai nodul(vectorul) in care se afla
	ementul de intors. Se intoarce intrarea.
	 
	
Comenzi posibile:
		
	__DAY_PASSES__
Se incrementeaza current_day si se sterg intratile mai vechi de max_days zile.
Stergerea se face cu pop_back().

	__ACCESS_PAGE <URL>__
Se adauga la inceputul deque-ului structura entry formata din day si url.
Adaugarea se face cu push_front().

	__CLEAR_RECENT_HISTORY <NO_DAYS>__
Se sterg intrarile mai noi de no_days zile.
Stergerea se face cu pop_front().

	__SET_MAX_DAYS <NO_DAYS>__
Se modifica numarul maxim de zile max_days cu no_days.
Se sterg apoi intrarile mai vechi de max_days.
Stergerea se face cu pop_back().

	__SHOW_ENTRY <INDEX>__
Se gaseste intrarea de la INDEX cu ajutorul functiei get.
Se afiseaza intrarea.

	__DELETE_ENTRY <INDEX>__
Se sterge intrarea de la INDEX cu ajutorul functiei erase.

	__SHOW_HISTORY__
Se afiseaza intrarile din history si ziua curenta.

	__RECOVER_HISTORY <FILE_NAME>__
Din fisierul FILE_NAME se citesc intrarile si se adauga la history.
