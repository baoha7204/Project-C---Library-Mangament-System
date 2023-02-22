#include <stdio.h>
#include <stdlib.h>
#include "define.h"
#include "Student.h"
#include "Librarian.h"

void modify_librarian(Librarian* lb) {
	printf("Enter to continue...\n");  getchar();
	printf("Name: "); fgets(lb->name, 50, stdin); lb->name[strcspn(lb->name, "\n")] = 0; // delete '\n' in the end
	printf("ID: "); fgets(lb->ID, 10, stdin); lb->ID[strcspn(lb->ID, "\n")] = 0;
	printf("Date of birth:\nDay: "); scanf("%d", &lb->date_Of_Birth.day);
	printf("Month: "); scanf("%d", &lb->date_Of_Birth.month);
	printf("Year: "); scanf("%d", &lb->date_Of_Birth.year);
}

void issue_book() {
	char searching_ID[10];
	int found = 0;
	printf("Enter the ID: "); fgets(&searching_ID, 10, stdin); searching_ID[strcspn(searching_ID, "\n")] = 0;
	// search in Student.dat
	FILE* f = fopen(STUDENT_DIR, "r+");
	if (f == NULL) {
		fprintf(stderr, "Error opening file.");
		exit(EXIT_FAILURE);
	}
	else {
		// check valid student
		Student searching_student;
		while (fread(&searching_student, sizeof(Student), 1, f) != NULL) {
			if (strcmp(searching_student.ID, searching_ID) == 0) {
				found = 1;
				printf("Found student ID!\n");
				request_book_issue(&searching_student);
				// overwrite data in Student.dat
				fseek(f, -1 * sizeof(Student), SEEK_CUR);
				fwrite(&searching_student, sizeof(Student), 1, f);
				printf("Successfully update!\n");
			}
		}
		if (!found) {
			printf("Invalid ID.\n");
		}
	}
}

void return_book() {
	char searching_ID[10];
	int found = 0;
	printf("Enter the ID: "); fgets(&searching_ID, 10, stdin); searching_ID[strcspn(searching_ID, "\n")] = 0;
	// search in Student.dat
	FILE* f = fopen(STUDENT_DIR, "r+");
	if (f == NULL) {
		fprintf(stderr, "Error opening file.");
		exit(EXIT_FAILURE);
	}
	else {
		// check valid student
		Student searching_student;
		while (fread(&searching_student, sizeof(Student), 1, f) != NULL) {
			if (strcmp(searching_student.ID, searching_ID) == 0) {
				found = 1;
				printf("Found student ID!\n");
				request_book_issue(&searching_student);
				// overwrite data in Student.dat
				fseek(f, -1 * sizeof(Student), SEEK_CUR);
				fwrite(&searching_student, sizeof(Student), 1, f);
				printf("Successfully update!\n");
			}
		}
		if (!found) {
			printf("Invalid ID.\n");
		}
	}
}

void charge_fine() {
	char searching_ID[10];
	int found = 0;
	printf("Enter the ID: "); fgets(&searching_ID, 10, stdin); searching_ID[strcspn(searching_ID, "\n")] = 0;
	// search in Student.dat
	FILE* f = fopen(STUDENT_DIR, "r+");
	if (f == NULL) {
		fprintf(stderr, "Error opening file.");
		exit(EXIT_FAILURE);
	}
	else {
		// check valid student
		Student searching_student;
		while (fread(&searching_student, sizeof(Student), 1, f) != NULL) {
			if (strcmp(searching_student.ID, searching_ID) == 0) {
				found = 1;
				printf("Found student ID!\n");
				// calculate fine
				int days;
				printf("Enter number of days: "); scanf("%d", &days);
				if (days > 30) {
					searching_student.fine = (days - 30) * 10000;
					// overwrite data in Student.dat
					fseek(f, -1 * sizeof(Student), SEEK_CUR);
					fwrite(&searching_student, sizeof(Student), 1, f);
					printf("Successfully update!\n");
				}
				else {
					printf("Available for issue more.\n");
				}
			}
		}
		if (!found) {
			printf("Invalid ID.\n");
		}
	}
}