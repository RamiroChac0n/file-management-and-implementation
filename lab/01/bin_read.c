#include <stdio.h>

int main(){
    FILE *fd;
    char *filename = "number.dat";
    int num;
    fd = fopen(filename, "r");
    if (fd == NULL)
    {
        printf("No se pudo abrir el archivo %s\n", filename);
        return 1;
    }
    printf("Archivo %s abierto correctamente\n", filename);
    int tam_int = sizeof(int);
    int i;
    int r = fread(&i, tam_int, 1, fd);
    for (i = 0; i < 10; i++)
    {
        printf("Numero %d leido\n", i);
        r = fread(&i, tam_int, 1, fd);
    }
    fclose(fd);
    return 0;
}