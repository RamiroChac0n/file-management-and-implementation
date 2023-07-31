#include <stdio.h>

int main(){
    FILE *fd;
    char *filename = "number.dat";
    fd = fopen(filename, "w+");
    if (fd == NULL)
    {
        printf("No se pudo abrir el archivo %s\n", filename);
        return 1;
    }
    printf("Archivo %s abierto correctamente\n", filename);
    int tam_int = sizeof(int);
    int i;
    for (i = 0; i < 10; i++)
    {
        fwrite(&i, tam_int, 1, fd);
    }
    printf("Datos escritos correctamente\n");
    fclose(fd);
    return 0;
}