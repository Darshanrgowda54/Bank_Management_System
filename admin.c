#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "admin.h"
#include "user.h"
#include "finduserbyaccountnumber.h"
#include "transaction.h"
#include "bankaccount.h"



int adminlogin()
{
    char adminID[20];
    char adminpassword[20];

    printf("Enter admin ID: ");
    scanf("%s", adminID);

    printf("Enter admin password: ");
    scanf("%s", adminpassword);

    if (strcmp(adminID, "0504") == 0 && strcmp(adminpassword,"Darshan") == 0)
    {
        return 1;
    }
    return 0;
}



void adminMenu(struct user **users)
{
    int choice;
    while (1)
    {
        printf("\n... Admin Menu ...\n");
        printf("1. Create Account\n");
        printf("2. Delete Account\n");
        printf("3. Update Account\n");
        printf("4. View User Account Details\n");
        printf("5. View User Transaction History\n");
        printf("6. Sort and Display Users by Account Type\n");
        printf("7. Logout\n");
        printf("Select an option: ");
        scanf("%d", &choice);



        switch (choice)
        {
        case 1:
            createAccount(users);
            break;
        case 2:
        {
            int accountNumber;
            printf("Enter account number to delete: ");
            scanf("%d", &accountNumber);
            deleteAccount(users, accountNumber);
            break;
        }
        case 3:
        {
            int accountNumber;
            printf("Enter account number to update: ");
            scanf("%d", &accountNumber);
            updateAccount(users, accountNumber);
            break;
        }
        case 4:
        {
            int accountNumber;
            printf("Enter account number to view details: ");
            scanf("%d", &accountNumber);
            struct user *user = findUserByAccountNumber(*users, accountNumber);
            if (user != NULL)
            {
                viewAccountDetails(user);
            } else
            {
                printf("Account not found.\n");
            }
            break;
        }
        case 5:
        {
            int accountNumber;
            printf("Enter account number to view transaction history: ");
            scanf("%d", &accountNumber);
            struct user *user = findUserByAccountNumber(*users, accountNumber);
            if (user != NULL)
            {
                viewTransactionHistory(user);
            }else
            {
                printf("Account not found.\n");
            }
            break;
        }
        case 6:
            sortUsersByAccountType(users);
            break;
        case 7:
            printf("... Logout from Admin ...\n");
            return;
        default:
            printf("Invalid choice. Please try again.\n");
            break;
        }
    }
}



int accountCounter = 1000;

void createAccount(struct user **users)
{
    struct user *newUser = malloc(sizeof(struct user));
    if (!newUser)
    {
        printf("Memory allocation failed!\n");
        return;
    }
    printf("Enter User ID: ");
    scanf(" %[^\n]", newUser->userID);
    printf("Enter Password: ");
    scanf(" %[^\n]", newUser->userPassword);
    printf("Enter Name: ");
    scanf(" %[^\n]", newUser->name);
    printf("Enter Mobile Number: ");
    scanf(" %[^\n]", newUser->mobile);
    printf("Enter Email: ");
    scanf("%s", newUser->email);
    printf("Enter Address: ");
    scanf(" %[^\n]", newUser->address);

    while (1)
    {
        printf("Enter Account Type (Savings/Current): ");
        scanf("%s", newUser->account.accountType);
        if (strcmp(newUser->account.accountType, "Savings") == 0 ||
            strcmp(newUser->account.accountType, "Current") == 0)
        {
            break;
        } else
        {
            printf("Invalid Account Type. Please enter 'Savings' or 'Current'.\n");
        }
    }

    while (1) {
        int Duplicate = 0;
        struct user *current = *users;

        while (current != NULL)
        {
            if (current->account.accountNumber == accountCounter)
            {
                Duplicate = 1;
                break;
            }
            current = current->next;
        }

        if (!Duplicate)
        {
            newUser->account.accountNumber = accountCounter++;
            break;
        } else
        {
            accountCounter++;
        }
    }

    printf("Enter Initial Amount: ");
    scanf("%f", &newUser->account.balance);
    if (newUser->account.balance < 0)
    {
        printf("Initial amount cannot be negative.\n");
        newUser->account.balance = 0;
    }

    newUser->transactions = NULL;
    newUser->next = *users;
    *users = newUser;

    printf("Account created successfully with Account Number: %d\n", newUser->account.accountNumber);
}



