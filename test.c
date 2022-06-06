#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    FILE * file = fopen("/dev/display_kernel","w");
    fwrite("asd",1,3,file);
    fclose(file);
    return 0;
}