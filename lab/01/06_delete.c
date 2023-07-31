#include <stdio.h>

int delete_file(){
    char nombre[100], nombre2[100], letra = ' ';
    printf("Porfavor escriba el nombre del archivo a borrar\n");
    fflush(stdin);
    fgets(nombre, 99, stdin);

    FILE *archivo = fopen(nombre, "r");
    if (archivo == NULL)
    {
        printf("Error, no se encuentra el archivo \n");
        return 1;
    } else {
        fclose(archivo);
        if (remove(nombre) == -1)
        {
            printf("No se pudo borrar el archivo correctamente\n");
        } else {
            printf ("El archivo fue borrado \n");
        }
    }
}
int main(){
    delete_file();
    return 0;
}