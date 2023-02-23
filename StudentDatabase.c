#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "define.h"
#include "AccountDatabase.h"
#include "Student.h"
#include "StudentDatabase.h"

void add_student(Student* s) {
	modify_student(s);
	s->issuedBookISBN = 0;
	s->fine = 0;
}

void delete_student(Student* s) {
	do {
		char searching_ID[10];
		int found = 0;
		printf("Enter the ID: "); fgets(&searching_ID, 10, stdin); searching_ID[strcspn(searching_ID, "\n")] = 0;
		// Create a temporary file (temp file), write all the record of Student except the deleting one, then replace temp file with Student.dat
		FILE* f = fopen(ACCOUNT_DIR, "r");
		FILE* f_tmp = fopen(TEMP_DIR, "w");
		if (f == NULL || f_tmp == NULL) {
			fprintf(stderr, "Error opening file.");
			exit(EXIT_FAILURE);
		}
		else {
			Student searching_student;
			while (fread(&searching_student, sizeof(Student), 1, f) != NULL) {
				if (strcmp(searching_student.ID, searching_ID) == 0) {
					found = 1;
					printf("A student with requested ID has been found and deleted.\n");
				}
				else {
					fwrite(&searching_student, sizeof(Student), 1, f_tmp);
				}
			}
			if (!found) {
				printf("Invalid ID.\n");
			}
			fclose(f);
			fclose(f_tmp);

			remove(STUDENT_DIR);
			rename(TEMP_DIR, STUDENT_DIR);
		}
		printf("Delete more (y/n)? "); while (getchar() != '\n');
	} while (tolower(getchar()) == 'y');
}

void display_all_students() {
	FILE* f = fopen(ACCOUNT_DIR, "r+");
	if (f == NULL) {
		fprintf(stderr, "Error opening file.");
		exit(EXIT_FAILURE);
	}
	else {
		printf("All the students in the library:\n");
		Account a;
		a.identity = malloc(sizeof(Student));
		while (fread(&a, sizeof(Account), 1, f) != NULL) {
			display_student((Student*) a.identity);
			printf("--------------\n");
		}
		fclose(f);
	}
}

void search_student() {
	do {
		char searching_ID[10];
		int found = 0;
		printf("Enter the ID: "); fgets(&searching_ID, 10, stdin); searching_ID[strcspn(searching_ID, "\n")] = 0;
		// Look for matching ID in Student.identity in Account database
		FILE* f = fopen(ACCOUNT_DIR, "r+");
		if (f == NULL) {
			fprintf(stderr, "Error opening file.");
			exit(EXIT_FAILURE);
		}
		else {
			Account searching;
			searching.identity = malloc(sizeof(Student));
			while (fread(&searching, sizeof(Account), 1, f) != NULL) {
				Student* s = (Student*) searching.identity;
				if (strcmp(s->ID, searching_ID) == 0) {
					found = 1;
					display_student(s);
					break;
				}
			}
			if (!found) {
				printf("Invalid ID.\n");
			}
			fclose(f);
		}
		printf("Search more (y/n)? "); while (getchar() != '\n');
	} while (tolower(getchar()) == 'y');
}

void modify_Student() {
	do {
		char searching_ID[10];
		int found = 0;
		printf("Enter the ID: "); fgets(&searching_ID, 10, stdin); searching_ID[strcspn(searching_ID, "\n")] = 0;
		// Look for matching ID in Student.identity in Account database
		FILE* f = fopen(ACCOUNT_DIR, "r+");
		if (f == NULL) {
			fprintf(stderr, "Error opening file.");
			exit(EXIT_FAILURE);
		}
		else {
			Account modifying;
			modifying.identity = malloc(sizeof(Student));
			while (fread(&modifying, sizeof(Account), 1, f) != NULL) {
				Student* s = (Student*) modifying.identity;
				if (strcmp(s->ID, searching_ID) == 0) {
					found = 1;
					modify_student(s);
					update_account(modifying, fseek(f, -1 * sizeof(Account), SEEK_CUR));
					break;
				}
			}
			if (!found) {
				printf("Invalid ID.\n");
			}
			fclose(f);
		}
		printf("Modify more (y/n)? "); while (getchar() != '\n');
	} while (tolower(getchar()) == 'y');
}