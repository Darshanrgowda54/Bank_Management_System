#ifndef ADMIN_H
#define ADMIN_H
#include "user.h"


typedef struct Admin {
    char adminID[20];
    char adminPassword[20];
} Admin;

int adminLogin();
void adminMenu(head *userList);
void createAccount(head *userList);
void deleteAccount(head *userList, int accountNumber);
void updateAccount(head *userList, int accountNumber);
void viewAccountDetails(head *userList, int accountNumber);
void viewAccountHistory(head *userList, int accountNumber);
void sortAccountsByType(head *userList);

#endif
