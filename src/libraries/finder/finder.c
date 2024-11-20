#include "finder.h"

static Record *recordBuffer = NULL;
static int resultCount;
static char searchBuffer[255];

// Private Functions

void matchRecordByName(Record rec) {
    if (strcmp(rec.data[0], searchBuffer) == 0) {
        recordBuffer[resultCount++] = rec;
    }
}

void matchRecordBySurname(Record rec) {
    if (strcmp(rec.data[1], searchBuffer) == 0) {
        recordBuffer[resultCount++] = rec;
    }
}

void matchRecordByFullname(Record rec) {
    char tmp[255];
    strcpy(tmp, rec.data[0]);
    strcat(tmp, rec.data[1]);
    if (strcmp(tmp, searchBuffer) == 0) {
        recordBuffer[resultCount++] = rec;
    }
}

void matchRecordByCitizenID(Record rec) {
    if (strcmp(rec.data[2], searchBuffer) == 0) {
        recordBuffer[resultCount++] = rec;
    }
}

// Public Functions

int fetchByName(Citizen *buffer, char name[21]) {
    if (recordBuffer != NULL) {
        free(recordBuffer);
        recordBuffer = NULL;
    }

    resultCount = 0;
    strcpy(searchBuffer, name);

    recordBuffer = malloc(sizeof(Record) * record_size(DATA_CITIZEN));
    if (recordBuffer == NULL) {
        puts("Something went wrong while trying to allocate 'recordBuffer' memory.");
        return -1;
    }

    foreach(matchRecordByName, DATA_CITIZEN);
    
    if (resultCount <= 0) {
        return 0;
    }

    for (int i = 0; i < resultCount; i++) {
        int status;
        Record addressRecord = fastFetchRecord(DATA_ADDRESS, atoll(recordBuffer[i].data[10]), &status);
        if (status == 2) {
            printf("%s %s\n", recordBuffer[i].data[10], recordBuffer[i].data[0]);
        }
        int date, year;
        char month[11];

        sscanf(recordBuffer[i].data[9], "%d/%s/%d", &date, month, &year);

        buffer[i] = make_citizen(
            recordBuffer[i].data[0],
            recordBuffer[i].data[1],
            recordBuffer[i].data[2],
            (Gender)atoi(recordBuffer[i].data[3]),
            (Status)atoi(recordBuffer[i].data[4]),
            (PersonState)atoi(recordBuffer[i].data[5]),
            recordBuffer[i].data[6],
            recordBuffer[i].data[7],
            recordBuffer[i].data[8],
            make_date(
                date,
                month,
                year               
            ),
            make_address(
                addressRecord.data[0],
                addressRecord.data[1],
                addressRecord.data[2],
                addressRecord.data[3],
                addressRecord.data[4]
            ),
            recordBuffer[i].data[11]
        );
    }

    return resultCount;
}

int fetchBySurname(Citizen *buffer, char surname[21]) {
    if (recordBuffer != NULL) {
        free(recordBuffer);
        recordBuffer = NULL;
    }

    resultCount = 0;
    strcpy(searchBuffer, surname);

    recordBuffer = malloc(sizeof(Record) * record_size(DATA_CITIZEN));
    if (recordBuffer == NULL) {
        puts("Something went wrong while trying to allocate 'recordBuffer' memory.");
        return -1;
    }

    foreach(matchRecordBySurname, DATA_CITIZEN);
    
    if (resultCount <= 0) {
        return 0;
    }

    for (int i = 0; i < resultCount; i++) {
        int status;
        Record addressRecord = fastFetchRecord(DATA_ADDRESS, atoll(recordBuffer[i].data[10]), &status);
        if (status == 2) {
            printf("%s %s\n", recordBuffer[i].data[10], recordBuffer[i].data[0]);
        }
        int date, year;
        char month[11];

        sscanf(recordBuffer[i].data[9], "%d/%s/%d", &date, month, &year);

        buffer[i] = make_citizen(
            recordBuffer[i].data[0],
            recordBuffer[i].data[1],
            recordBuffer[i].data[2],
            (Gender)atoi(recordBuffer[i].data[3]),
            (Status)atoi(recordBuffer[i].data[4]),
            (PersonState)atoi(recordBuffer[i].data[5]),
            recordBuffer[i].data[6],
            recordBuffer[i].data[7],
            recordBuffer[i].data[8],
            make_date(
                date,
                month,
                year               
            ),
            make_address(
                addressRecord.data[0],
                addressRecord.data[1],
                addressRecord.data[2],
                addressRecord.data[3],
                addressRecord.data[4]
            ),
            recordBuffer[i].data[11]
        );
    }

    return resultCount;
}

