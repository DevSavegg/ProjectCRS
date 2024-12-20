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

// Public Functions

void intToChar(char *buffer, int num) {
    sprintf(buffer, "%d", num);
    return;
}

void generateCitizenID(char *buffer, Citizen citizenInfo) {
    char dateOfBirth[7]; // ddmmyy format
    snprintf(dateOfBirth, sizeof(dateOfBirth), "%02d%02d%02d",
             citizenInfo.dateOfBirth.date,
             citizenInfo.dateOfBirth.month,  // Assuming month is given in text
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

void strMonth(int month, char o[21]){
    char months[13][21] = {"","January","Febuary", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
    strcpy(o, months[month]);
}