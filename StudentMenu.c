#include <stdio.h>
#include <stdlib.h>
#include "StudentMenu.h"
#include "BookDatabase.h"

void student_menu(Student* s) {
	while (1) {
		system("cls");
		printf("-------STUDENT MENU-------\n");
		printf("1. Display your information.\n");
		printf("2. Search for book.\n");
		printf("3. Request a book issue.\n");
		printf("4. Return an issued book.\n");
		printf("5. Pay fine.\n");
		printf("0. Return login.\n");
		printf("Please select your choice: ");
		int lua_chon; scanf("%d", &lua_chon);
		printf("Enter to continue..."); while (getchar() != '\n');
		system("cls");
		switch (lua_chon) {
		case 1:
			display_student(*s);
			break;
		case 2:
			search_book();
			break;
		case 3:
			request_book_issue(s);
			break;
		case 4:
			return_book_issue(s);
			break;
		case 5:
			pay_fine(s); 
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