#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "transaction.h"
#include "user.h"


void addTransaction(struct user *user, const char *type, float amount)
{
    struct transaction *newTransaction = (struct transaction *)malloc(sizeof(struct transaction));
    if (!newTransaction)
    {
        printf("Memory allocation failed!\n");
        return;
    }

    if (strncpy_s(newTransaction->type, sizeof(newTransaction->type), type, sizeof(newTransaction->type) - 1) != 0)
    {
        printf("Failed to copy transaction type.\n");
        free(newTransaction);
        return;
    }

    newTransaction->amount = amount;
    newTransaction->next = NULL;

    if (user->transactions == NULL)
    {
        user->transactions = newTransaction;
    } else
    {
        struct transaction *current = user->transactions;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = newTransaction;
    }
}


void freeTransactions(struct transaction *transactions)
{
    while (transactions)
    {
        struct transaction *temp = transactions;
        transactions = transactions->next;
        free(temp);
    }
}
