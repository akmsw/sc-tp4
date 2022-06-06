#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(){
    char*argv[] = {"/home/liwex/lcd/lcd_write.py","ABCD",NULL};
    execv("/usr/bin/python3",argv);
    return 0;    
}