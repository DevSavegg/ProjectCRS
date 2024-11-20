#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include "..\register\register.h"
#include "..\reporter\reporter.h"
#include "..\finder\finder.h"

#define bgcl 0
#define textcl 4 
#define count 7
void Birthscreen();
void Marriagescreen();
void Deathscreen();
void Search();
void Searchscreen();
void dissapearscreen();
void prompt();
void UpdaterScreen();

void setConsoleColor(int textColor, int bgColor) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int colorAttribute = (bgColor << 4) | textColor;
    SetConsoleTextAttribute(hConsole, colorAttribute);
}
void printWithBackground(const char *str, int bgColor , int textColor ) {
    setConsoleColor(textColor,bgColor);
    printf(str);
    setConsoleColor(7,0);
}
void title(){
    printf("       _ _   _                                _     _             _   _             \n");
    printf("      (_) | (_)                              (_)   | |           | | (_)            \n");
    printf("   ___ _| |_ _ _______ _ __    _ __ ___  __ _ _ ___| |_ _ __ __ _| |_ _  ___  _ __  \n");
    printf("  / __| | __| |_  / _ \\ '_ \\  | '__/ _ \\/ _` | / __| __| '__/ _` | __| |/ _ \\| '_ \\ \n");
    printf(" | (__| | |_| |/ /  __/ | | | | | |  __/ (_| | \\__ \\ |_| | | (_| | |_| | (_) | | | |\n");
    printf("  \\___|_|\\__|_/___\\___|_| |_| |_|  \\___|\\__, |_|___/\\__|_|  \\__,_|\\__|_|\\___/|_| |_|\n");
    printf("                                         __/ |                                      \n");
    printf("                                        |___/                                       \n");
}
void menu(int select){
    setConsoleColor(4,0);
    title();
    if (abs(select%count) == 1){
        printWithBackground("Birth report",2,4);
        printf("\n");
    }else printWithBackground("Birth report\n",0,4);
  if (abs(select%count) == 2){
             printWithBackground("Marriage report",2,4);
                    printf("\n");

    }else printWithBackground("Marriage report\n",0,4);
    if (abs(select%count) == 3){
                printWithBackground("Decease report",2,4);
                        printf("\n");

    }else printWithBackground("Decease report\n",0,4);
    if (abs(select%count) == 4){
                printWithBackground("Dissapearance Report",2,4);
                        printf("\n");
    }else printWithBackground("Dissapearance Report\n",0,4);
    if (abs(select%count) == 5){
                printWithBackground("Search",2,4);
                        printf("\n");

    }else printWithBackground("Search\n",0,4);
    if (abs(select%count) == 6){
                printWithBackground("Updater",2,4);
                        printf("\n");

    }else printWithBackground("Updater\n",0,4);
   if (abs(select%count) == 0){
             printWithBackground("Exit",2,4);
                    printf("\n");

    }else printWithBackground("Exit\n",0,4);
    printWithBackground("\nUse arrowkey to move and tab to select....",0,4);
    setConsoleColor(7,0);

}
int selector(){
  char key;
   int select = 1;
  menu(select);
  

 while (1+1==2) {
     system("cls");
     menu(select);
    key = getch();
       if (key == 0 || key == 224) { 
            key = getch(); 
            switch (key) {
                case 72:
                    if (select == 0)select = 6;if (select < 0)select++;else select --;
                     break;
                case 80:
                    if (select < 0)select--;else select ++;
                    break;
            }
        }else if(key == 9)break;
 }
return select;
}

int newselector()//this one use w and s instead of arrow(just in case)
{
    char key;
   int select = 1;
  menu(select);
 while (1) {
     system("cls");
     menu(select);
        key = getch(); // Read the actual key
        if(key == 'w'){if (select == 0)select = 6;if (select < 0)select++;else select --;}
        else if (key == 's') {if (select < 0)select--;else select ++;}
        else if(key == 9 )break;
        }
          return abs(select);
          }

