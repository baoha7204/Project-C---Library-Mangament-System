#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "define.h"
#include "Student.h"
#include "AccountDatabase.h"
#include "Librarian.h"

void issue_book() {
	do {
		char searching_ID[10];
		int found = 0;
		printf("Enter the ID: "); fgets(&searching_ID, 10, stdin); searching_ID[strcspn(searching_ID, "\n")] = 0;
		// Look for matching ID in StudentAccount.dat
		FILE* f = fopen(STUDENTACCOUNT_DIR, "r+");
		if (f == NULL) {
			fprintf(stderr, "Error opening file.");
			exit(EXIT_FAILURE);
		}
		else {
			// check valid student
			StudentAccount searching;
			while (fread(&searching, sizeof(StudentAccount), 1, f) != NULL) {
				if (strcmp(searching.identity.ID, searching_ID) == 0) {
					found = 1;
					printf("Found student ID!\n");
					request_book_issue(&searching.identity);
					// overwrite data in StudentAccount.dat
					fseek(f, -1 * sizeof(StudentAccount), SEEK_CUR);
					fwrite(&searching, sizeof(StudentAccount), 1, f);
				}
			}
			if (!found) {
				printf("Invalid ID.\n");
			}
			fclose(f);
		}
		printf("Issue more book (y/n)? "); while (getchar() != '\n');
	} while (tolower(getchar()) == 'y');
}

void return_book() {
	do {
		char searching_ID[10];
		int found = 0;
		printf("Enter the ID: "); fgets(&searching_ID, 10, stdin); searching_ID[strcspn(searching_ID, "\n")] = 0;
		// search in Student.dat
		FILE* f = fopen(STUDENTACCOUNT_DIR, "r+");
		if (f == NULL) {
			fprintf(stderr, "Error opening file.");
			exit(EXIT_FAILURE);
		}
		else {
			// check valid student
			StudentAccount searching;
			while (fread(&searching, sizeof(StudentAccount), 1, f) != NULL) {
				if (strcmp(searching.identity.ID, searching_ID) == 0) {
					found = 1;
					printf("Found student ID!\n");
					return_book_issue(&searching.identity);
					// overwrite data in StudentAccount.dat
					fseek(f, -1 * sizeof(StudentAccount), SEEK_CUR);
					fwrite(&searching, sizeof(StudentAccount), 1, f);
				}
			}
			if (!found) {
				printf("Invalid ID.\n");
			}
			fclose(f);
		}
		printf("Return more book (y/n)? "); while (getchar() != '\n');
	} while (tolower(getchar()) == 'y');
}

void charge_fine() {
	do {
		char searching_ID[10];
		int found = 0;
		printf("Enter the ID: "); fgets(&searching_ID, 10, stdin); searching_ID[strcspn(searching_ID, "\n")] = 0;
		// search in Student.dat
		FILE* f = fopen(STUDENTACCOUNT_DIR, "r+");
		if (f == NULL) {
			fprintf(stderr, "Error opening file.");
			exit(EXIT_FAILURE);
		}
		else {
			// check valid student
			StudentAccount searching;
			while (fread(&searching, sizeof(StudentAccount), 1, f) != NULL) {
				if (strcmp(searching.identity.ID, searching_ID) == 0) {
					found = 1;
					printf("Found student ID!\n");
					// calculate fine
					int days;
					printf("Enter number of days: "); scanf_s("%d", &days);
					if (days > 30) {
						searching.identity.fine = (days - 30) * 10000;
						// overwrite data in StudentAccount.dat
						fseek(f, -1 * sizeof(StudentAccount), SEEK_CUR);
						fwrite(&searching, sizeof(StudentAccount), 1, f);
					}
					else {
						printf("Available for issue more.\n");
					}
				}
			}
			if (!found) {
				printf("Invalid ID.\n");
			}
			fclose(f);
		}
		printf("Charge fine more (y/n)? "); while (getchar() != '\n');
	} while (tolower(getchar()) == 'y');
}