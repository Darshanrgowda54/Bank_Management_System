#ifndef TRANSACTION_H
#define TRANSACTION_H


struct transaction
{
    char type[20];
    int transactionId;
    float amount;
    struct transaction *next;
};



#endif // TRANSACTION_H


