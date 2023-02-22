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
	Account acc;
	int lua_chon;
	do {
		system("cls");
		printf_s("--------LOGIN--------\n");
		printf_s("1. Login.\n");
		printf_s("2. Register student account.\n");
		printf_s("0. Exit.\n");
		printf_s("Choose your function: "); scanf("%d", &lua_chon);
		system("cls");
		switch (lua_chon) {
		case 1:
			printf("Enter to continue...\n"); getchar();
			if (login_account(&acc)) {
				if (acc.role == 1) {
					printf("You are now login as student...\n");
					student_menu((Student*)acc.identity);
				}
				else {
					printf("You are now login as librarian...\n");
					librarian_menu();
				}
			}
			break;
		case 2:
			printf("Enter to continue...\n");  getchar();
			register_student_Account();
			break;
		case 0:
			return;
		default:
			printf("Not found the choice! Please enter again.\n");
		}
	} while (lua_chon != 1);
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

int login_account(Account* acc_database) {
	FILE* f = fopen(ACCOUNT_DIR, "r");
	if (f == NULL) {
		fprintf(stderr, "Error opening file.");
		exit(EXIT_FAILURE);
	}
	else {
		Account acc_user;
		printf_s("Nhap username: "); fgets(&acc_user.username, 50, stdin); fflush(stdin);
		printf_s("Nhap password: "); fgets(&acc_user.password, 50, stdin); fflush(stdin);

		while (fread(acc_database, sizeof(Account), 1, f) != NULL) {
			if (checkLogin(acc_user, *acc_database)) {
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