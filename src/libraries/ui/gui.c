#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "..\register\register.h"
#include "..\reporter\reporter.h"

#define bgcl 0
#define textcl 4 
#define count 6
void Birthscreen();
void Marriagescreen();
void Deathscreen();
void Search();
void Searchscreen();
void dissapearscreen();
void prompt();

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
    else if (select%count == 5){Searchscreen();} }
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
void prompt(char *dest,char question[100],int title){

    if (title == 1 )Birth();
    if (title == 2 )Marriage();
    if (title == 3 )Death();
    if (title == 4 )Search();
    if (title == 5 )dissapear();
    char answer[100];
    printf("\n\n");
printWithBackground(question,0,4);printWithBackground("\n>",0,4);gets(answer); system("cls");strcpy(dest,answer);
}
void Marriage(){
    printWithBackground("  __  __              _                    ,d88b.d88b,\n",0,4);
    printWithBackground(" |  \\/  |__ _ _ _ _ _(_)__ _ __ _ ___      88888888888\n",0,4);
    printWithBackground(" | |\\/| / _` | '_| '_| / _` / _` / -_)     `Y8888888Y'\n",0,4);
    printWithBackground(" |_|  |_\\__,_|_| |_| |_\\__,_\\__,\\___|        `Y888Y'\n",0,4);
    printWithBackground("                            |___/              `Y'\n",0,4);


}
void Searchscreen(){
system("cls");
char lookfor[255];
prompt(lookfor,"Input Person ID",4);
setConsoleColor(4,0);
   printCitizenInfo(lookfor);
    setConsoleColor(7,0);
printWithBackground("press any key to go back to menu...",bgcl,textcl);getche();
GUI();
}

void form(char ID[14],char name[21],char surname[21],char gender[11],char day[3],char month[11],char year[5],char religion[11],char status[11],char state[11],char house[11],char street[51],char city[51],char province[51],char post[11]){
        printf("+--------------------------------------------------------+\n");
    printf("|                   Citizen Profile                      |\n");
    printf("+--------------------------------------------------------+\n");
    printf("|    Citizen's ID:      %-13s                    |\n", ID);
    printf("|    Name:   %-10s Surname:   %-10s            |\n",name,surname);
    printf("|    Gender:      %-19s                    |\n", gender);
    printf("|                                                        |\n");
    printf("|    Date of Birth:    %s/%s/%-17s                |\n",day,month,year);
    printf("|                                                        |\n");
    printf("|    Religion:    %-22s                 |\n", religion);
    printf("|                                                        |\n");
    printf("|    Status:    %-24s                 |\n", status);
    printf("|    State:    %-25s                 |\n", state);
    printf("+--------------------------------------------------------+\n");
    printf("|                       Address                          |\n");
    printf("+--------------------------------------------------------+\n");
    printf("|   House No.   %-5s           St. %-20s |\n", house,street);
    printf("|   City        %-15s                          |\n", city);
    printf("|   Province    %-15s Post Code   %-5s        |\n", province,post);
    printf("+--------------------------------------------------------+\n");

}
/*void Birthscreen()
{
    char name[21];prompt(name,"Input Name",1);
   char gender[11];prompt(name,"Input Gender",1);
   char religion[11];prompt(name,"Input Religion ID",1);
   char dadid[21];prompt(name,"Input Father ID",1);
   char momid[21];prompt(name,"Input Father ID",1);
   reportBirth(dadid,momid,name,gender,religion);

}*/
void Birthscreen()
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
}  
void Deathscreen(){
    system("cls");
    char ID[14];prompt(ID,"Input Deceased person ID",3);
    printWithBackground("\n\nwe are sorry for your loss...press any key to go back to menu...",0,4);getche();

    GUI();}
void Marriagescreen(){
    system("cls");
    char husband[14];prompt(husband,"Input Husband ID",2);
    char wife[14];prompt(wife,"Input Wife ID",2);
    printWithBackground("\n\nCongratulation on the new couple! press any key to go back to menu...",0,4);getche();

    GUI();} 
