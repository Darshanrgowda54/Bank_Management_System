#include <stdio.h>
#include "user.h"


struct user *findUserByAccountNumber(struct user *users, int accountNumber)
{
    struct user *user = users;
    while (user != NULL)
    {
        if (user->account.accountNumber == accountNumber)
        {
            return user;
        }
        user = user->next;
    }
    return NULL;
}
