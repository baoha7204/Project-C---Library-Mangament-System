#include "AccountDatabase.h"

void login_menu();
int checkLogin(Account acc_check, Account acc_src);
int login_account(Account* acc_database, int* pos); // return login succeed or fail
void register_student_Account();