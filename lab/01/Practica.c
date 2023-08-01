#include <stdio.h>
#include <string.h>

void create_file(char name[50]){
    char filename[54];
    strcpy(filename, name);
    strcat(filename, ".txt");
    FILE *file = fopen(filename, "w+");
    if(file == NULL){
        printf("Error al crear el archivo\n");
    }else{
        printf("Archivo creado con exito\n");
    }
    fclose(file);
}

void read_file(char name[50]){
    char filename[54];
    strcpy(filename, name);
    strcat(filename, ".txt");
    FILE *file = fopen(filename, "r");
    if(file == NULL){
        printf("Error al abrir el archivo\n");
    }else{
        printf("Archivo abierto con exito\n");
        char text[200];
        while(fgets(text, 200, file) != NULL){
            printf("%s", text);
        }
    }
    fclose(file);
}

void update_file(char name[50]){
    char filename[54];
    strcpy(filename, name);
    strcat(filename, ".txt");
    FILE *file = fopen(filename, "a");
    if(file == NULL){
        printf("Error al abrir el archivo\n");
    }else{
        printf("Archivo abierto con exito\n");
        char text[200];
        printf("Ingrese el texto a agregar: ");
        scanf(" %[^\n]", text);
        fprintf(file, "%s\n", text);
        printf("Texto agregado con exito\n");
    }
    fclose(file);
}

int delete_file(char name[50]){
    char filename[54];
    strcpy(filename, name);
    strcat(filename, ".txt");
    if(remove(filename) == 0){
        printf("Archivo eliminado con exito\n");
        return 1;
    }else{
        printf("Error al eliminar el archivo\n");
        return 0;
    }
}

// Binaries
void create_file_bin(char name[50]){
    char filename[54];
    strcpy(filename, name);
    strcat(filename, ".bin");
    FILE *file = fopen(filename, "wb");
    if(file == NULL){
        printf("Error al crear el archivo\n");
    }else{
        printf("Archivo creado con exito\n");
    }
    fclose(file);
}

void read_file_bin(char name[50]){
    char filename[54];
    strcpy(filename, name);
    strcat(filename, ".bin");
    FILE *file = fopen(filename, "rb");
    if(file == NULL){
        printf("Error al abrir el archivo\n");
    }else{
        printf("Archivo abierto con exito\n");
        char text[200];
        while(fgets(text, 200, file) != NULL){
            printf("%s", text);
        }
    }
    fclose(file);
}

void update_file_bin(char name[50]){
    char filename[54];
    strcpy(filename, name);
    strcat(filename, ".bin");
    FILE *file = fopen(filename, "ab");
    if(file == NULL){
        printf("Error al abrir el archivo\n");
    }else{
        printf("Archivo abierto con exito\n");
        char text[200];
        printf("Ingrese el texto a agregar: ");
        scanf(" %[^\n]", text);
        fprintf(file, "%s\n", text);
        printf("Texto agregado con exito\n");
    }
}

int main(){
    int option;
    do
    {
        printf("\n______________________ Menu ______________________\n");
        printf("1. Crear archivo\n");
        printf("2. Leer archivo\n");
        printf("3. Agregar texto a un archivo\n");
        printf("4. Eliminar archivo\n");
        printf("5. Crear archivo binario\n");
        printf("6. Leer archivo binario\n");
        printf("7. Agregar texto a un archivo binario\n");
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
        case 2:
            char name1[50];
            printf("Ingrese el nombre del archivo: ");
            scanf(" %[^\n]", name1);
            read_file(name1);
            break;
        case 3:
            char name2[50];
            printf("Ingrese el nombre del archivo: ");
            scanf(" %[^\n]", name2);
            update_file(name2);
            break;
        case 4:
            char name3[50];
            printf("Ingrese el nombre del archivo: ");
            scanf(" %[^\n]", name3);
            delete_file(name3);
            break;
        case 5:
            char name4[50];
            printf("Ingrese el nombre del archivo: ");
            scanf(" %[^\n]", name4);
            create_file_bin(name4);
            break;
        case 6:
            char name5[50];
            printf("Ingrese el nombre del archivo: ");
            scanf(" %[^\n]", name5);
            read_file_bin(name5);
            break;
        case 7:
            char name6[50];
            printf("Ingrese el nombre del archivo: ");
            scanf(" %[^\n]", name6);
            update_file_bin(name6);
            break;
        case 0:
            printf("Saliendo...\n");
            option = 0;
            break;
        }
    } while (option != 0);
    
    return 0;
}