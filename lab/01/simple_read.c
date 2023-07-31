#include <stdio.h>

int main(){
    FILE *fd;
    char *filename = "archivo.txt";
    char c;

    fd = fopen(filename, "r");
    if (fd == NULL)
    {
        printf("No se pudo abrir el archivo %s\n", filename);
        return 1;
    }

    c = fgetc(fd);
    while (c != EOF)
    {
        putchar(c);
        c = fgetc(fd);
    }

    fclose(fd);
    return 0;
}