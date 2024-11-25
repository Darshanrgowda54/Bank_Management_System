#ifndef TRANSACTION_H
#define TRANSACTION_H
//#include <time.h>


struct transaction
{
    int transactionId;
    char type[20];
    float amount;
   //time_t transactionTime;
    struct transaction *next;
};



#endif // TRANSACTION_H


