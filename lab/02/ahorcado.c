#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int elegir_ahorcado(){
    int eleccion = -1;
    int continuar = 1;
    while (continuar)
    {
        printf("------------------------------------\n");
        printf("Escoja un mapa\n");
        scanf("%d", &eleccion);
        if (eleccion > 0 && eleccion < 10)
        {
            return eleccion;
        }
        else
        {
            printf("Eleccion invalida\n");
        }   
    } 
}

char *cargar_ahorcado(int eleccion){
    char *nombre_archivo = malloc(sizeof(char) * 20);
    switch (eleccion)
    {
    case 1:strcpy(nombre_archivo, "ahorcado1.txt");break;
    }
    return nombre_archivo;
}

void mostrar_ahorcado(char *nombre_archivo){
    FILE *archivo = fopen(nombre_archivo, "r");
    char letra = ' ';
    if(archivo == NULL){
        printf("archivo no encontrado\n");
    }else{
        while ((letra = getc(archivo)) != EOF)
        {
            printf("%c", letra);
        }
    }
}

void cargar_sobre_arreglo(char *nombre_archivo, char *arreglo){
    FILE *archivo = fopen(nombre_archivo, "r");
    char letra = ' ';
    int contador = 0;
    if(archivo == NULL){
        printf("archivo no encontrado\n");
    }else{
        while ((letra = getc(archivo)) != EOF)
        {
            arreglo[contador] = letra;
            contador++;
        }
    }
}

char escoger_letra(char *nombre_archivo){
    char letra = ' ';
    int continuar = 1;
    while (continuar)
    {
        mostrar_ahorcado(nombre_archivo);
        printf("Escoja una letra\n");
        scanf("%c", &letra);
        if(letra >= 65 && letra <= 90){
            return letra;
        }else{
            printf("Eleccion invalida\n");
        }
    }
}

char *cargar_solucion(int valor){
    char *nombre_archivo = malloc(sizeof(char) * 23);
    switch (valor)
    {
    case 1:strcpy(nombre_archivo, "ahorcado1_solucion.txt");break;
    }
    return nombre_archivo;
}

void actualizar_ahorcado(char *nombre_archivo, char letra){
    FILE *archivo = fopen(nombre_archivo, "r");
    char letra_archivo = ' ';
    char *nuevo_archivo = malloc(sizeof(char) * 100);
    int contador = 0;
    if(archivo == NULL){
        printf("archivo no encontrado\n");
    }else{
        while ((letra_archivo = getc(archivo)) != EOF)
        {
            if(letra_archivo == '_'){
                nuevo_archivo[contador] = letra;
            }else{
                nuevo_archivo[contador] = letra_archivo;
            }
            contador++;
        }
    }
    fclose(archivo);
    archivo = fopen(nombre_archivo, "w");
    fprintf(archivo, "%s", nuevo_archivo);
    fclose(archivo);
}

bool validar_jugada(char *nombre_archivo, char letra){
    FILE *archivo = fopen(nombre_archivo, "r");
    char letra_archivo = ' ';
    if(archivo == NULL){
        printf("archivo no encontrado\n");
    }else{
        while ((letra_archivo = getc(archivo)) != EOF)
        {
            if(letra_archivo == letra){
                return true;
            }
        }
    }
    return false;
}

void elegir_posicion(char *nombre_archivo, char letra){
    int posicion = 0;
    int contador = 0;
    FILE *archivo = fopen(nombre_archivo, "r");
    char letra_archivo = ' ';
    if(archivo == NULL){
        printf("archivo no encontrado\n");
    }else{
        while ((letra_archivo = getc(archivo)) != EOF)
        {
            if(letra_archivo == letra){
                printf("Posicion %d\n", contador);
            }
            contador++;
        }
    }
}

bool evaluar_victoria(char *nombre_archivo){
    FILE *archivo = fopen(nombre_archivo, "r");
    char letra_archivo = ' ';
    if(archivo == NULL){
        printf("archivo no encontrado\n");
    }else{
        while ((letra_archivo = getc(archivo)) != EOF)
        {
            if(letra_archivo == '_'){
                return false;
            }
        }
    }
    return true;
}

int main(){
    int ahorcado[10], ahorcado_origen[10], solucion[10], posicion = -1, continuar = 1;
    int eleccion = elegir_ahorcado();
    cargar_sobre_arreglo(cargar_ahorcado(eleccion), ahorcado);
    cargar_sobre_arreglo(cargar_ahorcado(eleccion), ahorcado_origen);
    cargar_sobre_arreglo("ahorcado1_solucion.txt", solucion);
    while (continuar)
    {
        char letra = escoger_letra(cargar_ahorcado(eleccion));
        if(validar_jugada(cargar_ahorcado(eleccion), letra)){
            printf("Letra encontrada\n");
            actualizar_ahorcado(cargar_ahorcado(eleccion), letra);
            if(evaluar_victoria(cargar_ahorcado(eleccion))){
                printf("Ganaste\n");
                continuar = 0;
            }
        }else{
            printf("Letra no encontrada\n");
        }
    }
}