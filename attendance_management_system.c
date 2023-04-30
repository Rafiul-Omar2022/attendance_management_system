#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dos.h>

#include "splash.h"      //  ascii
#include "login.h"      //  login
#include "menu.h"      //  menu
#include "database.h" //  all database operation & files


int main(){

    splashimg();
    asciiImg();
    frontInterface();

    return 0;
}
