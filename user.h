#ifndef USER_H
#define USER_H

#include "bankaccount.h"
#include "transaction.h"

typedef struct user {
    char userID[20];
    char userPassword[20];
    char name[50];
    char mobile[15];
    char email[50];
    char address[100];
    struct bankAccount account;
    struct transaction *transactions;
    struct user *next;
} user;


typedef struct head {
    user *head;
    int userCount;
} head;


user *userLogin(user *users);
void userMenu(user *loggedInUser, head *userList);
void deposit(user *loggedInUser, float amount);
void withdraw(user *loggedInUser, float amount);
void transfer(user *sender, user *receiver, float amount);
void addTransaction(user *loggedInUser, const char *type, float amount);


#endif
