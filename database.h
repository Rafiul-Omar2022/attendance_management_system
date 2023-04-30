#define CLASS_COUNT 30

typedef struct database{
    char name[100];
    char id[100];
    int day[CLASS_COUNT];
    int attendance;
}db;

void append(){
    FILE *fp; // file pointer
    int size = 0;

    system("cls");
    asciiImg();

    printf("\n\nHow many people do you want to add: ");
    scanf("%d", &size);
    db person[size]; // array of struct

    fp = fopen("database.txt", "a");
    for(int i=0; i<size; i++){
        for(int j=0; j<CLASS_COUNT; j++) person[i].day[j] = -1; // storing -1 for not assigning.
        printf("\nEnter Id: ");
        scanf(" %s", person[i].id);
        printf("Enter person name: ");
        scanf(" %[^\n]s", person[i].name);
        person[i].attendance = 0;
        fwrite(&person[i], sizeof(db), 1, fp); // for every element, the data is stored in database file
    }
    fclose(fp);
}

void display(){
    db person;
    FILE *fp = fopen("database.txt", "r");

    int totalPerson  = 0; // counting the iteration for storing, totalperson

    system("cls");
    asciiImg();

    printf("%9s|\t%12s|\t|1 |2 |3 |4 |5 |6 |7 |8 |9 |10 |11 |12 |13 |14 |15 |16 |17 |18 |19 |20 |21 |22 |23 |24 |25 |26 |27 |28 |29 |30  %s \n","ID","Name","Days");

    while(fread(&person, sizeof(db), 1, fp)){
            printf("%9s|\t%12s|\t", person.id, person.name);
            for(int i=0; i<CLASS_COUNT; i++) { // 30 times loops for 30 days
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
    fp1 = fopen("temp.txt", "w"); // for storing tmp data

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
    } // reading temp, and writing to database file.

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
            for(int i=0; i<CLASS_COUNT; i++) {
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
    scanf(" %s", id);
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

void reset_All(){
    FILE *fp, *fp1;
    system("cls");
    asciiImg();
    fp = fopen("database.txt", "w");
    fp1 = fopen("temp.txt", "w");
    fclose(fp);
    fclose(fp1);
}
