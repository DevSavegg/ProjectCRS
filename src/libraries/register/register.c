#include "register.h"

#define DATA_CITIZEN "Citizens.dat"
#define DATA_ADDRESS "Addresses.dat"
#define DATA_CONTACT "Contacts.dat"
#define DATA_CRIME "Crimes.dat"


/*

- Database structure -

name, surname, id, dateOfBirth, address_id, contact_id

*/

// Private Functions

void concatDate(char *buffer, Date date) {
    sprintf(buffer, "%d/%s/%d", date.date, date.month, date.year);

    return;
}

// Library Functions

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