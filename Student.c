#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "define.h"
#include "Book.h"
#include "Student.h"

void display_student(Student s) {
	printf("Name: %s\n", s.name);
	printf("ID: %s\n", s.ID);
	printf("Date of birth: %d/%d/%d\n", s.date_Of_Birth.day, s.date_Of_Birth.month, s.date_Of_Birth.year);
	printf("ISBN issued book: %lld\n", s.issuedBookISBN);
	printf("Fine: %.2lf\n", s.fine);
}

void modify_student(Student* s) {
	printf("Enter to continue...\n");  getchar();
	printf("Name: "); fgets(s->name, 50, stdin); s->name[strcspn(s->name, "\n")] = 0; // delete '\n' in the end
	printf("ID: "); fgets(s->ID, 10, stdin); s->ID[strcspn(s->ID, "\n")] = 0;
	printf("Date of birth:\nDay: "); scanf_s("%d", &s->date_Of_Birth.day);
	printf("Month: "); scanf_s("%d", &s->date_Of_Birth.month);
	printf("Year: "); scanf_s("%d", &s->date_Of_Birth.year);
}

void set_fine(Student* s, double newFine) {
	s->fine = newFine;
}

void pay_fine(Student* s) {
	printf("Current fine: %.2lf\n", s->fine);
	if (s->fine >= 0) {
		if (s->fine == 0) {
			printf("You have no fine to pay.\n");
		} else {
			double money;
			printf("Enter money: "); scanf_s("%lf", &money);
			if (money >= s->fine) {
				double change = money - s->fine;
				if (change == 0) {
					printf("Fine has been paid.\n");
				}
				else {
					printf("Your change: %.2lf\n", change);
				}
				s->fine = 0;
			}
			else {
				printf("You have entered not enough money to pay fine.\n");
			}
		}
	}
}

void request_book_issue(Student *s) {
	if (s->issuedBookISBN != 0) {
		printf("You have currently issued another book.\nPlease return the book issue and pay fine (if you do) before issuing another book.\n");
	}
	else {
		long long issued_ISBN;
		int found = 0, flag = 0;
		printf("Enter the ISBN: "); scanf_s("%lld", &issued_ISBN);
		// Look for matching ISBN in Book database
		FILE* f = fopen(BOOK_DIR, "r+");
		if (f == NULL) {
			fprintf(stderr, "Error opening file.");
			exit(EXIT_FAILURE);
		}
		else {
			Book issued_book;
			while (fread(&issued_book, sizeof(Book), 1, f) != NULL) {
				if (issued_book.ISBN == issued_ISBN) {
					flag = 1;
					if (issued_book.status == 1) {
						found = 1;
						printf("The issued book information:\n");
						display_book(issued_book);
						// set Student -> ISBN
						s->issuedBookISBN = issued_ISBN;
						// set Book -> issued
						set_status_issued(&issued_book);
						// overwrite the issued book in Book database
						fseek(f, -1 * sizeof(Book), SEEK_CUR);
						fwrite(&issued_book, sizeof(Book), 1, f);
						printf("Book issued!\nWarning: You have 30 days before the due date. After due date, you will have to pay fine 10000 dong/day.\n");
						break;
					}
					else {
						printf("The book has been issued by another student.\n");
						break;
					}
				}
			}
			if (!found && !flag) {
				printf("Invalid ISBN.\n");
			}
			fclose(f);
		}
	}
}

void return_book_issue(Student* s) {
	// check if student actually borrowed the book
	if (s->issuedBookISBN == 0) {
		printf("You haven't issued any book yet.\n");
	}
	else {
		long long issued_ISBN;
		int found = 0, flag = 0;
		printf("Enter the ISBN: "); scanf_s("%lld", &issued_ISBN);
		// Look for matching ISBN in Book database
		FILE* f = fopen(BOOK_DIR, "r+");
		if (f == NULL) {
			fprintf(stderr, "Error opening file.");
			exit(EXIT_FAILURE);
		}
		else {
			Book issued_book;
			while (fread(&issued_book, sizeof(Book), 1, f) != NULL) {
				if (issued_book.ISBN == issued_ISBN) {
					flag = 1;
					if (s->issuedBookISBN == issued_book.ISBN) {
						if (issued_book.status == 2) {
							found = 1;
							printf("Return the book...\n");
							// set Student ISBN -> 0
							s->issuedBookISBN = 0;
							// set Book -> available
							set_status_available(&issued_book);
							// overwrite the book in Book database
							fseek(f, -1 * sizeof(Book), SEEK_CUR);
							fwrite(&issued_book, sizeof(Book), 1, f);
							printf("Return complete!\n");
							break;
						}
						else {
							printf("The book is already available.\n");
							break;
						}
					}
					else {
						printf("The book has been issued by another student.\n");
					}
				}
			}
			if (!found && !flag) {
				printf("Invalid ISBN.\n");
			}
			fclose(f);
		}
	}
}