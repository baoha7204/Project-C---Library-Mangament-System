#ifndef ACCOUNT_H
#define ACCOUNT_H

typedef struct Account {
	char username[50];
	char password[50];
	int role; // 1 = student, 2 = librarian 
	void* identity; // generic type
} Account;

#endif