#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "admin.h"
#include "user.h"
#include "fileoperations.h"


int mainmenu() {
    struct user *users = NULL;
    int choice;

    loadDataFromFile(&users, "bank_data.dat");

    while (1)
    {
        printf("\n..... Welcome to the Bank .....\n");
        printf("1. Admin Login\n");
        printf("2. User Login\n");
        printf("3. Exit\n");
        printf("Select an option: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
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

        case 2:
        {
            struct user *userlogin = userLogin(users);
            if (userlogin != NULL)
            {
                printf("User login successful.\n");
                displayUserMenu(userlogin, users);
            }
            else
            {
                printf("Invalid user credentials.\n");
            }
            break;
        }

        case 3:
            saveDataToFile(users, "bank_data.dat");
            printf(" Thank you. Please visit again\n");
            return 0;

        default:
            printf("Invalid choice. Please try again.\n");
            break;
        }
    }
}
