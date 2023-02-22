#include <stdio.h>
#include <stdlib.h>
#include "StudentMenu.h"
#include "BookDatabase.h"

void student_menu(Student* s) {
	while (1) {
		system("cls");
		printf("-------STUDENT MENU-------\n");
		printf("1. Search for book.\n");
		printf("2. Request a book issue.\n");
		printf("3. Pay fine.\n");
		printf("0. Exit.\n");
		printf("Please select your choice: ");
		int lua_chon; scanf("%d", &lua_chon);
		system("cls");
		switch (lua_chon) {
		case 1:
			search_book();
			break;
		case 2:
			request_book_issue(s);
			break;
		case 3:
			pay_fine(s);
			break;
		case 0:
			return;
		default:
			printf("Not found the choice! Please enter again.\n");
		}
	}
}