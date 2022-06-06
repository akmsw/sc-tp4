#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>


int main(){
    FILE * file = fopen("/dev/display_kernel","w");
    char buffer[32];
    if(!file){
        printf("Error al abrir CDD");
        exit(EXIT_FAILURE); 
    }
    while(-1){
        write(1,"Ingrese string a enviar al display: ",37);
        read(0,buffer,31);
        char * clear = "                              \0";
        fwrite(clear,sizeof(char),32,file);
        fflush(file);
        buffer[31] = '\0';
        if(strcmp(buffer,"salir")==0){
            fclose(file);
            return 0;
        }
        fwrite(buffer,sizeof(char),strlen(buffer),file);
        fflush(file);
    }    
}
