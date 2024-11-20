#ifndef FINDER_H
#define FINDER_H

#include "../register/register.h"

int fetchByName(Citizen *buffer, char name[21]);
int fetchBySurname(Citizen *buffer, char surname[21]);
int fetchByFullName(Citizen *buffer, char name[21], char surname[21]);

int fetchByCitizenID(Citizen *buffer, char citizenID[14]);

int fetchRawRecordID(char *buffer, char citizenID[14]);

#endif