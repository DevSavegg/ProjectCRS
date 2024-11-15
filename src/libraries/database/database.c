#include "hdr/database.h"
#include <stdio.h>
#include <string.h>
#include <errno.h>
struct Record fetchRecord(char fileName[255], char id[255], int *status){
    FILE* file = fopen(fileName, "rb");
    struct Record record;
    if (file == NULL) {
        printf("Unable to open file %s\n", fileName);
        *status = 1;
        return (struct Record){"NULLRECORD", {{"NULL"}}};
    }
    while (fread(&record, sizeof(struct Record), 1, file) == 1) {
        if (strcmp(record.id, id) == 0) {
            *status = 0;
            fclose(file);
            struct Record result = record;
            return result;
        }
    }
    printf("Record[%s] not found\n", id);
    *status = 2;
    fclose(file);
    return (struct Record){"NULLRECORD", {{"NULL"}}};
}
void fetch(char fileName[255], char id[255],  int attributeCol, char result[255], int *status){
    struct Record record;
    fetchRecord(fileName, id, status);
    if(status){
        printf("An error occured\n");
        return;
    }
    strcpy(result, record.data[attributeCol-1]);
}

void push(char fileName[255], struct Record record){
    FILE* file = fopen(fileName, "rb");
    FILE* tempFile = fopen("tempFile.tmp", "wb");
    int found = 0;
    struct Record reading;

    // Check if the main file doesn't exist
    if (file == NULL) {
        // If the file doesn't exist, create it and write the first record
        file = fopen(fileName, "wb");
        if (file == NULL) {
            perror("Error opening file");
            if (tempFile) fclose(tempFile);
            return;
        }
        fwrite(&record, sizeof(struct Record), 1, file);
        fclose(file);
        fclose(tempFile);
        return;
    }

    // Read through the file and update/overwrite records as needed
    while (fread(&reading, sizeof(struct Record), 1, file) == 1) {
        if (strcmp(record.id, reading.id) == 0) {
            fwrite(&record, sizeof(struct Record), 1, tempFile);
            found = 1;
        } else {
            fwrite(&reading, sizeof(struct Record), 1, tempFile);
        }
    }

    // If the record wasn't found, append the new record
    if (!found) {
        fwrite(&record, sizeof(struct Record), 1, tempFile);
    }

    // Close the files properly
    fclose(file);
    fclose(tempFile);

    // Remove the original file and rename the temporary file
    if (remove(fileName) != 0) {
        perror("Error removing original file");
        return;
    }

    if (rename("tempFile.tmp", fileName) != 0) {
        printf("Rename failed: %s\n", strerror(errno));
    }
}
void delete(char fileName[255], char id[255], int *status){
    FILE* file = fopen(fileName, "rb");
    FILE* tempFile = fopen("tempFile.tmp", "wb");
    struct Record reading;
    if(file == NULL){
        printf("Unable to open file %s\n", fileName);
        *status = 1;
        fclose(file);
        fclose(tempFile);
        return;
    }

    while(fread(&reading, sizeof(struct Record), 1, file) == 1){
        if(strcmp(id, reading.id) == 0){
            continue;
        }else {
            fwrite(&reading, sizeof(struct Record), 1, tempFile);
        }
    }

    fclose(file);
    fclose(tempFile);

    remove(fileName);
    rename("tempFile.tmp", fileName);
    *status = 0;
}
void update(char fileName[255], char id[255], int dataCol,void *data, int *status){
    FILE* file = fopen(fileName, "rb");
    FILE* tempFile = fopen("tempFile.tmp", "wb");
    struct Record reading;
    int found = 0;
    if(file == NULL){
        printf("Unable to open file %s\n", fileName);
        *status = 1;
        fclose(file);
        fclose(tempFile);
        return;
    }

    while(fread(&reading, sizeof(struct Record), 1, file) == 1){
        if(strcmp(id, reading.id) == 0){
            strcpy(reading.data[dataCol], (char*)data);
            found = 1;
            fwrite(&reading, sizeof(struct Record), 1, tempFile);
            *status = 0;
        }else {
            fwrite(&reading, sizeof(struct Record), 1, tempFile);
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
struct Record make_record(char id[255], char format[255], ...){
    va_list args;
    va_start(args, format);
    struct Record record;
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


void printRecord(struct Record record){
    int i;
    printf("|%10s|", record.id);
    for(i = 0; i < record.size; i++){
        printf("%10s|", record.data[i]);
    }
    printf("\n");
}

void printTBL(char fileName[255]){
    struct Record rec;
    int i;
    FILE* file = fopen(fileName, "rb");
    if(file == NULL){
        printf("Unable to open file %s\n", fileName);
        fclose(file);
        return;
    }
    fread(&rec, sizeof(struct Record), 1, file);
    for(i = 0; i <= rec.size; i++) printf("%11d", i);
    printf("\n");
    printRecord(rec);
    while(fread(&rec, sizeof(struct Record), 1, file) == 1){
        printRecord(rec);
    }
    for(i = 0; i <= rec.size; i++) printf("-----------");
    printf("\n");
    fclose(file);
}


int isNullRecord(struct Record record){
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
    struct Record rec;
    for(;fread(&rec, sizeof(struct Record), 1, file) == 1; i++);
    fclose(file);
    return i;
}

void foreach(void (*funcName)(struct Record), char fileName[255]){
    int i;
    FILE* file = fopen(fileName, "rb");
    if(file == NULL){
        printf("Unable to open file %s\n", fileName);
        fclose(file);
        return;
    }
    struct Record rec;
    while(fread(&rec, sizeof(struct Record), 1, file) == 1){
        funcName(rec);
    }
    fclose(file);
}
