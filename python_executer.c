#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(){
    char*argv[] = {"/usr/bin/python3","/home/liwex/lcd/lcd_write.py","ABCD",NULL};
    execv(argv[0],argv);
    return 0;    
}