#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>


int main(){
    FILE * file = fopen("/dev/display_kernel","w");
    char buffer[512];
    bzero(buffer,512);
    if(!file){
        printf("Error al abrir CDD");
        exit(EXIT_FAILURE); 
    }
    
    write(1,"Ingrese string a enviar al display: ",37);
    if(read(0,buffer,512)>32) {
        printf("El string tiene mas de 32 caracteres\n");
    }else{
        buffer[strlen(buffer)-1] = '\0';
        fwrite(buffer,sizeof(char),strlen(buffer),file);
    }
    fclose(file);
    return 0;

}