void GUI()//main function
{
  int select = newselector();
    if (select%count == 1){Birthscreen();} 
    else if (select%count == 2){Marriagescreen();}      
    else if (select%count == 3){Deathscreen();}
    else if (select%count == 4){dissapearscreen();}
    else if (select%count == 5){Searchscreen();} 
    else if(select%count == 6) UpdaterScreen();
    else system("cls");
}
    
void Birth(){
    printWithBackground("  ___ _     _   _                            _ \n",0,4);
    printWithBackground(" | _ |_)_ _| |_| |_    _ _ ___ __ ___ _ _ __| |\n",0,4);
    printWithBackground(" | _ \\ | '_|  _| ' \\  | '_/ -_) _/ _ \\ '_/ _` |\n",0,4);
    printWithBackground(" |___/_|_|  \\__|_||_| |_| \\___\\__\\___/_| \\__,_|\n",0,4);
}
void Death(){
    printWithBackground("  ___           _   _    \n",0,4);
    printWithBackground(" |   \\ ___ __ _| |_| |_  \n",0,4);
    printWithBackground(" | |) / -_) _` |  _|  ' \\ \n",0,4);
    printWithBackground(" |___/\\___\\__,_|\\__|_||_|\n",0,4);
}
void dissapear(){
     setConsoleColor(4,0);
    printf("   ___  _                                 ___ \n");
    printf("  |   \\(_)___ __ _ _ __ _ __  ___ __ _ _ |__ \\\n");
    printf("  | |) | (_-</ _` | '_ \\ '_ \\/ -_) _` | '_|/_/\n");
    printf("  |___/|_/__/\\__,_| .__/ .__/\\___\\__,_|_| (_)\n");
    printf("                  |_|  |_|                   \n");
    setConsoleColor(7,0);
}
void dissapearscreen(){
system("cls");
char lookfor[255];
prompt(lookfor,"Input ID of a lost person",5);
reportDisappeared(lookfor);
printCitizenInfo(lookfor);
printWithBackground("press any key to go back to menu...",bgcl,textcl);getche();
GUI();}

void Marriage();
void Search(){
    setConsoleColor(4,0);
    printf("  ___                  _    \n");
    printf(" / __| ___ __ _ _ _ __| |_  \n");
    printf(" \\__ \\/ -_) _` | '_/ _| ' \\ \n");
    printf(" |___/\\___\\__,_|_| \\__|_||_|\n");
    printf("                            \n");
    setConsoleColor(7,0);
}

void UpdateT(){
    setConsoleColor(4,0);
    printf(" _   _           _       _       \n");
    printf("| | | |         | |     | |      \n");
    printf("| | | |_ __   __| | __ _| |_ ___ \n");
    printf("| | | | '_ \\ / _` |/ _` | __/ _ \n");
    printf("| |_| | |_) | (_| | (_| | ||  __/\n");
    printf(" \\___/| .__/ \\__,_|\\__,_|\\__\\___|\n");
    printf("      | |                        \n");
    printf("      |_|                        \n");
    setConsoleColor(7,0);
}

void prompt(char *dest,char question[100],int title){

    if (title == 1 )Birth();
    if (title == 2 )Marriage();
    if (title == 3 )Death();
    if (title == 4 )Search();
    if (title == 5 )dissapear();
    if(title == 6) UpdateT();
    char answer[100];
    printf("\n\n");
printWithBackground(question,0,4);printWithBackground("\n>",0,4);gets(answer);fflush(stdin); system("cls");strcpy(dest,answer);
}
void Marriage(){
    printWithBackground("  __  __              _                    ,d88b.d88b,\n",0,4);
    printWithBackground(" |  \\/  |__ _ _ _ _ _(_)__ _ __ _ ___      88888888888\n",0,4);
    printWithBackground(" | |\\/| / _` | '_| '_| / _` / _` / -_)     `Y8888888Y'\n",0,4);
    printWithBackground(" |_|  |_\\__,_|_| |_| |_\\__,_\\__,\\___|        `Y888Y'\n",0,4);
    printWithBackground("                            |___/              `Y'\n",0,4);


}
void searchByIDScr(){
    system("cls");
    char lookfor[255];
    prompt(lookfor,"Input Person ID",4);
    setConsoleColor(4,0);
    printCitizenInfo(lookfor);
    setConsoleColor(7,0);
    printWithBackground("press any key to go back to menu...",bgcl,textcl);getche();
    GUI();
}

