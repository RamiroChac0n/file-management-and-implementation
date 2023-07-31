#include <stdio.h>
#include <string.h>

int main(){
    FILE  *fd;
    char *cadena = "HOLA DESDE C";
    char *filename = "archivo.txt";

    fd = fopen(filename, "w+");
    if (fd == NULL)
    {
        printf("No se pudo abrir el archivo %s\n", filename);
        return 1;
    }
    printf("Archivo %s abierto correctamente\n", filename);

    int len = strlen(cadena);
    int i;
    for (i = 0; i < len; i++)
    {
        fputc(cadena[i], fd);
    }
    fputc('\n', fd);
    printf("Datos escritos correctamente\n");
    fclose(fd);
    return 0;
}