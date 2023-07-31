#include <stdio.h>
#include <string.h>

int create_file(char *name){
    FILE *file;
    file = fopen(name, "w");
    if(file == NULL){
        return 1;
    }
    fclose(file);
    return 0;
}

int main(){
    int option;
    do
    {
        printf("\n______________________ Menu ______________________\n");
        printf("1. Crear archivo\n");
        printf("0. Salir\n");
        printf("_________________________________________________\n");
        printf("Opcion: ");
        scanf("%d", &option);
        fflush(stdin);
        switch (option)
        {
        case 1:
            char name[50];
            printf("Ingrese el nombre del archivo: \n");
            scanf("%s", name);
            fflush(stdin);
            if(create_file(name) == 1){
                printf("Error al crear el archivo\n");
            }else{
                printf("Archivo creado con exito\n");
            }
            break;
        case 0:
            printf("Saliendo...\n");
            option = 0;
            break;
        }
    } while (option != 0);
    
    return 0;
}