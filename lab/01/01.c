#include <stdio.h>
void crear_Archivo(){
    FILE *archivo= fopen("my_first_file.txt", "w");
    if (archivo == NULL)
    {
        printf("Ocurrio un error, no fue creado.\n");
    }else
        printf("El archivo fue creado.\n");
    fclose(archivo);
}

int main(){
    crear_Archivo();
    return 0;
}