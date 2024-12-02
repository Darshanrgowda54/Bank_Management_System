#ifndef ADMIN_H
#define ADMIN_H
#include"user.h"

struct Admin
{
    char adminID[20];
    char adminPassword[20];
};

int adminlogin();
void adminMenu(struct user *users);
void createAccount(struct user *users);
void deleteAccount(struct user *users, int accountNumber);
void updateAccount(struct user *users, int accountNumber);
void viewAccountDetails(struct user *user);
void viewTransactionHistory(struct user *user);
void sortUsersByAccountType(struct user **users);

#endif // ADMIN_H


