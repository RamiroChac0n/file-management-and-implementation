#include <stdio.h>                                              // printf, fopen, fclose, fputc
#include <string.h>

int main(){
    FILE  *fd;                                                  // Puntero a FILE
    char *cadena = "HOLA DESDE C";
    char *filename = "archivo.txt";                             // Nombre del archivo

    fd = fopen(filename, "w+");                                 // Abrir archivo en modo escritura
    if (fd == NULL)
    {
        printf("No se pudo abrir el archivo %s\n", filename);   // Si no se pudo abrir el archivo
        return 1;
    }
    printf("Archivo %s abierto correctamente\n", filename);     // Si se pudo abrir el archivo

    int len = strlen(cadena);                                   // Tamaño de la cadena
    int i;
    for (i = 0; i < len; i++)                                   // Escribir la cadena
    {
        fputc(cadena[i], fd);                                   // Escribir un caracter
    }
    fputc('\n', fd);                                            // Escribir un salto de linea
    printf("Datos escritos correctamente\n");                   // Si se escribieron los datos
    fclose(fd);                                                 // Cerrar el archivo
    return 0;
}