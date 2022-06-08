#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    char *args[] = {"/usr/bin/python3", "/usr/bin/lcd_write.py", argv[1], NULL};

    execv(args[0], args);

    return 0;
}