#ifndef STUDENT_H
#define STUDENT_H 

#include "Date.h"

typedef struct Student {
	char name[50];
	char ID[10]; //key
	Date date_Of_Birth;
	long long issuedBookISBN;
	double fine;
} Student;

void display_student(Student* s);
void modify_student(Student* s);
void set_fine(Student* s, double newFine);
void pay_fine(Student* s);
void request_book_issue(Student* s);

#endif