#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "define.h"
#include "AccountDatabase.h"
#include "Student.h"
#include "StudentDatabase.h"

void add_student(Student* s) {
	modify_student(s);
	s->issuedBookISBN = 0;
	s->fine = 0;
}

void delete_student() {
	do {
		char searching_ID[10];
		int found = 0;
		printf("Enter the ID: "); fgets(&searching_ID, 10, stdin); searching_ID[strcspn(searching_ID, "\n")] = 0;
		// Create a temporary file (temp file), write all the record of Student except the deleting one, then replace temp file with Student.dat
		FILE* f = fopen(STUDENTACCOUNT_DIR, "r");
		FILE* f_tmp = fopen(TEMP_DIR, "w");
		if (f == NULL || f_tmp == NULL) {
			fprintf(stderr, "Error opening file.");
			exit(EXIT_FAILURE);
		}
		else {
			StudentAccount searching;
			while (fread(&searching, sizeof(StudentAccount), 1, f) != NULL) {
				if (strcmp(searching.identity.ID, searching_ID) == 0) {
					if (searching.identity.issuedBookISBN != 0) {
						printf("The student is currently issuing a book. Cannot delete!\n");
						fclose(f);
						fclose(f_tmp);
						return;
					}
					else {
						found = 1;
						printf("A student with requested ID has been found and deleted. Please aware that deleting students also means deleting their account.\n");
					}
				}
				else {
					fwrite(&searching, sizeof(StudentAccount), 1, f_tmp);
				}
			}
			if (!found) {
				printf("Invalid ID.\n");
			}
			fclose(f);
			fclose(f_tmp);

			remove(STUDENTACCOUNT_DIR);
			rename(TEMP_DIR, STUDENTACCOUNT_DIR);
		}
		printf("Delete more (y/n)? "); while (getchar() != '\n');
	} while (tolower(getchar()) == 'y');
}

void display_all_students() {
	FILE* f = fopen(STUDENTACCOUNT_DIR, "r+");
	if (f == NULL) {
		fprintf(stderr, "Error opening file.");
		exit(EXIT_FAILURE);
	}
	else {
		printf("All the students in the library:\n");
		StudentAccount a;
		while (fread(&a, sizeof(StudentAccount), 1, f) != NULL) {
			display_student(a.identity);
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
		FILE* f = fopen(STUDENTACCOUNT_DIR, "r+");
		if (f == NULL) {
			fprintf(stderr, "Error opening file.");
			exit(EXIT_FAILURE);
		}
		else {
			StudentAccount searching;
			while (fread(&searching, sizeof(StudentAccount), 1, f) != NULL) {
				if (strcmp(searching.identity.ID, searching_ID) == 0) {
					found = 1;
					display_student(searching.identity);
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
		FILE* f = fopen(STUDENTACCOUNT_DIR, "r+");
		if (f == NULL) {
			fprintf(stderr, "Error opening file.");
			exit(EXIT_FAILURE);
		}
		else {
			StudentAccount modifying;
			while (fread(&modifying, sizeof(StudentAccount), 1, f) != NULL) {
				if (strcmp(modifying.identity.ID, searching_ID) == 0) {
					found = 1;
					modify_student(&modifying.identity);
					fseek(f, -1 * sizeof(StudentAccount), SEEK_CUR);
					fwrite(&modifying, sizeof(StudentAccount), 1, f);
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