#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    FILE * file = fopen("/dev/display_kernel","w");
    if(!file){
        printf("Exploto");
        exit(EXIT_FAILURE); 
    }
    fwrite("ABCD",sizeof(char),4,file);
    fclose(file);
    return 0;
}