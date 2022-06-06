#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

int main(){
    int file = open("/dev/display_kernel","w");
    write(file,"ABCD",4);
    close(file);
    return 0;
}