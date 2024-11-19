#include "database.h"

Record fetchRecord(char fileName[255], char id[255], int *status){
    FILE* file = fopen(fileName, "rb");
    *status = -1;
    Record record;
    if (file == NULL) {
        printf("Unable to open file %s\n", fileName);
        *status = 1;
        return NULLRECORD;
    }
    while (fread(&record, sizeof(Record), 1, file) == 1) {
        if (strcmp(record.id, id) == 0) {
            *status = 0;
            fclose(file);
            Record result = record;
            return result;
        }
    }
    printf("Record[%s] not found\n", id);
    *status = 2;
    fclose(file);
    return NULLRECORD;
}

Record fastFetchRecord(char fileName[255], int id, int*status){
    FILE* file = fopen(fileName, "rb");
    Record rec;
    *status = -1;
    if(file == NULL){
        printf("Unable to open file %s.\n", fileName);
        *status = 1;
        return NULLRECORD;
    }
    int toMove = id * sizeof(Record), lastID = id, currentLine;
    while(fseek(file, toMove, SEEK_SET) != 0 && toMove >= 0) toMove = (id--) * sizeof(Record); //If Not found record, read until found
    currentLine = toMove/sizeof(Record);
    if(currentLine < 0){
        printf("File %s is empty.\n", fileName);
        *status = 3;
        return NULLRECORD;
    }
    fseek(file, -2 * sizeof(Record), SEEK_CUR);
    fread(&rec, sizeof(Record), 1, file);
    if(atoi(rec.id) != id){
        while(1){
            fread(&rec, sizeof(Record), 1, file);
            if(atoi(rec.id) == id) break;
            lastID = atoi(rec.id);
            if(lastID < id || lastID-1 < 0){
                printf("Record is not found.: %d\n", lastID);
                *status = 2;
                return NULLRECORD;
            }
            fseek(file, -2 * sizeof(Record), SEEK_CUR);
        }

        *status = 0;
    }
    fclose(file);
    return rec;
}

void fetch(char fileName[255], char id[255],  int attributeCol, char result[255], int *status){
    Record record = fetchRecord(fileName, id, status);
    if(*status != 0){
        printf("An error occured\n");
        printf("status = %d\n", *status);
        return;
    }
    strcpy(result, record.data[attributeCol]);
}

void push(char fileName[255], Record record){
    FILE* file = fopen(fileName, "rb");
    FILE* tempFile = fopen("tempFile.tmp", "wb");
    int found = 0;
    Record reading;

    // Check if the main file doesn't exist
    if (file == NULL) {
        // If the file doesn't exist, create it and write the first record
        file = fopen(fileName, "wb");
        if (file == NULL) {
            perror("Error opening file");
            if (tempFile) fclose(tempFile);
            return;
        }
        fwrite(&record, sizeof(Record), 1, file);
        fclose(file);
        fclose(tempFile);
        return;
    }

    // Read through the file and update/overwrite records as needed
    while (fread(&reading, sizeof(Record), 1, file) == 1) {
        if (strcmp(record.id, reading.id) == 0) {
            fwrite(&record, sizeof(Record), 1, tempFile);
            found = 1;
        } else {
            fwrite(&reading, sizeof(Record), 1, tempFile);
        }
    }

    if (!found) {
        fwrite(&record, sizeof(Record), 1, tempFile);
    }

    fclose(file);
    fclose(tempFile);

    if (remove(fileName) != 0) {
        perror("Error removing original file");
        return;
    }

    if (rename("tempFile.tmp", fileName) != 0) {
        printf("Rename failed: %s\n", strerror(errno));
    }
}
void del(char fileName[255], char id[255], int *status){
    FILE* file = fopen(fileName, "rb");
    FILE* tempFile = fopen("tempFile.tmp", "wb");
    Record reading;
    if(file == NULL){
        printf("Unable to open file %s\n", fileName);
        *status = 1;
        fclose(file);
        fclose(tempFile);
        return;
    }

    while(fread(&reading, sizeof(Record), 1, file) == 1){
        if(strcmp(id, reading.id) == 0){
            continue;
        }else {
            fwrite(&reading, sizeof(Record), 1, tempFile);
        }
    }

    fclose(file);
    fclose(tempFile);

    remove(fileName);
    rename("tempFile.tmp", fileName);
    *status = 0;
}
void update(char fileName[255], char id[255], int dataCol,char data[255], int *status){
    FILE* file = fopen(fileName, "rb");
    FILE* tempFile = fopen("tempFile.tmp", "wb");
    Record reading;
    int found = 0;
    if(file == NULL){
        printf("Unable to open file %s\n", fileName);
        *status = 1;
        fclose(file);
        fclose(tempFile);
        return;
    }

    while(fread(&reading, sizeof(Record), 1, file) == 1){
        if(strcmp(id, reading.id) == 0){
            strcpy(reading.data[dataCol], data);
            found = 1;
            fwrite(&reading, sizeof(Record), 1, tempFile);
            *status = 0;
        }else {
            fwrite(&reading, sizeof(Record), 1, tempFile);
        }
    }
    
    fclose(file);
    fclose(tempFile);

    if(found){
        remove(fileName);
        rename("./tempFile.tmp", fileName);
    }else{
        *status = 2;
    }
}
Record make_record(char id[255], char format[255], ...){
    va_list args;
    va_start(args, format);
    Record record;
    strcpy(record.id, id);

    int i = 0;
    for (; format[i] != '\0'; i++) {
        if (format[i] == 's') {
            strcpy(record.data[i], va_arg(args, char*));
        } else if (format[i] == 'd') {
            sprintf(record.data[i], "%d", va_arg(args, int));
        } else if (format[i] == 'f') {
            sprintf(record.data[i], "%lf", va_arg(args, double));
        } else if (format[i] == 'L') {
            sprintf(record.data[i], "%ld", va_arg(args, long int));
        }
    }
    record.size = i;
    va_end(args);
    return record;
}

