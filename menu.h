void frontInterface(){

    int n;
    point:

    system("cls");
    asciiImg();

    printf("\t1. Login\n\n");
    printf("\t0. Exit\n\n");

    printf("\nEnter ( 0 - 1 ) to operate. \n\nInput: ");
    scanf("%d", &n);

        switch(n){
        case 0:
            exit(1);
            break;
        case 1:
            login();
            break;
        default:
            goto point;
            break;
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
            printf("\nPress any number/character to continue....."); // taking  a input for pausing the screen
            scanf(" %s", any);
            userPage(); // called itself, recursion
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

