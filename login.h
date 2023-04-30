#define USER_NAME "admin"
#define USER_PASS "admin123"

int loginAccess( char name[], char password[] ){
     if( !strcmp(name, USER_NAME ) && !strcmp(password, USER_PASS) ) return 1; // if all matched
     else if( (!strcmp(name, USER_NAME ) == 1) && (!strcmp(password, USER_PASS) == 0) ) return -1; // if only username matched
     else if( (!strcmp(name, USER_NAME ) == 0) && (!strcmp(password, USER_PASS) == 1) ) return -2; // if only password matched
     else return 0; // if both password and username is not matched
}

int login(){

    char any[20];

    system("cls");
    asciiImg();
    char userName[50];
    char userPass[50];

    printf("\n\t\t\t-- Login: \n");

    printf("\n\t\tUser: ");
    scanf(" %[^\n]s", userName);

    printf("\n\t\tPassword: ");
    scanf(" %[^\n]s", &userPass);

    if( loginAccess(userName, userPass) == 1 ){
        userPage();
    }
    else if( loginAccess(userName, userPass) == -1 ){
        printf("\nPassWord invalid!\n");
        printf("\nPress any number/character to continue.....");
        scanf(" %s", any);
        frontInterface();
    }
    else if( loginAccess(userName, userPass) == -2 ){
        printf("\nUserName invalid!\n");
        printf("\nPress any number/character to continue.....");
        scanf(" %s", any);
        frontInterface();
    }
    else{
        printf("\nUserName & Password both invalid!\n");
        printf("\nPress any number/character to continue.....");
        scanf(" %s", any);
        frontInterface();
    }

    printf("\n\n\n\n");
}
