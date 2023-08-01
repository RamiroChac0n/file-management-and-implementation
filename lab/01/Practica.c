#include <stdio.h>
#include <string.h>

void create_file(char name[50]){
    char filename[54];
    strcpy(filename, name);
    strcat(filename, ".txt");
    FILE *file = fopen(filename, "w");
    if(file == NULL){
        printf("Error al crear el archivo\n");
    }else{
        printf("Archivo creado con exito\n");
    }
    fclose(file);
}

int main(){
    int option;
    do
    {
        printf("\n______________________ Menu ______________________\n");
        printf("1. Crear archivo\n");
        printf("0. Salir\n");
        printf("_________________________________________________\n");
        printf("Opcion:\n");
        scanf(" %d", &option);
        fflush(stdin);
        switch (option)
        {
        case 1:
            char name[50];
            printf("Ingrese el nombre del archivo: ");
            scanf(" %[^\n]", name);
            create_file(name);
            break;
        case 0:
            printf("Saliendo...\n");
            option = 0;
            break;
        }
    } while (option != 0);
    
    return 0;
}