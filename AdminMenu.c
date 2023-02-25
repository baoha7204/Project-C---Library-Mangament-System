#include <stdio.h>
#include <stdlib.h>
#include "AccountDatabase.h"
#include "LoginSystem.h"
#include "StudentDatabase.h"
#include "AdminMenu.h"

void admin_menu() {
	while (1) {
		system("cls");
		printf("-------ADMIN MENU-------\n");
		printf("1. Add librarian account.\n");
		printf("2. Delete student.\n");
		printf("3. Modify student.\n");
		printf("0. Return login.\n");
		printf("Please select your choice: ");
		int lua_chon; scanf_s("%d", &lua_chon);
		printf("Enter to continue..."); while (getchar() != '\n');
		system("cls");
		switch (lua_chon) {
		case 1:
			register_librarian_Account();
			break;
		case 2:
			delete_student();
			break;
		case 3:
			modify_Student();
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