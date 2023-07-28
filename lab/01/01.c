#include <stdio.h>
crear_Archivo(char nombre[100]){
    FILE *archivo= fopen("my_first_file.txt", "w");
    if (archivo == NULL)
    {
        printf("Ocurrio un error, no fue creado.\n");
    }else
        printf("El archivo fue creado.\n");
    fclose(archivo);
}

int main(){
    char nombre[100];
    printf("Ingrese el nombre del archivo que desee crear\n");
    fgets(nombre, 99, stdin);
    crear_Archivo(nombre);
    return 0;
}