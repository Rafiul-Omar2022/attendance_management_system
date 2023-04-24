#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define USER_NAME "admin"
#define USER_PASS "admin123"
#define CLASS_COUNT 31


typedef struct database{
    char name[100];
    char id[100];
    int day[CLASS_COUNT];
    int attendance;
}db;


void asciiImg();
void loadingScreen();
void frontInterface();
int loginAccess(char name[], char password[]);
void about();
int login();
void append();
void display();
void takeAttendance();
void search();
void reset_All();
void resetDays();
void update();
void userPage();


int main(){

    asciiImg();
    frontInterface();

    return 0;
}

void append(){
    FILE *fp;
    int size = 0;

    system("cls");
    asciiImg();

    printf("\n\nHow many people do you want to add: ");
    scanf("%d", &size);
    db person[size];

    fp = fopen("database.txt", "a");
    for(int i=0; i<size; i++){
        for(int j=0; j<30; j++) person[i].day[j] = -1;
        printf("\nEnter Id: ");
        scanf(" %s", person[i].id);
        printf("Enter person name: ");
        scanf(" %[^\n]s", person[i].name);
        person[i].attendance = 0;
        fwrite(&person[i], sizeof(db), 1, fp);
    }
    fclose(fp);
}

void display(){
    db person;
    FILE *fp = fopen("database.txt", "r");

    int totalPerson  = 0;

    system("cls");
    asciiImg();

    printf("%9s|\t%12s|\t|1 |2 |3 |4 |5 |6 |7 |8 |9 |10 |11 |12 |13 |14 |15 |16 |17 |18 |19 |20 |21 |22 |23 |24 |25 |26 |27 |28 |29 |30  %s \n","ID","Name","Days");

    while(fread(&person, sizeof(db), 1, fp)){
            printf("%9s|\t%12s|\t", person.id, person.name);
            for(int i=0; i<30; i++) {
                if(i>9){
                    if( person.day[i] == 1 ) printf(" |P ");
                    else if( person.day[i] == -1 ) printf(" |0 ");
                    else printf(" |A ");
                }
                else{
                    if( person.day[i] == 1 ) printf("|P ");
                    else if( person.day[i] == -1 ) printf("|0 ");
                    else printf("|A ");
                }
            }

            printf("  %d", person.attendance);
            printf("\n");
            totalPerson++;
    }
    fclose(fp);
    printf("\n\t\t\t\t\t\tTotal person: %d", totalPerson);
}

void takeAttendance(){
    db person;
    FILE *fp, *fp1;

    system("cls");
    asciiImg();

    fp = fopen("database.txt", "r");
    fp1 = fopen("temp.txt", "w");

    int day;
    printf("Class no: ");
    scanf("%d", &day);

    printf("\nEnter 1 for present, and 0 for absent\n");

    while( fread(&person, sizeof(db), 1, fp )){
        printf("\nID: %s, Name: %s, class no( %d ):  ", person.id, person.name, day);
        int attend;

        scanf("%d", &attend);
        if( attend >= 1 ) person.day[day-1] = 1;
        else person.day[day-1] = 0;

        int totalDays = 0;
        for(int i=0; i<CLASS_COUNT; i++) {
            if(person.day[i] == 1) totalDays += person.day[i];
        }
        person.attendance = totalDays;

        fwrite( &person, sizeof(db), 1, fp1 );
    }

    fclose(fp);
    fclose(fp1);

    fp = fopen("database.txt", "w");
    fp1 = fopen("temp.txt", "r");

    while(fread(&person, sizeof(db), 1, fp1)){
        fwrite(&person, sizeof(db), 1, fp);
    }

    fclose(fp);
    fclose(fp1);

}