Record imake_record(char format[255], ...){
    va_list args;
    va_start(args, format);
    Record record;

    int i = 0;
    for (; format[i] != '\0'; i++) {
        if (format[i] == 's') {
            strcpy(record.data[i], va_arg(args, char*));
        } else if (format[i] == 'd') {
            sprintf(record.data[i], "%d", va_arg(args, int));
        } else if (format[i] == 'f') {
            sprintf(record.data[i], "%lf", va_arg(args, double));
        } else if (format[i] == 'L') {
            sprintf(record.data[i], "%ld", va_arg(args, long int));
        }
    }
    record.size = i;
    va_end(args);
    return record;
}

void printRecord(Record record){
    int i;
    printf("%10s|", record.id);
    for(i = 0; i < record.size; i++){
        printf("%10s|", record.data[i]);
    }
    printf("\n");
}

void printTBL(char fileName[255]){
    Record rec;
    int i;
    FILE* file = fopen(fileName, "rb");
    if(file == NULL){
        printf("Unable to open file %s\n", fileName);
        fclose(file);
        return;
    }
    fread(&rec, sizeof(Record), 1, file);
    for(i = 0; i <= rec.size; i++) printf("%10d", i);
    printf("\n");
    printRecord(rec);
    while(fread(&rec, sizeof(Record), 1, file) == 1){
        printRecord(rec);
    }
    for(i = 0; i <= rec.size; i++) printf("-----------");
    printf("\n");
    fclose(file);
}


int isNullRecord(Record record){
    if(strcmp(record.id, "NULLRECORD") == 0) return 1;
    return 0;
}

int record_size(char fileName[255]){
    int i = 0;
    FILE* file = fopen(fileName, "rb");
    if(file == NULL){
        printf("Unable to open file %s\n", fileName);
        fclose(file);
        return -1;
    }
    Record rec;
    for(;fread(&rec, sizeof(Record), 1, file) == 1; i++);
    fclose(file);
    return i;
}

void foreach(void (*funcName)(Record), char fileName[255]){
    int i;
    FILE* file = fopen(fileName, "rb");
    if(file == NULL){
        printf("Unable to open file %s\n", fileName);
        fclose(file);
        return;
    }
    Record rec;
    while(fread(&rec, sizeof(Record), 1, file) == 1){
        funcName(rec);
    }
    fclose(file);
}

int getLastRecordId(char fileName[255]) {
    FILE *file = fopen(fileName, "rb");
    Record lastRec;
    int id = 0;

    if (file != NULL) {
        while (fread(&lastRec, sizeof(Record), 1, file) == 1);
        if (feof(file)) {
            id = atoi(lastRec.id);
            
        }
        fclose(file);
    }

    return id;
}

void ipush(char fileName[255], Record record){
    FILE *file = fopen(fileName, "rb");
    Record lastRec;
    int id = 0;

    if (file != NULL) {
        while (fread(&lastRec, sizeof(Record), 1, file) == 1);
        if (feof(file)) {
            id = atoi(lastRec.id);
            
        }
        fclose(file);
    }
    id++;
    Record toadd = record;
    sprintf(toadd.id, "%d", id);
    file = fopen(fileName, "ab");
    if (file == NULL) {
        perror("Unable to open file for appending");
        return;
    }
    fwrite(&toadd, sizeof(Record), 1, file);
    fclose(file);
}

void unsafePush(char fileName[255], Record record){
    FILE *file = fopen(fileName, "ab");
    //Record lastRec;
    //int id = record_size(fileName) + 1;
    Record toadd = record;
    //sprintf(toadd.id, "%d", id);
    //file = fopen(fileName, "ab");
    if (file == NULL) {
        perror("Unable to open file for appending");
        return;
    }
    fwrite(&toadd, sizeof(Record), 1, file);
    fclose(file);
}