void searchByNameScr(){
    system("cls");
    char fName[50], lName[50];
    prompt(fName,"Input Person Name",4);
    prompt(lName,"Input Person Surname",4);
    setConsoleColor(4,0);
    Citizen cit;
    fetchByFullName(&cit, fName, lName);
    printCitizenInfo(cit.citizenID);
    setConsoleColor(7,0);
    printWithBackground("press any key to go back to menu...",bgcl,textcl);getche();
    GUI();
}

void searchMenu(int select){
    setConsoleColor(4,0);
    title();
    if (abs(select%3) == 1){
        printWithBackground("Search by ID",2,4);
        printf("\n");
    }else printWithBackground("Search by ID\n",0,4);
    if (abs(select%3) == 2){
             printWithBackground("Search by Name",2,4);
                    printf("\n");

    }else printWithBackground("Search by Name\n",0,4);
    if (abs(select%3) == 0){
                printWithBackground("Back",2,4);
                        printf("\n");

    }else printWithBackground("Back", 0, 4);
    printWithBackground("\nUse arrowkey to move and tab to select....",0,4);
    setConsoleColor(7,0);
}

int searchSelector(){
    char key;
    int select = 1;
    searchMenu(select);
    while (1) {
     system("cls");
     searchMenu(select);
        key = getch(); // Read the actual key
        if(key == 'w'){if (select == 0)select = 6;if (select < 0)select++;else select --;}
        else if (key == 's') {if (select < 0)select--;else select ++;}
        else if(key == 9 )break;
        }
          return abs(select);
}

void Searchscreen(){
    int select = searchSelector();
    if (select%3 == 1){searchByIDScr();} 
    else if (select%3 == 2){searchByNameScr();}
    else GUI();
}



void updateMenu(int select){
    setConsoleColor(4,0);
    title();
    if (abs(select%3) == 1){
        printWithBackground("Update Name",2,4);
        printf("\n");
    }else printWithBackground("Update Name\n",0,4);
    if (abs(select%3) == 2){
             printWithBackground("Update Surname",2,4);
                    printf("\n");

    }else printWithBackground("Update Surname\n",0,4);
    if (abs(select%3) == 0){
                printWithBackground("Back",2,4);
                        printf("\n");

    }else printWithBackground("Back", 0, 4);
    printWithBackground("\nUse arrowkey to move and tab to select....",0,4);
    setConsoleColor(7,0);
}

int updateSelector(){
    char key;
    int select = 1;
    updateMenu(select);
    while (1) {
     system("cls");
     updateMenu(select);
        key = getch(); // Read the actual key
        if(key == 'w'){if (select == 0)select = 6;if (select < 0)select++;else select --;}
        else if (key == 's') {if (select < 0)select--;else select ++;}
        else if(key == 9 )break;
        }
          return abs(select);
}

void updateNameScr(int what){
    char id[255];
    char toChange[50];
    prompt(id,"Input Person ID",6);
    prompt(toChange, "Change to >> ", 6);
    reportChangeName(what, id, toChange);
    printCitizenInfo(id);
    printWithBackground("press any key to go back to menu...",bgcl,textcl);getche();
    GUI();
}

void UpdaterScreen(){
    int select = updateSelector();
    system("cls");
    if (select%3 == 1){updateNameScr(1);} 
    else if (select%3 == 2){updateNameScr(2);}
    else GUI();
}

