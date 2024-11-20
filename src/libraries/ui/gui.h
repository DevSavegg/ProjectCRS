#ifndef GUI_H
#define GUI_H
#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include <math.h>
#define bgcl 0
#define textcl 4 
#define count 4
void setConsoleColor(int textColor, int bgColor);
void printWithBackground(const char *str, int bgColor , int textColor );
void title();
void menu(int select);
int selector();
int newselector();
void Birthscreen();
void Marriagescreen();
void Deathscreen();
void dissapearscreen();
void GUI();
void Birth();
void Death();
void Marriage();
void dissapearscreen();
void Search();
void Searchscreen();
void Birthscreen();
void Deathscreen();
void Marriagescreen();


#endif