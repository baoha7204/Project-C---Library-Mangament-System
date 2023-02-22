#ifndef BOOK_H
#define BOOK_H

#include "Date.h"

typedef struct Book {
	char title[50];
	char author[50];
	long long ISBN; // key
	Date date_Publicaton;
	int status; // 1 = available, 2 = issued
} Book;

void display_book(Book b);
void modify_book(Book* b);
void set_status_available(Book* b);
void set_status_issued(Book* b);

#endif