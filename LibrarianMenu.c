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
		printf("8. Add student.\n");
		printf("9. Delete student.\n");
		printf("10. Display all students.\n");
		printf("11. Search student.\n");
		printf("12. Modify student.\n");
		printf("13. Issue book.\n");
		printf("14. Return book.\n");
		printf("15. Charge fine.\n");
		printf("16. Exit.");
		printf("Please select your choice: ");
		int lua_chon; scanf("%d", &lua_chon);
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
			add_student();
			break;
		case 9:
			delete_student();
			break;
		case 10:
			display_all_students();
			break;
		case 11:
			search_student();
			break;
		case 12:
			modify_Student();
			break;
		case 13:
			issue_book();
			break;
		case 14:
			return_book();
			break;
		case 15:
			charge_fine();
			break;
		case 16:
			return;
		default:
			printf("Not found the choice! Please enter again.\n");
		}
	}
}