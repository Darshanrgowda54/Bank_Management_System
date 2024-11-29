#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "user.h"
#include "finduserbyaccountnumber.h"
#include "bankaccount.h"
#include "fileoperations.h"


struct user *userLogin(struct user *users)
{
    char userID[20], password[20];
    printf("Enter User ID: ");
    scanf("%s", userID);
    printf("Enter Password: ");
    scanf("%s", password);

    struct user *current = users;
    while (current != NULL)
    {
        if (strcmp(current->userID, userID) == 0 && strcmp(current->userPassword, password) == 0)
        {
            return current;
        }
        current = current->next;
    }
    printf("Invalid User ID or Password.\n");
    return NULL;
}


typedef enum {
    DEPOSITE =1,
    WITHDRAW,
    TRANDFER,
    CHECKBALANCE,
    LOGOUT
} MenuOption;


void displayUserMenu(struct user *user, struct user *users)
{
    int choice;
    while (1)
    {
        printf("\n... User Menu ....\n");
        printf("1. Deposit\n");
        printf("2. Withdraw\n");
        printf("3. Transfer\n");
        printf("4. Check Balance\n");
        printf("5. Logout\n");
        printf("Select an option: ");
        scanf("%d", &choice);

        switch ((MenuOption)choice)
        {
        case DEPOSITE:
        {
            float amount;
            printf("Enter amount to deposit: ");
            scanf("%f", &amount);
            deposit(user, amount);
            break;
        }
        case WITHDRAW:
        {
            float amount;
            printf("Enter the amount to withdraw: ");
            scanf("%f", &amount);
            withdraw(user, amount);
            break;
        }
        case TRANDFER:
        {
            int accountNumber;
            printf("Enter receiver account number: ");
            scanf("%d", &accountNumber);
            struct user *receiver = findUserByAccountNumber(users, accountNumber);
            if (receiver != NULL)
            {
                float amount;
                printf("Enter amount to transfer: ");
                scanf("%f", &amount);
                transfer(user, receiver, amount);
            }
            else {
                printf("Receiver account not found.\n");
            }
            break;
        }
        case CHECKBALANCE:
            printf("Your current balance is: %.2f\n", user->account.balance);
            break;
        case LOGOUT:
            saveDataToFile(users, "bank_data.txt");
            printf("... Logout form User ...\n");
            return;
        default:
            printf("Invalid choice. Please try again.\n");
            break;
        }
    }
}


void deposit(struct user *user, float amount)
{
    if (amount > 0) {
        user->account.balance += amount;
        addTransaction(user, "Deposit", amount);
        printf("Deposited %.2f successfully. New balance: %.2f\n", amount, user->account.balance);
    } else {
        printf("Invalid deposit amount.\n");
    }
}


void withdraw(struct user *user, float amount)
{
    if (amount > 0 && (user->account.balance - amount >= 500)) {
        user->account.balance -= amount;
        addTransaction(user, "Withdraw", amount);
        printf("Withdrawn %.2f successfully. New balance: %.2f\n", amount, user->account.balance);
    } else if (amount <= 0) {
        printf("Invalid withdrawal amount.\n");
    } else {
        printf("Transaction denied. Maintaining a minimum blance of 500 is required.\n");
    }
}


void transfer(struct user *sender, struct user *receiver, float amount)
{
    if (amount > 0 && (sender->account.balance - amount >= 500)) {
        sender->account.balance -= amount;
        receiver->account.balance += amount;
        addTransaction(sender, "Transfer Sent", amount);
        addTransaction(receiver, "Transfer Received", amount);
        printf("Transferred %.2f successfully to Account %d. Your new balance: %.2f\n", amount, receiver->account.accountNumber, sender->account.balance);
    } else if (amount <= 0) {
        printf("Invalid transfer amount.\n");
    } else {
        printf("Transaction denied. Maintaining a minimum blance of 500 is required.\n");
    }
}


