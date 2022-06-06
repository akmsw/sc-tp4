#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

int main(){
    int flag;
    int file = open("/dev/display_kernel",O_CREAT|O_RDWR);
    write(file,"ABCD",4);
    close(file);
    return 0;
}