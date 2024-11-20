#include "utils.h"

// Private Functions

int computeHash(const char *input) {
    int hash = 0;
    for (int i = 0; input[i] != '\0'; i++) {
        hash += input[i];
    }
    return hash % 100;
}

int calculateCheckDigit(const char *partialID) {
    int sum = 0;
    for (int i = 0; i < 12; i++) {
        sum += partialID[i] - '0';
    }
    return sum % 10;
}

int getMonthIndex(const char *month) {
    const char *months[] = {"January", "February", "March", "April", "May", "June",
                            "July", "August", "September", "October", "November", "December"};
    for (int i = 0; i < 12; i++) {
        if (strcasecmp(month, months[i]) == 0) {
            return i + 1;
        }
    }
    return 0;
}

// Public Functions

void intToChar(char *buffer, int num) {
    sprintf(buffer, "%d", num);
    return;
}

void generateCitizenID(char *buffer, Citizen citizenInfo) {
    char dateOfBirth[7]; // ddmmyy format
    snprintf(dateOfBirth, sizeof(dateOfBirth), "%02d%02d%02d",
             citizenInfo.dateOfBirth.date,
             getMonthIndex(citizenInfo.dateOfBirth.month),  // Assuming month is given in text
             citizenInfo.dateOfBirth.year % 100);

    int firstPart = toupper(citizenInfo.name[0]);

    int secondPart = toupper(citizenInfo.surname[0]);

    char combined[255];
    snprintf(combined, sizeof(combined), "%s%s%s%d",
             citizenInfo.name, citizenInfo.surname, dateOfBirth, rand() % 1000);
    int fourthPart = computeHash(combined);

    char partialID[13];
    snprintf(partialID, sizeof(partialID), "%02d%02d%s%02d",
             firstPart, secondPart, dateOfBirth, fourthPart);

    int checkDigit = calculateCheckDigit(partialID);

    snprintf(buffer, 14, "%s%d", partialID, checkDigit);
}