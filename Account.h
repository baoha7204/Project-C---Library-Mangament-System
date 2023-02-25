#ifndef ACCOUNT_H
#define ACCOUNT_H
#include "Student.h"
typedef struct Account {
	char username[50];
	char password[50];
	int role; // 1 = student, 2 = librarian, 3 = admin
} Account;

typedef struct StudentAccount {
	char username[50];
	char password[50];
	int role;
	Student identity;
} StudentAccount;
#endif