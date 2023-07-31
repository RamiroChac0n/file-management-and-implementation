#include <stdio.h>

int read_File(){
    char nombre[100], nombre2[100], letra = ' ';
    printf("Porfavor escriba el nombre del archivo a leer\n");
    fflush(stdin);
    fgets(nombre, 99, stdin);
    FILE *archivo = fopen(nombre, "r");
    if (archivo == NULL)
    {
        printf("Ocurrio un error, el archivo no existe\n");
        return 1;
    }else
    {
        while (letra != EOF)
        {
            letra = fgetc(archivo);
            if (letra != -1)
            {
                printf("%c", letra);
            }
            
        }
        printf("Archivo leido con exito.");
    }
    
    fclose(archivo);    
}

int main(){
    read_File();
    return 0;
}