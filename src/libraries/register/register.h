#ifndef REGISTER_H
#define REGISTER_H

#define DATA_CITIZEN "src/data/Citizens.dat"
#define DATA_ADDRESS "src/data/Addresses.dat"
#define DATA_CONTACT "src/data/Contacts.dat"
#define DATA_CRIME "src/data/Crimes.dat"

#include "../database/database.h"

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
    char gender[7];
    char status[21];
    char personState[21];

    char religion[21];
    
    char fatherRecordID[255];
    char motherRecordID[255];

    Date dateOfBirth;
    Address address;
    char spouseID[255];
} Citizen;

#define NULLDATE (Date){-1, "NULL", -1}
#define NULLADDRESS (Address){"NULL", "NULL", "NULL", "NULL", "NULL"}
#define NULLCONTACT (Contact){"NULL", "NULL"}
#define NULLCITIZEN (Citizen){"-", "-", "-", "-", "-", "-", "-", "-", "-", NULLDATE, NULLADDRESS, "-"}
int registerCitizen(char[21], char[21], char[14], Date, Address, char[7], char[21], char[21],  char[21], char[255], char[255], char[255]);

Date make_date(int, char[11], int);
Address make_address(char[11], char[51], char[51], char[51], char[11]);
Citizen make_citizen(char[21], char[21], char[14], Date, Address, char[7], char[21], char[21],  char[21], char[255], char[255], char[255]);

void load_citizens_from_csv(const char*);

#endif