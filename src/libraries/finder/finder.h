#ifndef FINDER_H
#define FINDER_H

#include "../register/register.h"

int fetchByName(Citizen*, char[21]);
int fetchByCitizenId(Citizen*, char[14]);

#endif