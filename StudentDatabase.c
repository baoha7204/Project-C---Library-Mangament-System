#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "define.h"
#include "Student.h"
#include "StudentDatabase.h"

void add_student() {
	do {
		Student s;
		modify_student(&s);
		s.issuedBookISBN = 0;
		s.fine = 0;
		// add to file
		FILE* f = fopen(STUDENT_DIR, "a+");
		if (f == NULL) {
			fprintf(stderr, "Error opening file.");
			exit(EXIT_FAILURE);
		}
		else {
			fwrite(&s, sizeof(Student), 1, f);
			fclose(f);
		}
		printf("Add more (y/n)? "); while (getchar() != '\n');
	} while (tolower(getchar()) == 'y');
}

void delete_student() {
	do {
		char searching_ID[10];
		int found = 0;
		printf("Enter the ID: "); fgets(&searching_ID, 10, stdin); searching_ID[strcspn(searching_ID, "\n")] = 0;
		// Create a temporary file (temp file), write all the record of Student except the deleting one, then replace temp file with Student.dat
		FILE* f = fopen(STUDENT_DIR, "r");
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
	FILE* f = fopen(STUDENT_DIR, "r+");
	if (f == NULL) {
		fprintf(stderr, "Error opening file.");
		exit(EXIT_FAILURE);
	}
	else {
		printf("All the students in the library:\n");
		Student s;
		while (fread(&s, sizeof(Student), 1, f) != NULL) {
			display_student(s);
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
		// Look for matching ID in Student database
		FILE* f = fopen(STUDENT_DIR, "r+");
		if (f == NULL) {
			fprintf(stderr, "Error opening file.");
			exit(EXIT_FAILURE);
		}
		else {
			Student searching_student;
			while (fread(&searching_student, sizeof(Student), 1, f) != NULL) {
				if (strcmp(searching_student.ID, searching_ID) == 0) {
					found = 1;
					display_student(searching_student);
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
		// Modify student in student database
		FILE* f = fopen(STUDENT_DIR, "r+");
		if (f == NULL) {
			fprintf(stderr, "Error opening file.");
			exit(EXIT_FAILURE);
		}
		else {
			Student modifying_student;
			while (fread(&modifying_student, sizeof(Student), 1, f) != NULL) {
				if (strcmp(modifying_student.ID, searching_ID) == 0) {
					found = 1;
					modify_student(&modifying_student);
					fseek(f, -1 * sizeof(Student), SEEK_CUR);
					fwrite(&modifying_student, sizeof(Student), 1, f);
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