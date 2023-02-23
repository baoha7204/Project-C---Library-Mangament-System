#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "define.h"
#include "Librarian.h"
#include "Student.h"
#include "StudentDatabase.h"
#include "AccountDatabase.h"


void display_account(Account a) {
	printf("Username: %s\n", a.username);
	printf("Password: %s\n", a.password);
	printf("Role: ");
	(a.role == 1) ? printf("Student\n") : printf("Librarian\n");
}

void update_account(Account a, int pos) {
	FILE* f = fopen(ACCOUNT_DIR, "r+");
	if (f == NULL) {
		fprintf(stderr, "Error opening file.");
		exit(EXIT_FAILURE);
	}
	else {
		fseek(f, pos, SEEK_SET);
		fwrite(&a, sizeof(Account), 1, f);
		fclose(f);
	}
}
void modify_account(Account* a) {
	printf("Enter to continue...\n");  getchar();
	printf("Username: "); fgets(a->username, 50, stdin); a->username[strcspn(a->username, "\n")] = 0;
	printf("Password: "); fgets(a->password, 50, stdin); a->password[strcspn(a->password, "\n")] = 0;
	do {
		printf("Role (1 = student, 2 = librarian): "); scanf("%d", &a->role);
	} while (a->role != 1 && a->role != 2);
}

void register_student_account(Account* a) {
	printf("Username: "); fgets(a->username, 50, stdin); a->username[strcspn(a->username, "\n")] = 0;
	printf("Password: "); fgets(a->password, 50, stdin); a->password[strcspn(a->password, "\n")] = 0;
	a->role = 1; 
	a->identity = malloc(sizeof(Student));
	add_student((Student*)a->identity);
}

void register_librarian_account(Account* a) {
	printf("Enter to continue...\n");  getchar();
	printf("Username: "); fgets(a->username, 50, stdin); a->username[strcspn(a->username, "\n")] = 0;
	printf("Password: "); fgets(a->password, 50, stdin); a->password[strcspn(a->password, "\n")] = 0;
	a->role = 2;
	a->identity = malloc(sizeof(Librarian));
	modify_librarian((Librarian*)a->identity);
}
