#ifndef FILEOPERATIONS_H
#define FILEOPERATIONS_H
#include "user.h"

void saveDataToFile(struct user *users, const char *filename);

void loadDataFromFile(struct user **users, const char *filename);

#endif // FILEOPERATIONS_H
