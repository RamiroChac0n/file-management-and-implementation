#include <stdio.h>

int copy_File(){
    char nombre[100], nombre2[100], letra = ' ';
    printf("Porfavor escriba el nombre del archivo a copiar\n");
    fflush(stdin);
    fgets(nombre, 99, stdin);
    printf("Porfavor escriba el nombre del archivo nuevo\n");
    fflush(stdin);
    fgets(nombre2, 99, stdin);
    FILE *archivo = fopen(nombre, "r");
    if (archivo == NULL)
    {
        printf("Ocurrio un error, el archivo no existe\n");
        return 1;
    }

    FILE *archivo2 = fopen(nombre, "a");
    if (archivo2 == NULL)
    {
        printf("Archivo no fue creado con exito\n");
    }else
    {
        while (letra != EOF)
        {
            letra = fgetc(archivo);
            if (letra != -1)
            {
                putc(letra, archivo2);
            }
            
        }
        printf("Archivo copiado con exito.");
    }
    
    fclose(archivo);
    fclose(archivo2);
    
}

int main(){
    copy_File();
    return 0;
}