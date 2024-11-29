#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "admin.h"
#include "user.h"
#include "fileoperations.h"

typedef enum
{
    ADMINLOGIN = 1,
    USERLOGIN,
    EXIT
} MenuOption;

int mainmenu() {
    struct user *users = NULL;
    int choice;

    loadDataFromFile(&users, "bank_data.txt");

    while (1)
    {
        printf("\n..... Welcome to the Bank .....\n");
        printf("1. Admin Login\n");
        printf("2. User Login\n");
        printf("3. Exit\n");
        printf("Select an option: ");
        scanf("%d", &choice);

        switch ((MenuOption)choice)
        {
        case ADMINLOGIN:
            if (adminlogin())
            {
                printf("Admin login successful.\n");
                adminMenu(&users);
            }
            else
            {
                printf("Invalid admin credentials.\n");
            }
            break;

        case USERLOGIN:
        {
            struct user *userlogin = userLogin(users);
            if (userlogin != NULL) {
                printf("User login successful.\n");
                displayUserMenu(userlogin, users);
            }
            else
            {
                printf("Invalid user credentials.\n");
            }
            break;
        }

        case EXIT:
            saveDataToFile(users, "bank_data.txt");
            printf("Thank you. Please visit again.\n");
            return 0;

        default:
            printf("Invalid choice. Please try again.\n");
            break;
        }
    }
}

