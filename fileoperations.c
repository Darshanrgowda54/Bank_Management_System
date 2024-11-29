#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fileoperations.h"
#include "transaction.h"


void saveDataToFile(struct user *users, const char *filename) {
    FILE *file = fopen(filename, "wb");
    if (!file) {
        printf("Error: Unable to open file for saving.\n");
        return;
    }

    struct user *currentUser = users;
    while (currentUser != NULL) {
        fwrite(currentUser, sizeof(struct user), 1, file);

        struct transaction *currentTransaction = currentUser->transactions;
        while (currentTransaction != NULL) {
            fwrite(currentTransaction, sizeof(struct transaction), 1, file);
            currentTransaction = currentTransaction->next;
        }

        struct transaction nullTransaction = {0};
        fwrite(&nullTransaction, sizeof(struct transaction), 1, file);

        currentUser = currentUser->next;
    }

    fclose(file);
    printf("All data saved successfully to %s.\n", filename);
}


void loadDataFromFile(struct user **users, const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        printf("No existing data file found. Starting fresh.\n");
        return;
    }

    struct user *lastUser = NULL;
    while (1) {
        struct user *newUser = (struct user *)malloc(sizeof(struct user));
        if (fread(newUser, sizeof(struct user), 1, file) != 1) {
            free(newUser);
            break;
        }

        newUser->transactions = NULL;
        newUser->next = NULL;

        struct transaction *lastTransaction = NULL;
        while (1) {
            struct transaction *newTransaction = (struct transaction *)malloc(sizeof(struct transaction));
            fread(newTransaction, sizeof(struct transaction), 1, file);

            if (newTransaction->amount == 0 && strlen(newTransaction->type) == 0) {
                free(newTransaction);
                break;
            }

            newTransaction->next = NULL;
            if (lastTransaction == NULL) {
                newUser->transactions = newTransaction;
            } else {
                lastTransaction->next = newTransaction;
            }
            lastTransaction = newTransaction;
        }

        if (*users == NULL) {
            *users = newUser;
        } else {
            if (lastUser != NULL){
            lastUser->next = newUser;
            }
        }
        lastUser = newUser;
    }

    fclose(file);
    printf("All data loaded successfully from %s.\n", filename);
}



