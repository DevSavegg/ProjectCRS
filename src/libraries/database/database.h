#ifndef DATABASE_H
#define DATABASE_H

#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
typedef struct {
    char id[255];
    char data[50][255];
    int size;
} Record;

#define NULLRECORD (Record){"NULLRECORD", {{"NULL"}}}

Record fetchRecord(char[255], char[255], int*);
void fetch(char[255], char[255],  int, char[255], int*);
Record fastFetchRecord(char[255], long long int, int*);

void push(char[255],Record);
void ipush(char[255], Record);
void unsafePush(char[255], Record); // DO NOT USE

void del(char[255],char[255],int *);
void update(char[255], char[255], int,char[255], int*);

Record make_record(char[255], char[255], ...);
Record imake_record(char[255], ...);

void printRecord(Record);
void printTBL(char[255]);

int isNullRecord(Record);
int record_size(char[255]);

void foreach(void (*)(Record), char[255]);

#endif