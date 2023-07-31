#include <stdio.h>

void add_Info(){
    char nombre[100];
    printf("Porfavor escriba el nombre del archivo a utilizar\n");
    fflush(stdin);
    fgets(nombre, 99, stdin);
    FILE *archivo = fopen(nombre, "a");
    if (archivo == NULL)
    {
        printf("Ocurrio un error, el archivo no existe\n");
    }else
    {
        char texto[200];
        printf("Ingrese la información\n");
        fflush(stdin);
        fgets(texto, 199, stdin);
        fprintf(archivo, " %s", texto);
        printf("La información fue guardada\n");
    }
    fclose(archivo);
}

int main(){
    char nombre[100];
    add_Info();
    return 0;
}