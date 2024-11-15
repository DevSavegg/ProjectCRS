#ifndef DATABASE_H
#define DATABASE_H
#include <stdarg.h>
struct Record{
    char id[255];
    char data[500][255];
    int size;
};


struct Record fetchRecord(char[255], char[255], int*);
void fetch(char[255], char[255],  int, char[255], int*);
void push(char[255],struct Record);
void delete(char[255],char[255],int *);
void update(char[255], char[255], int,void*, int*);
struct Record make_record(char[255], char[255], ...);
void printRecord(struct Record);
void printTBL(char[255]);
int isNullRecord(struct Record);
int record_size(char[255]);
void foreach(void (*)(struct Record), char[255]);
#endif