void deleteAccount(struct user **users, int accountNumber)
{
    struct user *current = *users;
    struct user *previous = NULL;

    while (current != NULL && current->account.accountNumber != accountNumber)
    {
        previous = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("Account not found.\n");
        return;
    }

    if (previous == NULL)
    {
        *users = current->next;
    } else
    {
        previous->next = current->next;
    }

    struct transaction *transaction = current->transactions;
    while (transaction != NULL)
    {
        struct transaction *temp = transaction;
        transaction = transaction->next;
        free(temp);
    }

    free(current);
    printf("Account Number %d deleted successfully.\n", accountNumber);
}



void updateAccount(struct user **users, int accountNumber)
{
    struct user *user = findUserByAccountNumber(*users, accountNumber);
    if (user == NULL)
    {
        printf("Account not found.\n");
        return;
    }

    int choice;
    while (1)
    {
        printf("\nSelect the field you want to update:\n");
        printf("1. Name\n");
        printf("2. Mobile Number\n");
        printf("3. Email\n");
        printf("4. Address\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter New Name: ");
            scanf(" %[^\n]", user->name);
            printf("Name updated successfully.\n");
            break;
        case 2:
            printf("Enter New Mobile Number: ");
            scanf(" %[^\n]", user->mobile);
            printf("Mobile number updated successfully.\n");
            break;
        case 3:
            printf("Enter New Email: ");
            scanf("%s", user->email);
            printf("Email updated successfully.\n");
            break;
        case 4:
            printf("Enter New Address: ");
            scanf(" %[^\n]", user->address);
            printf("Address updated successfully.\n");
            break;
        case 5:
            printf("Exiting update menu.\n");
            return;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    }
}


void viewTransactionHistory(struct user *user)
{
    printf("\nTransaction History:\n");
    if (user->transactions == NULL)
    {
        printf("No transactions available.\n");
        return;
    }

    struct transaction *current = user->transactions;
    int count = 1;
    while (current != NULL)
    {
        printf("%d. Type: %s, Amount: %.2f\n", count, current->type, current->amount);
        current = current->next;
        count++;
    }
}


void viewAccountDetails(struct user *user)
{
    printf("\nAccount Details:\n");
    printf("Name: %s\n", user->name);
    printf("Mobile: %s\n", user->mobile);
    printf("Email: %s\n", user->email);
    printf("Address: %s\n", user->address);
    printf("Account Type: %s\n", user->account.accountType);
    printf("Account Number: %d\n", user->account.accountNumber);
    printf("Balance: %.2f\n", user->account.balance);
}


void sortUsersByAccountType(struct user **users)
{
    int count = 0;
    struct user *current = *users;

    while (current != NULL)
    {
        count++;
        current = current->next;
    }

    if (count == 0)
    {
        printf("No users available to sort.\n");
        return;
    }

    struct user *tempArray[count];
    current = *users;

    for (int i = 0; i < count; i++)
    {
        tempArray[i] = current;
        current = current->next;
    }

    for (int i = 0; i < count - 1; i++)
    {
        for (int j = 0; j < count - i - 1; j++)
        {
            if (strcmp(tempArray[j]->account.accountType, tempArray[j + 1]->account.accountType) > 0)
            {
                struct user *temp = tempArray[j];
                tempArray[j] = tempArray[j + 1];
                tempArray[j + 1] = temp;
            }
        }
    }

    printf("Users sorted by account type\n");
    printf("-----------------------------\n");
    for (int i = 0; i < count; i++) {
        printf("Account Number: %d\n", tempArray[i]->account.accountNumber);
        printf("Name: %s\n", tempArray[i]->name);
        printf("Account Type: %s\n", tempArray[i]->account.accountType);
        printf("Balance: %.2f\n", tempArray[i]->account.balance);
        printf("-----------------------------\n");
    }
}
