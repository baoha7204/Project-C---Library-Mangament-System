#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Book.h"
#include "define.h"
#include "BookDatabase.h"

void add_book() {
	do {
		Book b;
		modify_book(&b);
		// add to file
		FILE* f = fopen(BOOK_DIR, "a+");
		if (f == NULL) {
			fprintf(stderr, "Error opening file.");
			exit(EXIT_FAILURE);
		}
		else {
			fwrite(&b, sizeof(Book), 1, f);
			fclose(f);
		}
		printf("Add more (y/n)? "); while (getchar() != '\n');
	} while (tolower(getchar()) == 'y');
}

void delete_book() {
	do {
		long long searching_ISBN;
		int found = 0;
		printf("Enter the ISBN: "); scanf_s("%lld", &searching_ISBN);
		// Create a temporary file (tmp file), write all the record of Book except the deleting one, then replace temp file with Book.dat
		FILE* f = fopen(BOOK_DIR, "r");
		FILE* f_tmp = fopen(TEMP_DIR, "w");
		if (f == NULL || f_tmp == NULL) {
			fprintf(stderr, "Error opening file.");
			exit(EXIT_FAILURE);
		}
		else {
			Book searching_book;
			while (fread(&searching_book, sizeof(Book), 1, f) != NULL) {
				if (searching_book.ISBN == searching_ISBN) {
					if (searching_book.status == 2) {
						printf("The book is currently issued. Cannot delete!\n");
						fclose(f);
						fclose(f_tmp);
						return;
					}
					else {
						found = 1;
						printf("The book with requested ISBN has been found and deleted.\n");
					}
				}
				else {
					fwrite(&searching_book, sizeof(Book), 1, f_tmp);
				}
			}
			if (!found) {
				printf("Invalid ISBN.\n");
			}
			fclose(f);
			fclose(f_tmp);

			remove(BOOK_DIR);
			rename(TEMP_DIR, BOOK_DIR);
		}
		printf("Delete more (y/n)? "); while (getchar() != '\n');
	} while (tolower(getchar()) == 'y');
}

void display_all_books() {
	FILE* f = fopen(BOOK_DIR, "r+");
	if (f == NULL) {
		fprintf(stderr, "Error opening file.");
		exit(EXIT_FAILURE);
	}
	else {
		printf("All the books in the library:\n");
		Book b;
		while (fread(&b, sizeof(Book), 1, f) != NULL) {
			display_book(b);
			printf("--------------\n");
		}
		fclose(f);
	}
}

void display_issued_books() {
	int counter = 0;
	FILE* f = fopen(BOOK_DIR, "r+");
	if (f == NULL) {
		fprintf(stderr, "Error opening file.");
		exit(EXIT_FAILURE);
	}
	else {
		printf("All the issued books in the library:\n");
		Book b;
		while (fread(&b, sizeof(Book), 1, f) != NULL) {
			if (b.status == 2) {
				counter++;
				display_book(b);
				printf("--------------\n");
			}
		}
		fclose(f);
		printf("Number of issued books: %d\n", counter);
	}
}

void display_available_books() {
	int counter = 0;
	FILE* f = fopen(BOOK_DIR, "r+");
	if (f == NULL) {
		fprintf(stderr, "Error opening file.");
		exit(EXIT_FAILURE);
	}
	else {
		printf("All the available books in the library:\n");
		Book b;
		while (fread(&b, sizeof(Book), 1, f) != NULL) {
			if (b.status == 1) {
				counter++;
				display_book(b);
				printf("--------------\n");
			}
		}
		fclose(f);
		printf("Number of available books: %d\n", counter);
	}
}

void search_book() {
	do {
		long long searching_ISBN;
		int found = 0;
		printf("Enter the ISBN: "); scanf_s("%lld", &searching_ISBN);
		// Look for matching ISBN in Book database
		FILE* f = fopen(BOOK_DIR, "r+");
		if (f == NULL) {
			fprintf(stderr, "Error opening file.");
			exit(EXIT_FAILURE);
		}
		else {
			Book searching_book;
			while (fread(&searching_book, sizeof(Book), 1, f) != NULL) {
				if (searching_book.ISBN == searching_ISBN) {
					found = 1;
					display_book(searching_book);
					break;
				}
			}
			if (!found) {
				printf("Invalid ISBN.\n");
			}
			fclose(f);
		}
		printf("Search more (y/n)? "); while (getchar() != '\n');
	} while (tolower(getchar()) == 'y');
}

void modify_Book() {
	do {
		long long modifying_ISBN;
		int found = 0;
		printf("Enter the ISBN: "); scanf_s("%lld", &modifying_ISBN);
		// Modify book in Book database
		FILE* f = fopen(BOOK_DIR, "r+");
		if (f == NULL) {
			fprintf(stderr, "Error opening file.");
			exit(EXIT_FAILURE);
		}
		else {
			Book modifying_book;
			while (fread(&modifying_book, sizeof(Book), 1, f) != NULL) {
				if (modifying_book.ISBN == modifying_ISBN) {
					found = 1;
					modify_book(&modifying_book);
					fseek(f, -1 * sizeof(Book), SEEK_CUR);
					fwrite(&modifying_book, sizeof(Book), 1, f);
					break;
				}
			}
			if (!found) {
				printf("Invalid ISBN.\n");
			}
			fclose(f);
		}
		printf("Modify more (y/n)? "); while (getchar() != '\n');
	} while (tolower(getchar()) == 'y');
}
