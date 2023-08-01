#include <stdio.h>                                              // printf, fopen, fclose, fread

int main(){
    FILE *fd;                                                   // Puntero a FILE
    char *filename = "number.dat";                              // Nombre del archivo
    fd = fopen(filename, "r");                                  // Abrir archivo en modo lectura
    if (fd == NULL)
    {
        printf("No se pudo abrir el archivo %s\n", filename);   // Si no se pudo abrir el archivo
        return 1;                                               // Terminar el programa
    }
    printf("Archivo %s abierto correctamente\n", filename);     // Si se pudo abrir el archivo
    int tam_int = sizeof(int);                                  // Tamaño de un entero
    int i;
    int r = fread(&i, tam_int, 1, fd);                          // Leer un entero
    while (r != 0)                                              // Mientras no se llegue al final del archivo
    {
        printf("Numero %d leido\n", i);                         // Imprimir el entero leido
        r = fread(&i, tam_int, 1, fd);                          // Leer un entero
    }
    fclose(fd);                                                 // Cerrar el archivo
    return 0;
}