#include <stdio.h>                                              // printf, fopen, fclose, fwrite

int main(){
    FILE *fd;                                                   // Puntero a FILE
    char *filename = "number.dat";                              // Nombre del archivo
    fd = fopen(filename, "w+");                                 // Abrir archivo en modo escritura
    if (fd == NULL)                                             
    {
        printf("No se pudo abrir el archivo %s\n", filename);   // Si no se pudo abrir el archivo
        return 1;
    }
    printf("Archivo %s abierto correctamente\n", filename);     // Si se pudo abrir el archivo
    int tam_int = sizeof(int);                                  // Tamaño de un entero
    int i;
    for (i = 0; i < 10; i++)                                    // Escribir 10 enteros
    {
        fwrite(&i, tam_int, 1, fd);                             // Escribir un entero
    }
    printf("Datos escritos correctamente\n");                   // Si se escribieron los datos
    fclose(fd);                                                 // Cerrar el archivo
    return 0;
}