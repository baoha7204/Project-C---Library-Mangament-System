#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Book.h"
#include "define.h"

void display_book(Book b) {
	printf("Title: %s\n", b.title);
	printf("Author: %s\n", b.author);
	printf("ISBN: %lld\n", b.ISBN);
	printf("Date of publication: %d/%d/%d\n", b.date_Publicaton.day, b.date_Publicaton.month, b.date_Publicaton.year);
	(b.status == 1) ? printf("Status: available\n") : printf("Status: issued\n");
}

void modify_book(Book* b) {
	printf("Enter to continue...\n");  getchar();
	printf("Title: "); fgets(b->title, 50, stdin); b->title[strcspn(b->title, "\n")] = 0;
	printf("Author: "); fgets(b->author, 50, stdin); b->author[strcspn(b->author, "\n")] = 0;
	printf("ISBN: "); scanf_s("%lld", &b->ISBN);
	printf("Date of publication:\nDay: "); scanf_s("%d", &b->date_Publicaton.day);
	printf("Month: "); scanf_s("%d", &b->date_Publicaton.month);
	printf("Year: "); scanf_s("%d", &b->date_Publicaton.year);
	do {
		printf("Status (1 = available, 2 = issued): "); scanf_s("%d", &b->status);
	} while (b->status != 1 && b->status != 2);
}

void set_status_available(Book* b) {
	b->status = 1;
}
void set_status_issued(Book* b) {
	b->status = 2;
}