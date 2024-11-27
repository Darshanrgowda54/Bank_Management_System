#ifndef USER_H
#define USER_H
#include "bankaccount.h"
#include "transaction.h"

struct user {
    char userID[20];
    char userPassword[20];
    char name[50];
    char mobile[15];
    char email[50];
    char address[100];
    struct bankAccount account;
    struct transaction *transactions;
    struct user *next;
};



struct user *userLogin(struct user *users);
void displayUserMenu(struct user *user, struct user *users);
void deposit(struct user *user, float amount);
void withdraw(struct user *user, float amount);
void transfer(struct user *sender, struct user *receiver, float amount);
void addTransaction(struct user *user, const char *type, float amount);



#endif // USER_H
