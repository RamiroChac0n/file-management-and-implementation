#include <stdio.h>

void copy_File(){
    char nombre[100], nombre2[100], letra = ' ';
    printf("Porfavor escriba el nombre del archivo a copiar\n");
    fflush(stdin);
    fgets(nombre, 99, stdin);
    printf("Porfavor escriba el nombre del archivo copia\n");
    fflush(stdin);
    fgets(nombre2, 99, stdin);
    FILE *archivo = fopen(nombre, "r");
    if (archivo == NULL)
    {
        printf("Ocurrio un error, el archivo no existe\n");
        return 1;
    }else
    {
        char texto[200];
        printf("Ingrese la información\n");
        fflush(stdin);
        fgets(texto, 199, stdin);
        fprintf(archivo, " %s", texto);
        printf("La información fue guardada\n");
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
    char nombre[100];
    copy_File();
    return 0;
}