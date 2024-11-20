#include "register.h"
#include "../finder/finder.h"
#include "../utils/utils.h"

/*

- Database structure -

name, surname, id, dateOfBirth, address_id

*/

// Private Functions //

void concatDate(char *buffer, Date date) {
    sprintf(buffer, "%d/%d/%d", date.date, date.month, date.year);

    return;
}

// Library Functions //

int reportBirth(char fatherCitizenID[255], char motherCitizenID[255], char childName[21], Gender gender, char religion[21], Date dateOfBirth) {
    char id[14];

    Citizen father_citizen_obj;
    Citizen mother_citizen_obj;

    fetchByCitizenID(&father_citizen_obj, fatherCitizenID);
    fetchByCitizenID(&mother_citizen_obj, motherCitizenID);

    Citizen child_citizen_obj = make_citizen(
        childName,
        father_citizen_obj.surname,
        "-",
        gender,
        SINGLE,
        ALIVE,
        religion,
        fatherCitizenID,
        motherCitizenID,
        dateOfBirth,
        father_citizen_obj.address,
        "-"
    );

    generateCitizenID(id, child_citizen_obj);
    strcpy(child_citizen_obj.citizenID, id);

    Record addressRecord = imake_record("sssss", child_citizen_obj.address.houseNo, child_citizen_obj.address.street, child_citizen_obj.address.city, child_citizen_obj.address.province, child_citizen_obj.address.postcode);
    ipush(DATA_ADDRESS, addressRecord);

    int addressRecordID = getLastRecordId(DATA_ADDRESS);
    char dateBuffer[255];

    concatDate(dateBuffer, child_citizen_obj.dateOfBirth);
    
    Record childRecord = imake_record("sssdddssssds", 
        child_citizen_obj.name,
        child_citizen_obj.surname,
        child_citizen_obj.citizenID,
        child_citizen_obj.gender,
        child_citizen_obj.status,
        child_citizen_obj.personState,
        child_citizen_obj.religion,
        child_citizen_obj.fatherRecordID,
        child_citizen_obj.motherRecordID,
        dateBuffer,
        addressRecordID,
        child_citizen_obj.spouseID
    );
    ipush(DATA_CITIZEN, childRecord);

    return 1;
}

int reportDeceased(char citizenID[14]) {
    int count, i, status;
    char citizenRecordBuffer[255];
    Citizen citizenObjectBuffer;
 
    count = fetchRawRecordID(citizenRecordBuffer, citizenID);
    count = fetchByCitizenID(&citizenObjectBuffer, citizenID);

    if (count <= 0) {
        return -1;
    }

    if (citizenObjectBuffer.status == MARRIED) {
        char tmp[255];
        fetchRawRecordID(tmp, citizenObjectBuffer.spouseID);

        update(DATA_CITIZEN, tmp, 11, "-", &status);
        update(DATA_CITIZEN, tmp, 4, "3", &status);
    }
    update(DATA_CITIZEN, citizenRecordBuffer, 5, "1", &status);

    return 1;
}

int reportDisappeared(char citizenID[14]) {
    int count, i, status;
    char citizenRecordBuffer[255];
 
    count = fetchRawRecordID(citizenRecordBuffer, citizenID);

    if (count <= 0) {
        return -1;
    }

    update(DATA_CITIZEN, citizenRecordBuffer, 5, "2", &status);

    return 1;
}

int reportMarriage(char groomCitizenID[14], char brideCitizenID[14]) {
    int status;
    Citizen groom_citizen_obj;
    Citizen bride_citizen_obj;
    char groomRecordBuffer[255];
    char brideRecordBuffer[255];

    fetchByCitizenID(&groom_citizen_obj, groomCitizenID);
    fetchByCitizenID(&bride_citizen_obj, brideCitizenID);

    fetchRawRecordID(groomRecordBuffer, groomCitizenID);
    fetchRawRecordID(brideRecordBuffer, brideCitizenID);
    
    update(DATA_CITIZEN, groomRecordBuffer, 4, "1", &status);
    update(DATA_CITIZEN, brideRecordBuffer, 4, "1", &status);

    update(DATA_CITIZEN, groomRecordBuffer, 11, brideCitizenID, &status);
    update(DATA_CITIZEN, brideRecordBuffer, 11, groomCitizenID, &status);

    return 1;
}

int reportDivorced(char citizenID[14]) {
    int status;
    Citizen person1_citizen_obj;
    Citizen person2_citizen_obj;
    char person1RecordBuffer[255];
    char person2RecordBuffer[255];

    fetchByCitizenID(&person1_citizen_obj, citizenID);
    fetchByCitizenID(&person2_citizen_obj, person1_citizen_obj.spouseID);

    if (person1_citizen_obj.status != MARRIED) {
        return -1;
    }

    fetchRawRecordID(person1RecordBuffer, person1_citizen_obj.citizenID);
    fetchRawRecordID(person2RecordBuffer, person2_citizen_obj.citizenID);
    
    update(DATA_CITIZEN, person1RecordBuffer, 4, "2", &status);
    update(DATA_CITIZEN, person2RecordBuffer, 4, "2", &status);

    update(DATA_CITIZEN, person1RecordBuffer, 11, "-", &status);
    update(DATA_CITIZEN, person2RecordBuffer, 11, "-", &status);

    return 1;
}

Date make_date(int date, int month, int year) {
    Date date_obj;
    
    date_obj.date = date ? date > 31 || date < 1 ? -1 : date : -1;
    date_obj.month = month ? month > 12 || month < 1 ? -1 : month : -2;
    date_obj.year = year ? year < 0 ? -1 : year : -1;

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

Citizen make_citizen(char name[21], char surname[21], char citizenID[14], Gender gender, Status status, PersonState personState, char religion[21], char fatherCitizenID[255], char motherCitizenID[255], Date dateOfBirth, Address address, char spouseID[255]) {
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

    if (fatherCitizenID == NULL || fatherCitizenID[0] == '\0') {
        strcpy(fatherCitizenID, "NaN");
    }

    if (motherCitizenID == NULL || motherCitizenID[0] == '\0') {
        strcpy(motherCitizenID, "NaN");
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
    strcpy(citizen_obj.fatherRecordID, fatherCitizenID);
    strcpy(citizen_obj.motherRecordID, motherCitizenID);

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
        int month;
        char houseNo[11], street[51], city[51], province[51], postcode[11];

        sscanf(line, "%20[^,],%20[^,],%13[^,],%6[^,],%9[^,],%11[^,],%20[^,],%254[^,],%254[^,],%d,%d,%d,%10[^,],%50[^,],%50[^,],%50[^,],%10[^,],%254[^\n]",
               name, surname, citizenID, gender_str, status_str, personState_str,
               religion, fatherRecordID, motherRecordID, &date, &month, &year,
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