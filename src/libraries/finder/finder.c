#include "finder.h"

// Variables

char temp_name[21];
char temp_id[14];

// Private Functions

int finder_foreach(Citizen *dest, Citizen (*funcName)(Record), char fileName[255]){
    int i;
    int count = 0;
    Citizen temp;

    FILE* file = fopen(fileName, "rb");
    if(file == NULL){
        printf("Unable to open file %s\n", fileName);
        fclose(file);
        return -1;
    }
    Record rec;
    while(fread(&rec, sizeof(Record), 1, file) == 1){
        temp = funcName(rec);

        if (strcmp(temp.name, "-") != 0) {
            dest[count] = temp;
            count++;
        }
    }
    fclose(file);

    return count;
}

Citizen fetchNameFunction(Record rec) {
    // printf("%s %s \n", rec.data[0], temp_name);
    if (strcmp(rec.data[0], temp_name) == 0) {
        int trash;

        Record tmp_address, tmp_contact;

        tmp_address = fastFetchRecord(DATA_ADDRESS, atoi(rec.data[4]), &trash);
        tmp_contact = fastFetchRecord(DATA_CONTACT, atoi(rec.data[5]), &trash);

        int d, y;
        char m[11];

        sscanf(rec.data[3], "%d/%s/%d", &d, m, &y);

        return make_citizen(
            rec.data[0],
            rec.data[1],
            rec.data[2],
            make_date(d, m, y),
            make_address(
                tmp_address.data[0],
                tmp_address.data[1],
                tmp_address.data[2],
                tmp_address.data[3],
                tmp_address.data[4]
            ),
            make_contact(
                tmp_contact.data[0],
                tmp_contact.data[1]
            )
        );
    } else {
        return NULLCITIZEN;
    }
}

Citizen fetchIdFunction(Record rec) {
    // printf("%s %s \n", rec.data[0], temp_name);
    if (strcmp(rec.data[2], temp_id) == 0) {
        int trash;

        Record tmp_address, tmp_contact;
        tmp_address = fastFetchRecord(DATA_ADDRESS, atoi(rec.data[4]), &trash);
        tmp_contact = fastFetchRecord(DATA_CONTACT, atoi(rec.data[5]), &trash);

        int d, y;
        char m[11];

        sscanf(rec.data[3], "%d/%s/%d", &d, m, &y);

        return make_citizen(
            rec.data[0],
            rec.data[1],
            rec.data[2],
            make_date(d, m, y),
            make_address(
                tmp_address.data[0],
                tmp_address.data[1],
                tmp_address.data[2],
                tmp_address.data[3],
                tmp_address.data[4]
            ),
            make_contact(
                tmp_contact.data[0],
                tmp_contact.data[1]
            )
        );
    } else {
        return NULLCITIZEN;
    }
}

// Public Functions

int fetchByName(Citizen *dest, char name[21]) {
    strcpy(temp_name, name);
    return finder_foreach(dest, fetchNameFunction, DATA_CITIZEN);
};

int fetchByCitizenId(Citizen *dest, char citizenId[14]) {
    strcpy(temp_id, citizenId);
    return finder_foreach(dest, fetchIdFunction, DATA_CITIZEN);
};