void search(){
    db person;
    FILE *fp;

    system("cls");
    asciiImg();

    fp = fopen("database.txt", "r");

    int found = 0;
    char id[50];

    printf("\nEnter person Id to search: ");
    scanf("%s", id);
    printf("\n");
    printf("%9s|\t%12s|\t|1 |2 |3 |4 |5 |6 |7 |8 |9 |10 |11 |12 |13 |14 |15 |16 |17 |18 |19 |20 |21 |22 |23 |24 |25 |26 |27 |28 |29 |30  %s \n","ID","Name","Days");
    printf("\n");
    while(fread(&person, sizeof(db), 1, fp)){
        if(!strcmp(person.id, id)){
            found = 1;
            printf("%9s|\t%12s|\t", person.id, person.name);
            for(int i=0; i<30; i++) {
                if(i>9){
                    if( person.day[i] == 1 ) printf(" |P ");
                    else if( person.day[i] == -1 ) printf(" |0 ");
                    else printf(" |A ");
                }
                else{
                    if( person.day[i] == 1 ) printf("|P ");
                    else if( person.day[i] == -1 ) printf("|0 ");
                    else printf("|A ");
                }
        }
            printf("  %d", person.attendance);
            printf("\n");

    }

}
    if(!found) printf("\n Id: %s, Not Found\n", id);

    fclose(fp);
    printf("\n\n");
}

void reset_All(){
    FILE *fp, *fp1;
    system("cls");
    asciiImg();
    fp = fopen("database.txt", "w");
    fp1 = fopen("temp.txt", "w");
    fclose(fp);
    fclose(fp1);
}

void resetDays(){
    db person;
    FILE *fp, *fp1;

    system("cls");
    asciiImg();

    fp = fopen("database.txt", "r");
    fp1 = fopen("temp.txt", "w");

    while(fread(&person, sizeof(db), 1, fp)){

        for(int i=0; i<CLASS_COUNT; i++) person.day[i] = -1;
        person.attendance = 0;
        fwrite(&person, sizeof(db), 1, fp1);
    }

    fclose(fp);
    fclose(fp1);

    fp1 = fopen("temp.txt", "r");
    fp = fopen("database.txt", "w");

    while(fread(&person, sizeof(db), 1, fp1)){
        fwrite(&person, sizeof(db), 1, fp);
    }

    fclose(fp);
    fclose(fp1);
}

void update(){
    db person;
    FILE *fp, *fp1;

    system("cls");
    asciiImg();

    fp = fopen("database.txt", "r");
    fp1 = fopen("temp.txt", "w");
    int found = 0, day;
    char id[50];
    printf("Enter Id to update: ");
    scanf("%s", id);
    printf("Enter day to update: ");
    scanf("%d", &day);

    while(fread(&person, sizeof(db), 1, fp)){
        if(!strcmp(person.id, id)){
            found = 1;
            printf("\nEnter 1 for present, and 0 for absent\n");
            printf("Input: ");
            scanf("%d", &person.day[day-1] );
        }
                int totalDays = 0;
                for(int i=0; i<CLASS_COUNT; i++) {
                    if(person.day[i] == 1) totalDays += person.day[i];
                }
                person.attendance = totalDays;
        fwrite(&person, sizeof(db), 1, fp1);
    }
    fclose(fp);
    fclose(fp1);


    if(found){
        fp1 = fopen("temp.txt", "r");
        fp = fopen("database.txt", "w");

        while(fread(&person, sizeof(db), 1, fp1)){
            fwrite(&person, sizeof(db), 1, fp);
        }

        fclose(fp);
        fclose(fp1);
    }else{
        printf("\nRecord not found!\n");
    }
}

void userPage(){
    int n;
    char any[50];
    point:
    system("cls");
    asciiImg();
    printf("\n\t1. Entry new people\n\n");
    printf("\t2. Take attendance\n\n");
    printf("\t3. Update attendance\n\n");
    printf("\t4. View people\n\n");
    printf("\t5. Search people\n\n");
    printf("\t6. Reset days\n\n");
    printf("\t7. Reset All\n\n");
    printf("\t0. Go back\n\n");
    printf("\nEnter ( 0 - 7 ) to operate. \n\nInput: ");
    scanf("%d", &n);

    switch(n){
        case 0:
            frontInterface();
            break;
        case 1:
            append();
            userPage();
            break;
        case 2:
            takeAttendance();
            userPage();
            break;
        case 3:
            update();
            printf("\nPress any number/character to continue.....");
            scanf(" %s", any);
            userPage();
            break;
        case 4:
            display();
            printf("\nPress any number/character to continue.....");
            scanf(" %s", any);
            userPage();
            break;
        case 5:
            search();
            printf("\nPress any number/character to continue.....");
            scanf(" %s", any);
            userPage();
            break;
        case 6:
            resetDays();
            printf("\nPress any number/character to continue.....");
            scanf(" %s", any);
            userPage();
            break;
        case 7:
            reset_All();
            printf("\nPress any number/character to continue.....");
            scanf(" %s", any);
            userPage();
            break;
        default:
            goto point;
            break;
        }
}

