#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

int main()
{
    FILE *file = fopen("/dev/display_driver", "w");

    char buffer[32];

    bzero(buffer, 32);

    if (!file)
    {
        printf("Error al abrir CDD");

        exit(EXIT_FAILURE);
    }

    while (-1)
    {
        write(STDOUT_FILENO, "Ingrese string a enviar al display: ", 37);

        read(0, buffer, 32);

        if (strcmp(buffer, "salir") == 0)
            break;

        buffer[strlen(buffer)] = '\0';

        fwrite(buffer, sizeof(char), strlen(buffer), file);
        fflush(file);

        bzero(buffer, 32);
    }

    fclose(file);

    return 0;
}