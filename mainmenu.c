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

    while (1) {
        printf("\n.....Welcome to the Pthinks Bank.....\n");
        printf("1. Admin Login\n");
        printf("2. User Login\n");
        printf("3. Exit\n");
        printf("Select an option: ");
        scanf("%d", &choice);

        if (choice == 1) {
            if (adminlogin()) {
                printf("Admin login successful.\n");
                adminMenu(&users);
            } else {
                printf("Invalid admin credentials.\n");
            }
        } if (choice == 2) {
            struct user *userlogin = userLogin(users);
            if (userlogin != NULL) {
                printf("User login successful.\n");
                displayUserMenu(userlogin, users);
                printf("Invalid user credentials.\n");
            }
        }else if (choice == 3) {
            saveDataToFile(users, "bank_data.dat");
            printf("Exiting the system. Goodbye!\n");
            break;
        } else {
            printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
