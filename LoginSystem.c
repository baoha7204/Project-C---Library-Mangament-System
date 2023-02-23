#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "define.h"
#include "StudentMenu.h"
#include "LibrarianMenu.h"
#include "BookDatabase.h"
#include "StudentDatabase.h"
#include "LoginSystem.h"

void login_menu() {
	while (1) {
		Account acc;
		system("cls");
		printf_s("--------LOGIN--------\n");
		printf_s("1. Login.\n");
		printf_s("2. Register student account.\n");
		printf_s("0. Exit.\n");
		printf_s("Choose your function: ");
		int lua_chon; scanf("%d", &lua_chon);
		int pos;
		switch (lua_chon) {
		case 1:
			printf("Enter to continue...\n"); getchar();
			system("cls");
			if (login_account(&acc, &pos)) {
				if (acc.role == 1) {
					printf("You are now login as student...\n");
					student_menu(&(Student*)acc.identity);
				}
				else {
					printf("You are now login as librarian...\n");
					librarian_menu();
				}
				update_account(acc, pos);
			}
			else {
				printf("Incorrect username/password. Please try again.\n");
			}
			break;
		case 2:
			printf("Enter to continue...\n");  getchar();
			system("cls");
			register_student_Account();
			break;
		case 0:
			return;
		default:
			printf("Not found the choice! Please enter again.\n");
		}
	}
}

int checkLogin(Account acc_check, Account acc_src) {
	if (strcmp(acc_check.username, acc_src.username) != 0) {
		return 0;
	}
	else if (strcmp(acc_check.password, acc_src.password) != 0) {
		return 0;
	}
	return 1;
}

int login_account(Account* acc_database, int* pos) {
	FILE* f = fopen(ACCOUNT_DIR, "r");
	if (f == NULL) {
		fprintf(stderr, "Error opening file.");
		exit(EXIT_FAILURE);
	}
	else {
		Account acc_user;
		printf_s("Nhap username: "); fgets(&acc_user.username, 50, stdin); acc_user.username[strcspn(acc_user.username, "\n")] = 0;
		printf_s("Nhap password: "); fgets(&acc_user.password, 50, stdin); acc_user.password[strcspn(acc_user.password, "\n")] = 0;

		while (fread(acc_database, sizeof(Account), 1, f) != NULL) {
			if (checkLogin(acc_user, *acc_database)) {
				*pos = fseek(f, -1 * sizeof(Account), SEEK_CUR);
				fclose(f);
				return 1;
			}
		}
		fclose(f);
		return 0;
	}
}

void register_student_Account() {
	FILE* f = fopen(ACCOUNT_DIR, "a");
	if (f == NULL) {
		fprintf(stderr, "Error opening file.");
		exit(EXIT_FAILURE);
	}
	else {
		Account acc;
		register_student_account(&acc);
		fwrite(&acc, sizeof(acc), 1, f);
		fclose(f);
		printf("Successfully register student account...\n");
	}
}