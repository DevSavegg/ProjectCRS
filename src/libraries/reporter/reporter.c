#include "reporter.h"

// Private Functions

// Public Functions

void printCitizenInfo(char id[255]) {
    int status = 0;
    Record citizen_record = fastFetchRecord(DATA_CITIZEN, atoll(id), &status);

    char *address_id;
    Record address_record;

    if (status != 0) {
        printf("Error occured while fetching citizen data.");
        return;
    }

    address_id = citizen_record.data[9];

    if (address_id != NULL) {
        address_record = fastFetchRecord(DATA_ADDRESS, atoll(address_id), &status);

        if (status != 0) {
            printf("%d\n", status);
            printf("Error occured while fetching address data.");
            return;
        }
    }
//name, surname, ID, status, personState, religion, fatherRecordID, motherRecordID, date_buffer, address_id, gender
    printf("+--------------------------------------------------------+\n");
    printf("|                   Citizen Profile                      |\n");
    printf("+--------------------------------------------------------+\n");
    printf("|    Citizen's ID:      %-13s                    |\n", citizen_record.data[2]);
    printf("|    Name:   %-10s Surname:   %-10s            |\n", citizen_record.data[0], citizen_record.data[1]);
    printf("|    Gender:      %-19s                    |\n", citizen_record.data[10]);
    printf("|                                                        |\n");
    printf("|    Date of Birth:    %-17s                 |\n", citizen_record.data[8]);
    printf("|                                                        |\n");
    printf("|    Religion:    %-22s                 |\n", citizen_record.data[5]);
    printf("|                                                        |\n");
    printf("|    Status:    %-24s                 |\n", citizen_record.data[3]);
    printf("|    State:    %-25s                 |\n", citizen_record.data[4]);
    printf("+--------------------------------------------------------+\n");
    printf("|                       Address                          |\n");
    printf("+--------------------------------------------------------+\n");
    printf("|   House No.   %-5s           St. %-20s |\n", address_record.data[0], address_record.data[1]);
    printf("|   City        %-15s                          |\n", address_record.data[2]);
    printf("|   Province    %-15s Post Code   %-5s        |\n", address_record.data[3], address_record.data[4]);
    printf("+--------------------------------------------------------+\n");

}

void printCitizen(Citizen citizen) {
    printf("Name: %s\n", citizen.name);
    printf("Surname: %s\n", citizen.surname);
    printf("Citizen ID: %s\n", citizen.citizenID);

    // Depending on how Gender, Status, PersonState, and Date are defined, 
    // you will need to print those fields accordingly
    printf("Gender: %d\n", citizen.gender);  // Example: assuming Gender is an enum or integer
    printf("Status: %d\n", citizen.status);  // Assuming Status is an enum or integer
    printf("Person State: %d\n", citizen.personState);  // Assuming PersonState is an enum or integer

    printf("Religion: %s\n", citizen.religion);
    printf("Father Record ID: %s\n", citizen.fatherRecordID);
    printf("Mother Record ID: %s\n", citizen.motherRecordID);

    // Printing the date of birth (assuming Date is a struct with day, month, and year)
    printf("Date of Birth: %d-%d-%d\n", citizen.dateOfBirth.date, citizen.dateOfBirth.month, citizen.dateOfBirth.year);

    // Printing the address (assuming Address is a struct with street, city, etc.)
    printf("Address: %s\n", citizen.address.street);  // Example field; adjust based on Address definition

    printf("Spouse ID: %s\n", citizen.spouseID);
}