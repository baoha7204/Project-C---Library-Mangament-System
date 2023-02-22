#ifndef LIBRARIAN_H 
#define LIBRARIAN_H 

#include "Date.h"

typedef struct Librarian {
	char name[50];
	char ID[50];
	Date date_Of_Birth;
} Librarian;

void modify_librarian(Librarian* lb);
void issue_book();
void return_book();
void charge_fine();

#endif