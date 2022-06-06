#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

int main(){
    int file = open("/dev/display_kernel",O_RDWR);
    write(file,"ABCD",4);
    close(file);
    return 0;
}