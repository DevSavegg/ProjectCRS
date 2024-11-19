#include "reporter.h"

// Private Functions

char intToChar(int num) {
    if (num < 0 || num > 255) {
        return '\0';
    }
    return (char)num;
}

// Public Functions

void printCitizenInfo(char id[255]) {
    int status = 0;
    Record citizen_record = fastFetchRecord(DATA_CITIZEN, atoll(id), &status);

    char *address_id, *contact_id;
    Record address_record, contact_record;

    //printf("%s %s %s %s %s %s\n", citizen_record.data[0], citizen_record.data[1], citizen_record.data[2], citizen_record.data[3], address_id, contact_id);

    if (status != 0) {
        printf("Error occured while fetching citizen data.");
        return;
    }

    address_id = citizen_record.data[4];
    contact_id = citizen_record.data[5];

    if (address_id != NULL) {
        address_record = fastFetchRecord(DATA_ADDRESS, atoll(address_id), &status);

        if (status != 0) {
            printf("%d\n", status);
            printf("Error occured while fetching address data.");
            return;
        }
    }

    if (address_id != NULL) {
        contact_record = fastFetchRecord(DATA_CONTACT, atoll(contact_id), &status);

        if (status != 0) {
            printf("%d\n", status);
            printf("Error occured while fetching contact data.");
            return;
        }
    }

    printf("+--------------------------------------------------------+\n");
    printf("|                   Citizen Profile                      |\n");
    printf("+--------------------------------------------------------+\n");
    printf("|    Citizen's ID:      %-13s                    |\n", citizen_record.data[2]);
    printf("|    Name:   %-10s Surname:   %-10s            |\n", citizen_record.data[0], citizen_record.data[1]);
    printf("|                                                        |\n");
    printf("|    Date of Birth:    %-17s                 |\n", citizen_record.data[3]);
    printf("+--------------------------------------------------------+\n");
    printf("|                       Address                          |\n");
    printf("+--------------------------------------------------------+\n");
    printf("|   House No.   %-5s           St. %-20s |\n", address_record.data[0], address_record.data[1]);
    printf("|   City        %-15s                          |\n", address_record.data[2]);
    printf("|   Province    %-15s Post Code   %-5s        |\n", address_record.data[3], address_record.data[4]);
    printf("+--------------------------------------------------------+\n");
    printf("|                     Contact Info                       |\n");
    printf("+--------------------------------------------------------+\n");
    printf("|   Phone No.       %-10s                           |\n", contact_record.data[0]);
    printf("|   Email           %-35s  |\n", contact_record.data[1]);
    printf("+--------------------------------------------------------+\n");

}