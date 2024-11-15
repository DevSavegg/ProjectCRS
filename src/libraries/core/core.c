#include "core.h"

void initialize() {
    Record rec1 = imake_record("ssf", "Naphon", "Jangjit", 4900000.5);
    Record rec2 = imake_record("ssf", "Chetniphat", "Pokin", 1234.9);
    Record rec3 = imake_record("ssf", "Jeerawat", "Kromsang", 45.61);
    Record rec4 = imake_record("ssf", "Phonlawat", "SiaO", 9999999.4);
    Record rec5 = imake_record("ssf", "Dad's", "Tree", 100.5);
    ipush("nigga.dat", rec1);ipush("nigga.dat", rec2);ipush("nigga.dat", rec3);ipush("nigga.dat", rec4);ipush("nigga.dat", rec5);
    printTBL("nigga.dat");
}