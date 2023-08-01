#include <stdio.h>                                              // printf, fopen, fclose, fgetc

int main(){
    FILE *fd;                                                   // Puntero a FILE
    char *filename = "archivo.txt";                             // Nombre del archivo
    char c;

    fd = fopen(filename, "r");                                  // Abrir archivo en modo lectura
    if (fd == NULL)
    {
        printf("No se pudo abrir el archivo %s\n", filename);   // Si no se pudo abrir el archivo
        return 1;
    }

    c = fgetc(fd);                                              // Leer un caracter
    while (c != EOF)                                            // Mientras no se llegue al final del archivo
    {
        putchar(c);                                             // Imprimir el caracter leido
        c = fgetc(fd);                                          // Leer un caracter
    }

    fclose(fd);                                                 // Cerrar el archivo
    return 0;
}