int fetchByFullName(Citizen *buffer, char name[21], char surname[21]) {
    if (recordBuffer != NULL) {
        free(recordBuffer);
        recordBuffer = NULL;
    }

    resultCount = 0;
    strcpy(searchBuffer, name);
    strcat(searchBuffer, surname);

    recordBuffer = malloc(sizeof(Record) * record_size(DATA_CITIZEN));
    if (recordBuffer == NULL) {
        puts("Something went wrong while trying to allocate 'recordBuffer' memory.");
        return -1;
    }

    foreach(matchRecordByFullname, DATA_CITIZEN);
    
    if (resultCount <= 0) {
        return 0;
    }

    for (int i = 0; i < resultCount; i++) {
        int status;
        Record addressRecord = fastFetchRecord(DATA_ADDRESS, atoll(recordBuffer[i].data[10]), &status);
        if (status == 2) {
            printf("%s %s\n", recordBuffer[i].data[10], recordBuffer[i].data[0]);
        }
        int date, year;
        char month[11];

        sscanf(recordBuffer[i].data[9], "%d/%s/%d", &date, month, &year);

        buffer[i] = make_citizen(
            recordBuffer[i].data[0],
            recordBuffer[i].data[1],
            recordBuffer[i].data[2],
            (Gender)atoi(recordBuffer[i].data[3]),
            (Status)atoi(recordBuffer[i].data[4]),
            (PersonState)atoi(recordBuffer[i].data[5]),
            recordBuffer[i].data[6],
            recordBuffer[i].data[7],
            recordBuffer[i].data[8],
            make_date(
                date,
                month,
                year               
            ),
            make_address(
                addressRecord.data[0],
                addressRecord.data[1],
                addressRecord.data[2],
                addressRecord.data[3],
                addressRecord.data[4]
            ),
            recordBuffer[i].data[11]
        );
    }

    return resultCount;
}

int fetchByCitizenID(Citizen *buffer, char citizenID[14]) {
    if (recordBuffer != NULL) {
        free(recordBuffer);
        recordBuffer = NULL;
    }

    resultCount = 0;
    strcpy(searchBuffer, citizenID);

    recordBuffer = malloc(sizeof(Record) * record_size(DATA_CITIZEN));
    if (recordBuffer == NULL) {
        puts("Something went wrong while trying to allocate 'recordBuffer' memory.");
        return -1;
    }

    foreach(matchRecordByCitizenID, DATA_CITIZEN);
    
    if (resultCount <= 0) {
        return 0;
    }

    for (int i = 0; i < resultCount; i++) {
        int status;
        Record addressRecord = fastFetchRecord(DATA_ADDRESS, atoll(recordBuffer[i].data[10]), &status);
        if (status == 2) {
            printf("%s %s\n", recordBuffer[i].data[10], recordBuffer[i].data[0]);
        }
        int date, year;
        char month[11];

        sscanf(recordBuffer[i].data[9], "%d/%s/%d", &date, month, &year);

        buffer[i] = make_citizen(
            recordBuffer[i].data[0],
            recordBuffer[i].data[1],
            recordBuffer[i].data[2],
            (Gender)atoi(recordBuffer[i].data[3]),
            (Status)atoi(recordBuffer[i].data[4]),
            (PersonState)atoi(recordBuffer[i].data[5]),
            recordBuffer[i].data[6],
            recordBuffer[i].data[7],
            recordBuffer[i].data[8],
            make_date(
                date,
                month,
                year               
            ),
            make_address(
                addressRecord.data[0],
                addressRecord.data[1],
                addressRecord.data[2],
                addressRecord.data[3],
                addressRecord.data[4]
            ),
            recordBuffer[i].data[11]
        );
    }

    return resultCount;
}

int fetchRawRecordID(char *buffer, char citizenID[14]) {
    if (recordBuffer != NULL) {
        free(recordBuffer);
        recordBuffer = NULL;
    }

    resultCount = 0;
    strcpy(searchBuffer, citizenID);

    recordBuffer = malloc(sizeof(Record) * record_size(DATA_CITIZEN));
    if (recordBuffer == NULL) {
        puts("Something went wrong while trying to allocate 'recordBuffer' memory.");
        return -1;
    }

    foreach(matchRecordByCitizenID, DATA_CITIZEN);
    
    if (resultCount <= 0) {
        return 0;
    }

    strcpy(buffer, recordBuffer[0].id);

    return resultCount;
}