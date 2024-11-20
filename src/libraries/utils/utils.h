#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "../register/register.h"

void charToInt(char *buffer, int num);

void generateCitizenID(char *buffer, Citizen citizenInfo);

#endif