void strtolower(char string[255]){
    int i = 0;
    for(; string[i] != '\0'; i++)
        if(string[i] >= 'A' && string[i] <= 'Z') string[i] = string[i]-'A'+'a';
    
}

void Birthscreen()
{
    system("cls");
   char name[21];prompt(name,"Input Name",1);
   char gender[11];prompt(gender,"Input Gender",1);
   char day[3];prompt(day,"Input Day",1);
    int days = atoi(day);
    char month[11]; prompt(month, "Input Month", 1);
    int months = atoi(month);
    char year[5];prompt(year,"Input Year",1);
    int years = atoi(year);
char religion[11]; prompt(religion, "Input Religion", 1);
  strtolower(gender);
   Gender genders;
   if (strcmp(gender,"male")==0)genders = MALE;
   else if (strcmp(gender,"female")==0)genders = FEMALE;
   else {printf("invalid");getch();}
   char dadid[21];prompt(dadid,"Input Father ID",1);
   char momid[21];prompt(momid,"Input Mother ID",1);
   printf("%s %s %s %d %s %d %d %d",dadid,momid,name,genders,religion,days,months,years);
   reportBirth(dadid,momid,name,genders,religion,make_date(days,months,years));
   Citizen buf;
   fetchByName(&buf, name);
   printCitizenInfo(buf.citizenID);
  GUI();

}
/*void Birthscreen()
{
    system("cls");
   char name[21];
   prompt(name,"Input Name",1);
    char surname[21];
   prompt(surname,"Input Surname",1);
   char ID[14];
   prompt(ID,"Input ID",1);
    char day[3];prompt(day,"Input Day",1);
    int days = atoi(day);
    char month[11]; prompt(month, "Input Month", 1);
    char year[5];prompt(year,"Input Year",1);
    int years = atoi(year);
    char house[11]; prompt(house, "Input House ID", 1);
    char Street[51]; prompt(Street, "Input Street name", 1);
    char city[51]; prompt(city, "Input City", 1);
    char Province[51]; prompt(Province, "Input Province", 1);
    char postal[11]; prompt(postal, "Input Postal-code", 1);
    char gender[11]; prompt(gender, "Input Gender", 1);
    char status[11]; prompt(status, "Input Person status", 1);
    char religion[11]; prompt(religion, "Input Religion", 1);
    char father[255]; prompt(father, "Input Father ID", 1);
    char mother[255]; prompt(mother, "Input Mother ID", 1);
    char spouse[255]; prompt(spouse, "Input Spouse ID", 1);
    int i = registerCitizen(name,surname,ID,make_date(days,month,years),make_address(house,Street,city,Province,postal),gender,status,"Alive",religion,father,mother,spouse);
    char id[255];
    sprintf(id,"%d",i);
    setConsoleColor(4,0);
    printCitizenInfo(id);
    printf("%s Search ID is %s",name,id);
    setConsoleColor(7,0);
    printWithBackground("\n\nRegisterd! press any key to go back to menu...",bgcl,textcl);getche();
   
    GUI();
}  */
void Deathscreen(){
    system("cls");
    char ID[14];prompt(ID,"Input Deceased person ID",3);
    reportDeceased(ID);
    char buffer[255];
    fetchRawRecordID(buffer,ID);
    printCitizenInfo(buffer);
    printf("%s",ID);
    printWithBackground("\n\nwe are sorry for your loss...press any key to go back to menu...",0,4);getche();
    GUI();}
void Marriagescreen(){
    system("cls");
    char husband[14];prompt(husband,"Input Husband ID",2);
    char wife[14];prompt(wife,"Input Wife ID",2);
    reportMarriage(husband,wife);
    printCitizenInfo(husband);
    printCitizenInfo(wife);
    printWithBackground("\n\nCongratulation on the new couple! press any key to go back to menu...",0,4);getche();

    GUI();} 
