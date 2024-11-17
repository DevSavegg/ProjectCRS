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
    char phone[11];
    char email[51];
} Contact;

typedef struct {
    char name[21];
    char surname[21];

    char citizenID[14];

    Date dateOfBirth;
    Address address;
    
    Contact contact;
} Citizen;

int registerCitizen(char[21], char[21], char[14], Date, Address, Contact);

Date make_date(int, char[11], int);
Address make_address(char[11], char[51], char[51], char[51], char[11]);
Contact make_contact(char[11], char[51]);
Citizen make_citizen(char[21], char[21], char[14], Date, Address, Contact);

void load_citizens_from_csv(const char*);

#endif