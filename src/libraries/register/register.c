#include "register.h"

/*

- Database structure -

name, surname, id, dateOfBirth, address_id, contact_id

*/

// Private Functions //

void concatDate(char *buffer, Date date) {
    sprintf(buffer, "%d/%s/%d", date.date, date.month, date.year);

    return;
}

// Library Functions //

int registerCitizen(char name[21], char surname[21], char ID[14], Date dateOfBirth, Address address, Contact contact) {
    char date_buffer[18] = {0};
    int contact_id, address_id;

    Record citizen_record, contact_record, address_record;

    concatDate(date_buffer, dateOfBirth);

    contact_record = imake_record("ss", contact.phone, contact.email);
    ipush(DATA_CONTACT, contact_record);
    contact_id = record_size(DATA_CONTACT);

    address_record = imake_record("sssss", address.houseNo, address.street, address.city, address.province, address.postcode);
    ipush(DATA_ADDRESS, address_record);
    address_id = record_size(DATA_ADDRESS);

    citizen_record = imake_record("ssssdd", name, surname, ID, date_buffer, address_id, contact_id);
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

Contact make_contact(char phone[11], char email[51]) {
    Contact contact_obj = {
        .phone = "-",
        .email = "-"
    };

    if (phone != NULL && phone[0] != '\0') {
        strcpy(contact_obj.phone, phone);
    }

    if (email != NULL && email[0] != '\0') {
        strcpy(contact_obj.email, email);
    }

    return contact_obj;
}

Citizen make_citizen(char name[21], char surname[21], char id[14], Date dateOfBirth, Address address, Contact contact) {
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
    citizen_obj.contact = contact;

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
        int date, year;
        char month[11];
        char houseNo[11], street[51], city[51], province[51], postcode[11];
        char phone[11], email[51];

        sscanf(line, "%20[^,],%20[^,],%13[^,],%d,%10[^,],%d,%10[^,],%50[^,],%50[^,],%50[^,],%10[^,],%10[^,],%50[^\n]",
               name, surname, citizenID,
               &date, month, &year,
               houseNo, street, city, province, postcode,
               phone, email);

        Date dob = make_date(date, month, year);
        Address addr = make_address(houseNo, street, city, province, postcode);
        Contact contact = make_contact(phone, email);

        Record citizen_record, contact_record, address_record;

        concatDate(date_buffer, dob);
        sprintf(id_char, "%d", id);

        //printf("%d, %s\n", id, id_char);

        contact_record = make_record(id_char, "ss", contact.phone, contact.email);
        unsafePush(DATA_CONTACT, contact_record);

        address_record = make_record(id_char, "sssss", addr.houseNo, addr.street, addr.city, addr.province, addr.postcode);
        unsafePush(DATA_ADDRESS, address_record);

        citizen_record = make_record(id_char, "ssssdd", name, surname, citizenID, date_buffer, id, id);
        unsafePush(DATA_CITIZEN, citizen_record);

        id++;

        if (id % 1000 == 0) {
            printf("Register record checkpoint #%d passed.\n", id);
        }
    }

    fclose(file);
}