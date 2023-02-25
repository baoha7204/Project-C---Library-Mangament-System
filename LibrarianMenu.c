#include <stdio.h>
#include <stdlib.h>
#include "Librarian.h"
#include "BookDatabase.h"
#include "StudentDatabase.h"
#include "LibrarianMenu.h"

void librarian_menu() {
	while (1) {
		system("cls");
		printf("-------LIBRARIAN MENU-------\n");
		printf("1. Add book.\n");
		printf("2. Delete book.\n");
		printf("3. Display all books.\n");
		printf("4. Display available books.\n");
		printf("5. Display issued books.\n");
		printf("6. Search book.\n");
		printf("7. Modify book.\n");
		printf("8. Display all students.\n");
		printf("9. Search student.\n");
		printf("10. Issue book.\n");
		printf("11. Return book.\n");
		printf("12. Charge fine.\n");
		printf("0. Return login.\n");
		printf("Please select your choice: ");
		int lua_chon; scanf_s("%d", &lua_chon);
		printf("Enter to continue..."); while (getchar() != '\n');
		system("cls");
		switch (lua_chon) {
		case 1:
			add_book();
			break;
		case 2:
			delete_book();
			break;
		case 3:
			display_all_books();
			break;
		case 4:
			display_available_books();
			break;
		case 5:
			display_issued_books();
			break;
		case 6:
			search_book();
			break;
		case 7:
			modify_Book();
			break;
		case 8:
			display_all_students();
			break;
		case 9:
			search_student();
			break;
		case 10:
			issue_book();
			break;
		case 11:
			return_book();
			break;
		case 12:
			charge_fine();
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