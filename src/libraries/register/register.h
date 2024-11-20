#ifndef REGISTER_H
#define REGISTER_H

#define DATA_CITIZEN "src/data/Citizens.dat"
#define DATA_ADDRESS "src/data/Addresses.dat"
#define DATA_CRIME "src/data/Crimes.dat"

#include "../database/database.h"
#include "../finder/finder.h"
#include "../utils/utils.h"

typedef enum {
    MALE = 0,
    FEMALE = 1
} Gender;

typedef enum {
    SINGLE = 0,
    MARRIED = 1,
    DIVORCED = 2,
    WIDOWED = 3
} Status;

typedef enum {
    ALIVE = 0,
    DECEASED = 1,
    DISAPPEARED = 2,
    UNKNOWN = 3
} PersonState;

typedef struct {
    int date;
    char month[11];
    int year;
} Date;

typedef struct {
    char houseNo[11];
    char street[51];
    char city[51];
    char province[51];
    char postcode[11];
} Address;

typedef struct {
    char name[21];
    char surname[21];

    char citizenID[14];
    Gender gender;
    Status status;
    PersonState personState;

    char religion[21];
    
    char fatherRecordID[255];
    char motherRecordID[255];

    Date dateOfBirth;
    Address address;
    char spouseID[255];
} Citizen;

#define NULLDATE (Date){-1, "NULL", -1}
#define NULLADDRESS (Address){"NULL", "NULL", "NULL", "NULL", "NULL"}
#define NULLCITIZEN (Citizen){"-", "-", "-", MALE, SINGLE, UNKNOWN, "-", "-", "-", NULLDATE, NULLADDRESS, "-"}

int reportBirth(char fatherRecordID[255], char motherRecordID[255], char childName[21], Gender gender, char religion[21], Date dateOfBirth);
int reportDeceased(char citizenID[14]);
int reportDisappeared(char citizenID[14]);
int reportMarriage(char groomCitizenID[14], char brideCitizenID[14]);
int reportDivorced(char citizenID[14]);

Date make_date(int date, char month[11], int year);
Address make_address(char houseNo[11], char street[51], char city[51], char province[51], char postCode[11]);
Citizen make_citizen(char name[21], char surname[21], char citizenID[14], Gender gender, Status status,
                    PersonState personState, char religion[21], char fatherRecordID[255], char motherRecordID[255],
                    Date dateOfBirth, Address address, char spouseID[255]);

void genderToString(Gender gender, char* buffer);
void statusToString(Status status, char* buffer);
void personStateToString(PersonState state, char* buffer);

void load_citizens_from_csv(const char*);

#endif