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

// int reportDeceased(char citizenID[14]) {
//     int count, i, status;
//     char citizenRecordBuffer[255];
//     Citizen citizenObjectBuffer;
 
//     count = fetchRawRecordID(citizenRecordBuffer, citizenID);
//     count = fetchByCitizenID(&citizenObjectBuffer, citizenID);

//     if (count <= 0) {
//         return -1;
//     }

//     if (citizenObjectBuffer.status == MARRIED) {
//         char tmp[255];
//         fetchRawRecordID(tmp, citizenObjectBuffer.spouseID);

//         update(DATA_CITIZEN, tmp, 11, "-", &status);
//         update(DATA_CITIZEN, tmp, 4, "3", &status);
//     }
//     update(DATA_CITIZEN, citizenRecordBuffer, 5, "1", &status);
// }

Date make_date(int date, char month[11], int year) {
    Date date_obj;
    
    date_obj.date = date ? date > 31 || date < 1 ? -1 : date : -1;
    date_obj.year = year ? year < 0 ? -1 : year : -1;
    
    if (month == NULL || month[0] == '\0') {
        strcpy(month, "Undefined");
    }

    strcpy(date_obj.month, month);

    return date_obj;
}

Address make_address(char houseNo[11], char street[51], char city[51], char province[51], char postCode[11]) {
    Address address_obj;

    if (houseNo == NULL || houseNo[0] == '\0') {
        strcpy(houseNo, "NaN");
    }

    if (street == NULL || street[0] == '\0') {
        strcpy(street, "Undefined");
    }

    if (city == NULL || city[0] == '\0') {
        strcpy(city, "Undefined");
    }

    if (province == NULL || province[0] == '\0') {
        strcpy(city, "Undefined");
    }

    if (postCode == NULL || postCode[0] == '\0') {
        strcpy(city, "NaN");
    }

    strcpy(address_obj.houseNo, houseNo);
    strcpy(address_obj.street, street);
    strcpy(address_obj.city, city);
    strcpy(address_obj.province, province);
    strcpy(address_obj.postcode, postCode);

    return address_obj;
}

Citizen make_citizen(char name[21], char surname[21], char citizenID[14], Gender gender, Status status, PersonState personState, char religion[21], char fatherRecordID[255], char motherRecordID[255], Date dateOfBirth, Address address, char spouseID[255]) {
    Citizen citizen_obj;

    if (name == NULL || name[0] == '\0') {
        strcpy(name, "Unnamed");
    }

    if (surname == NULL || surname[0] == '\0') {
        strcpy(surname, "Undefined");
    }

    if (citizenID == NULL || citizenID[0] == '\0') {
        strcpy(citizenID, "NaN");
    }

    if (religion == NULL || religion[0] == '\0') {
        strcpy(religion, "Unknown");
    }

    if (fatherRecordID == NULL || fatherRecordID[0] == '\0') {
        strcpy(fatherRecordID, "NaN");
    }

    if (motherRecordID == NULL || motherRecordID[0] == '\0') {
        strcpy(motherRecordID, "NaN");
    }

    if (spouseID == NULL || spouseID[0] == '\0') {
        strcpy(spouseID, "NaN");
    }

    strcpy(citizen_obj.name, name);
    strcpy(citizen_obj.surname, surname);
    strcpy(citizen_obj.citizenID, citizenID);

    citizen_obj.gender = gender;
    citizen_obj.status = status;
    citizen_obj.personState = personState;

    strcpy(citizen_obj.religion, religion);
    strcpy(citizen_obj.fatherRecordID, fatherRecordID);
    strcpy(citizen_obj.motherRecordID, motherRecordID);

    citizen_obj.dateOfBirth = dateOfBirth;
    citizen_obj.address = address;

    strcpy(citizen_obj.spouseID, spouseID);

    return citizen_obj;
}

void genderToString(Gender gender, char* buffer) {
    switch (gender) {
        case MALE: strcpy(buffer, "Male"); break;
        case FEMALE: strcpy(buffer, "Female"); break;
        default: strcpy(buffer, "Unknown Gender"); break;
    }
}

void statusToString(Status status, char* buffer) {
    switch (status) {
        case SINGLE: strcpy(buffer, "Single"); break;
        case MARRIED: strcpy(buffer, "Married"); break;
        case DIVORCED: strcpy(buffer, "Divorced"); break;
        case WIDOWED: strcpy(buffer, "Widowed"); break;
        default: strcpy(buffer, "Unknown Status"); break;
    }
}

void personStateToString(PersonState state, char* buffer) {
    switch (state) {
        case ALIVE: strcpy(buffer, "Alive"); break;
        case DECEASED: strcpy(buffer, "Deceased"); break;
        case DISAPPEARED: strcpy(buffer, "Disappeared"); break;
        case UNKNOWN: strcpy(buffer, "Unknown"); break;
        default: strcpy(buffer, "Unknown State"); break;
    }
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
    int id = 1;
    char id_char[512];
    char line[512];

    fgets(line, sizeof(line), file); // Skip header

    while (fgets(line, sizeof(line), file)) {
        char name[21], surname[21], citizenID[14];
        char gender_str[7], status_str[10], personState_str[12];
        char religion[21], fatherRecordID[255], motherRecordID[255];
        char spouseID[255];
        int date, year;
        char month[11];
        char houseNo[11], street[51], city[51], province[51], postcode[11];

        sscanf(line, "%20[^,],%20[^,],%13[^,],%6[^,],%9[^,],%11[^,],%20[^,],%254[^,],%254[^,],%d,%10[^,],%d,%10[^,],%50[^,],%50[^,],%50[^,],%10[^,],%254[^\n]",
               name, surname, citizenID, gender_str, status_str, personState_str,
               religion, fatherRecordID, motherRecordID, &date, month, &year,
               houseNo, street, city, province, postcode, spouseID);

        // Map enums
        Gender gender = strcmp(gender_str, "MALE") == 0 ? MALE : FEMALE;
        Status status = strcmp(status_str, "SINGLE") == 0 ? SINGLE :
                        strcmp(status_str, "MARRIED") == 0 ? MARRIED :
                        strcmp(status_str, "DIVORCED") == 0 ? DIVORCED : WIDOWED;
        PersonState personState = strcmp(personState_str, "ALIVE") == 0 ? ALIVE :
                                  strcmp(personState_str, "DECEASED") == 0 ? DECEASED :
                                  strcmp(personState_str, "DISAPPEARED") == 0 ? DISAPPEARED : UNKNOWN;

        Date dob = make_date(date, month, year);
        Address addr = make_address(houseNo, street, city, province, postcode);

        Record citizen_record, address_record;

        concatDate(date_buffer, dob);
        sprintf(id_char, "%d", id);

        //printf("%d, %s\n", id, id_char);

        address_record = make_record(id_char, "sssss", addr.houseNo, addr.street, addr.city, addr.province, addr.postcode);
        unsafePush(DATA_ADDRESS, address_record);

        citizen_record = make_record(id_char, "sssdddssssds", name, surname, citizenID, gender, status, personState, religion, fatherRecordID, motherRecordID, date_buffer, id, spouseID);
        unsafePush(DATA_CITIZEN, citizen_record);

        id++;

        if (id % 1000 == 0) {
            printf("Register record checkpoint #%d passed.\n", id);
        }
    }

    fclose(file);
}