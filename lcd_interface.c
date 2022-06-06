#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

FILE * file;

void close_signal(int s){
    fclose(file);
    exit(EXIT_SUCCESS);
}

int main(){
    file = fopen("/dev/display_kernel","w");
    char buffer[512];
    if(!file){
        printf("Error al abrir CDD");
        exit(EXIT_FAILURE); 
    }
    signal(SIGINT,close_signal);
    while(-1){
        printf("Ingrese string a enviar al display: ");
        if(read(STDIN_FILENO,buffer,512)>32){
            printf("El string tiene mas de 32 caracteres\n");
            continue;
        } 
        fwrite(buffer,sizeof(char),strlen(buffer),file);
    }
    return 0;
}