void frontInterface(){

    int n;
    point:

    system("cls");
    asciiImg();

    printf("\t1. Login\n\n");
    printf("\t2. About\n\n");
    printf("\t0. Exit\n\n");

    printf("\nEnter ( 0 - 2 ) to operate. \n\nInput: ");
    scanf("%d", &n);

        switch(n){
        case 0:
            //
            exit(1);
            break;
        case 1:
            login();
            break;
        case 2:
            about();
            break;
        default:
            goto point;
            break;
        }

}

int login(){

    system("cls");
    asciiImg();
    char userName[50];
    char userPass[50];

    printf("\n\t\t\t-- Login: \n");

    printf("\n\t\tUser: ");
    scanf(" %[^\n]s", userName);

    printf("\n\t\tPassword: ");
    scanf(" %[^\n]s", &userPass);

    if( loginAccess(userName, userPass) ){
        //loadingScreen();
        //printf("Access");
        userPage();
    }
    else{
        frontInterface();
    }

    printf("\n\n\n\n");
}

int loginAccess( char name[], char password[] ){
     if( !strcmp(name, USER_NAME ) && !strcmp(password, USER_PASS) ) return 1;
     else return 0;
}

void loadingScreen(){
    for(int i=0,j=0; i<1000000000; i++){
        j = i;
    }
}

void about(){
    point:
    system("cls");
    asciiImg();

    int n;
    printf("\n\t\t\t\t\t\t\t\t\tWelcome to about page: ");
    printf("\n\t\t\n\n");
    printf("%40s%60s%15s\n", "||","--------------------------------------------","||");
     printf("%40s%60s%15s\n", "||"," ","||");
    printf("%40s%59s%16s\n", "||","Project Name: Attendance Management System.","||");
    printf("%40s%60s%15s\n", "||"," ","||");
    printf("%40s%-60s%15s\n", "||","                Features: Login, Create, Update, view.","||");
    printf("%40s%-60s%15s\n", "||","                          ACII Img.","||");
     printf("%40s%60s%15s\n", "||"," ","||");
    printf("%40s%-60s%15s\n", "||","                Created: Rafiul Omar Rafi.","||");
     printf("%40s%60s%15s\n", "||"," ","||");
    printf("%40s%-60s%15s\n", "||","                Date: 24/04/2023.","||");
     printf("%40s%60s%15s\n", "||"," ","||");
    printf("%40s%60s%15s\n", "||","--------------------------------------------","||");
    printf("\n\n\tPress 0 to go back.");
    printf("\n\nInput: ");
    scanf("%d", &n);

    if(n == 0)frontInterface();
    else
        goto point;
}

void asciiImg(){
        printf("\t\t\t\t\t\t\t       d8888 888b     d888  .d8888b.  \n");
        printf("\t\t\t\t\t\t\t      d88888 8888b   d8888 d88P  Y88b\n");
        printf("\t\t\t\t\t\t\t     d88P888 88888b.d88888 Y88b.\n");
        printf("\t\t\t\t\t\t\t    d88P 888 888Y88888P888  \"Y888b.\n");
        printf("\t\t\t\t\t\t\t   d88P  888 888 Y888P 888     \"Y88b.\n");
        printf("\t\t\t\t\t\t\t  d88P   888 888  Y8P  888       \"888 \n");
        printf("\t\t\t\t\t\t\t d8888888888 888   \"   888 Y88b  d88P\n");
        printf("\t\t\t\t\t\t\td88P     888 888       888  \"Y8888P\"\n");
        printf("\n\n");
        printf("\t\t\t\t\t\t\t\t\t - Attendance Management System\n\n");
        printf("\t\t\t\t\t\t---------------------------------------------------------------");
        printf("\n\n");
}
