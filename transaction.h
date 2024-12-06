#ifndef TRANSACTION_H
#define TRANSACTION_H

typedef struct transaction {
    char type[20];
    int transactionId;
    float amount;
    struct transaction *next;
} transaction;


#endif
