#include <stdio.h>
#include <string.h>

int main(){
    FILE  *fd;
    char *cadena = "HOLA DESDE C";
    char *filename = "archivo.txt";

    fd = fopen(filename, 'w+');
    if (fd == NULL)
    {
        printf("No se pudo abrir el archivo %s\n", filename);
        return 1;
    }
    
}