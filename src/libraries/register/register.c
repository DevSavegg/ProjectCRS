#include "register.h"

/*

- Database structure -

name, surname, id, dateOfBirth, address_id

*/

// Private Functions //

void concatDate(char *buffer, Date date) {
    sprintf(buffer, "%d/%s/%d", date.date, date.month, date.year);

    return;
}

// Library Functions //

int registerCitizen(char name[21], char surname[21], char ID[14], Date dateOfBirth, Address address, char gender[7], char status[21], char personState[21],  char religion[21], char fatherRecordID[255], char motherRecordID[255], char spouseID[255]) {
    char date_buffer[18] = {0};
    int address_id;

    Record citizen_record, address_record;

    concatDate(date_buffer, dateOfBirth);

    address_record = imake_record("sssss", address.houseNo, address.street, address.city, address.province, address.postcode);
    ipush(DATA_ADDRESS, address_record);
    address_id = record_size(DATA_ADDRESS);

    citizen_record = imake_record("sssssssssdss", name, surname, ID, status, personState, religion, fatherRecordID, motherRecordID, date_buffer, address_id, gender, spouseID);
    ipush(DATA_CITIZEN, citizen_record);
    
    return record_size(DATA_CITIZEN);
}

Date make_date(int date, char month[11], int year) {
    Date date_obj = {
        .date = 0,
        .month = "",
        .year = 0
    };

    if (date < 1 || date > 31) {
        printf("Date must be in range between 1 - 31\n");
        return date_obj;
    }

    if (year < 0) {
        printf("Year can't be negative.\n");
        return date_obj;
    }

    date_obj.date = date;
    
    strcpy(date_obj.month, month);

    date_obj.year = year;

    return date_obj;
}

Address make_address(char houseNo[11], char street[51], char city[51], char province[51], char postcode[11]) {
    Address address_obj = {
        .houseNo = "0",
        .street = "-",
        .city = "-",
        .province = "-",
        .postcode = "00000"
    };

    if (houseNo != NULL && houseNo[0] != '\0') {
        strcpy(address_obj.houseNo, houseNo);
    }

    if (street != NULL && street[0] != '\0') {
        strcpy(address_obj.street, street);
    }

    if (city != NULL && city[0] != '\0') {
        strcpy(address_obj.city, city);
    }

    if (province != NULL && province[0] != '\0') {
        strcpy(address_obj.province, province);
    }

    if (postcode != NULL && province[0] != '\0') {
        strcpy(address_obj.postcode, postcode);
    }

    return address_obj;
}



Citizen make_citizen(char name[21], char surname[21], char id[14], Date dateOfBirth, Address address, char gender[7], char status[21], char personState[21],  char religion[21], char fatherRecordID[255], char motherRecordID[255], char spouseID[255]) {
    Citizen citizen_obj = {
        .name = "-",
        .surname = "-",
        .citizenID = "-"
    };

    if (name != NULL && name[0] != '\0') {
        strcpy(citizen_obj.name, name);
    }
    
    if (surname != NULL && surname[0] != '\0') {
        strcpy(citizen_obj.surname, surname);
    }

    if (id != NULL && id[0] != '\0') {
        strcpy(citizen_obj.citizenID, id);
    }

    citizen_obj.dateOfBirth = dateOfBirth;
    citizen_obj.address = address;
    strcpy(citizen_obj.gender, gender);
    strcpy(citizen_obj.status, status);
    strcpy(citizen_obj.personState, personState);
    strcpy(citizen_obj.religion, religion);
    strcpy(citizen_obj.fatherRecordID, fatherRecordID);
    strcpy(citizen_obj.motherRecordID, motherRecordID);
    strcpy(citizen_obj.spouseID, spouseID);

    return citizen_obj;
}

// For Initializing Data only.
// DO NOT use it to add bulk data to already exist database
// THIS FUNCTION IS UNSAFE, USE AT YOUR OWN RISK
void load_citizens_from_csv(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Unable to open file");
        return;
    }

    char date_buffer[18] = {0};
    int id = record_size(DATA_CITIZEN);
    char id_char[512];
    char line[512];

    if (id == -1) {
        puts("Index will start from 1 instead.");
        id = 1;
    }

    fgets(line, sizeof(line), file); // Skip header

    while (fgets(line, sizeof(line), file)) {
        char name[21], surname[21], citizenID[14];
        char status[21], personState[21], religion[21];
        char fatherID[255], motherID[255], spouseID[255];
        int date, year;
        char month[11];
        char houseNo[11], street[51], city[51], province[51], postcode[11];
        char gender[7];

        sscanf(line, "%20[^,],%20[^,],%13[^,],%20[^,],%20[^,],%20[^,],%254[^,],%254[^,],%d,%10[^,],%d,%10[^,],%50[^,],%50[^,],%50[^,],%10[^,],%7[^,],%254[^,]",
               name, surname, citizenID, status, personState, religion, fatherID, motherID,
               &date, month, &year,
               houseNo, street, city, province, postcode,
               gender, spouseID);

        Date dob = make_date(date, month, year);
        Address addr = make_address(houseNo, street, city, province, postcode);

        Record citizen_record, address_record;

        concatDate(date_buffer, dob);
        sprintf(id_char, "%d", id);

        //printf("%d, %s\n", id, id_char);

        address_record = make_record(id_char, "sssss", addr.houseNo, addr.street, addr.city, addr.province, addr.postcode);
        unsafePush(DATA_ADDRESS, address_record);

        citizen_record = make_record(id_char, "sssssssssdss", name, surname, citizenID, status, personState, religion, fatherID, motherID, date_buffer, id, gender, spouseID);
        unsafePush(DATA_CITIZEN, citizen_record);

        id++;

        if (id % 1000 == 0) {
            printf("Register record checkpoint #%d passed.\n", id);
        }
    }

    fclose(file);
}