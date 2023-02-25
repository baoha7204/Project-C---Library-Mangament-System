#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "define.h"
#include "Student.h"
#include "StudentMenu.h"
#include "LibrarianMenu.h"
#include "AdminMenu.h"
#include "LoginSystem.h"

int checkLogin(Account acc_check, Account acc_src) {
	if (strcmp(acc_check.username, acc_src.username) != 0) {
		return 0;
	}
	else if (strcmp(acc_check.password, acc_src.password) != 0) {
		return 0;
	}
	return 1;
}

int checkStudentLogin(StudentAccount acc_check, StudentAccount acc_src) {
	if (strcmp(acc_check.username, acc_src.username) != 0) {
		return 0;
	}
	else if (strcmp(acc_check.password, acc_src.password) != 0) {
		return 0;
	}
	return 1;
}

int login_account(Account* acc, int* pos) {
	FILE* f = fopen(ACCOUNT_DIR, "r");
	if (f == NULL) {
		fprintf(stderr, "Error opening file.");
		exit(EXIT_FAILURE);
	}
	else {
		Account acc_user;
		printf_s("Nhap username: "); fgets(&acc_user.username, 50, stdin); acc_user.username[strcspn(acc_user.username, "\n")] = 0;
		printf_s("Nhap password: "); fgets(&acc_user.password, 50, stdin); acc_user.password[strcspn(acc_user.password, "\n")] = 0;

		Account acc_database;
		while (fread(&acc_database, sizeof(Account), 1, f) != NULL) {
			if (checkLogin(acc_user, acc_database)) {
				memcpy(acc, &acc_database, sizeof(Account));
				*pos = ftell(f) - 1 * sizeof(Account);
				fclose(f);
				return 1;
			}
		}
		fclose(f);
		return 0;
	}
}

int login_student_account(StudentAccount* acc, int* pos) {
	FILE* f = fopen(STUDENTACCOUNT_DIR, "r");
	if (f == NULL) {
		fprintf(stderr, "Error opening file.");
		exit(EXIT_FAILURE);
	}
	else {
		StudentAccount acc_user;
		printf_s("Nhap username: "); fgets(&acc_user.username, 50, stdin); acc_user.username[strcspn(acc_user.username, "\n")] = 0;
		printf_s("Nhap password: "); fgets(&acc_user.password, 50, stdin); acc_user.password[strcspn(acc_user.password, "\n")] = 0;

		StudentAccount acc_database;
		while (fread(&acc_database, sizeof(StudentAccount), 1, f) != NULL) {
			if (checkStudentLogin(acc_user, acc_database)) {
				memcpy(acc, &acc_database, sizeof(StudentAccount));
				*pos = ftell(f) - 1 * sizeof(StudentAccount);
				fclose(f);
				return 1;
			}
		}
		fclose(f);
		return 0;
	}
}

void register_student_Account() {
	FILE* f = fopen(STUDENTACCOUNT_DIR, "a");
	if (f == NULL) {
		fprintf(stderr, "Error opening file.");
		exit(EXIT_FAILURE);
	}
	else {
		StudentAccount acc;
		register_student_account(&acc);
		fwrite(&acc, sizeof(StudentAccount), 1, f);
		fclose(f);
		printf("Successfully register student account...\n");
	}
}

void register_librarian_Account() {
	FILE* f = fopen(ACCOUNT_DIR, "a");
	if (f == NULL) {
		fprintf(stderr, "Error opening file.");
		exit(EXIT_FAILURE);
	}
	else {
		Account acc;
		register_librarian_account(&acc);
		fwrite(&acc, sizeof(Account), 1, f);
		fclose(f);
		printf("Successfully register librarian account...\n"); 
	}
}

void login_menu() {
	printf("WELCOME TO LIBRARY MANAGEMENT SYSTEM\n");
	printf("Enter to continue..."); while (getchar() != '\n');
	while (1) {
		system("cls");
		printf_s("--------LOGIN--------\n");
		printf_s("1. Login.\n");
		printf_s("2. Register student account.\n");
		printf_s("0. Exit.\n");
		printf_s("Choose your function: ");
		int lua_chon; scanf_s("%d", &lua_chon);
		printf("Enter to continue..."); while (getchar() != '\n');
		system("cls");
		switch (lua_chon) {
		case 1:
			printf("1. Student.\n");
			printf("2. Librarian.\n");
			printf("3. Admin.\n");
			printf("You are login as? ");
			int role; scanf_s("%d", &role); while (getchar() != '\n');
			int pos, found = 0;
			if (role == 1) {
				StudentAccount sa;
				if (login_student_account(&sa, &pos)) {
					found = 1;
					printf("You are now login as student...\n");
					printf("Enter to continue..."); while (getchar() != '\n');
					student_menu(&sa.identity);
					// Update student info in StudentAccount.dat
					update_student_account(sa, pos);
				}
			}
			else if (role == 2 || role == 3) {
				Account acc;
				if (login_account(&acc, &pos)) {
					found = 1;
					if (acc.role == 2) {
						printf("You are now login as librarian...\n");
						printf("Enter to continue..."); while (getchar() != '\n');
						librarian_menu();
					}
					else if (acc.role == 3) {
						printf("You are now login as admin...\n");
						printf("Enter to continue..."); while (getchar() != '\n');
						admin_menu();
					}
				}
			}
			else {
				printf("Please enter the right role!");
				break;
			}
			if (!found) {
				printf("Incorrect username/password. Please try again.\n");
			}
			break;
		case 2:
			register_student_Account();
			break;
		case 0:
			return;
		default:
			printf("Not found the choice! Please enter again.\n");
		}
		printf("Enter to continue...");
		while (getchar() != '\n' && getchar() != EOF);
	}
}