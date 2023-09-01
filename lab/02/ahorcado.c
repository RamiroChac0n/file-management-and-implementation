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
        printf("Escoja dificultad\n");
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

void mostrar_ahorcado(char ahorcado[10]){
    int posicion = 0;
    printf("\n");
    while (posicion < 6)
    {
        printf("%c ", ahorcado[posicion]);
        posicion++;
    }
    printf("\n");
}

void cargar_sobre_arreglo(char *nombre_archivo, char ahorcado[10]){
    FILE *archivo = fopen(nombre_archivo, "r");
    char letra = ' ';
    int contador = 0;
    if(archivo == NULL){
        printf("archivo no encontrado\n");
    }else{
        while ((letra = getc(archivo)) != EOF)
        {
            if(letra != '\n'){
                ahorcado[contador] = letra;
                contador++;
            }
        }
    }
}

char escoger_letra(char ahorcado[10]){
    char letra = ' ';
    int continuar = 1;
    while (continuar)
    {
        mostrar_ahorcado(ahorcado);
        printf("Escoja una letra: ");
        scanf(" %c", &letra);
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

void actualizar_ahorcado(char ahorcado[10], int posicion, char letra){
    ahorcado[posicion] = letra;
}

bool validar_jugada(int posicion, char ahorcado_origen[10]){
    if(ahorcado_origen[posicion] == '_'){
        return true;
    }else{
        return false;
    }
}

void elegir_posicion(char letra, char ahorcado[10], int *posicionElegida, char ahorcado_origen[10]){
    int posicion = -1;
    bool validar = false;
    while(posicion < 0 || posicion > 9 || validar == false){
        printf("Escoja una posicion (0 a 9): ");
        scanf("%d", &posicion);
        if(posicion < 0 || posicion > 9){
            printf("Posicion invalida\n");
        }else{
            validar = validar_jugada(posicion, ahorcado_origen);
            if(validar){
                ahorcado[posicion] = letra;
            }else{
                printf("Letra ya jugada\n");
            }
        }
    }
    *posicionElegida = posicion;
}

bool evaluar_victoria(char ahorcado[10], char solucion[10]){
    int posicion = 0;
    while (posicion < 6)
    {
        if(ahorcado[posicion] != solucion[posicion]){
            return false;
        }
        posicion++;
    }
    return true;
}

int puntuacion(int vidas){
    return vidas * 100;
}

void savePlayer(char *nombre, int puntuacion){
    FILE *archivo = fopen("jugadores.txt", "a");
    if(archivo == NULL){
        printf("archivo no encontrado\n");
    }else{
        fprintf(archivo, "%s;%d\n", nombre, puntuacion);
    }
    fclose(archivo);
}

int main(){
    printf("Bienvenido al juego del ahorcado\n");
    printf("Instrucciones:\n");
    printf("1. Escoja un nivel\n");
    printf("2. Solo se pueden escoger letras\n");
    printf("3. Las letras deben estar en mayuscula\n");
    printf("4. Escoja posiciones del 1 en adelante\n");
    char ahorcado[10], ahorcado_origen[10], solucion[10];
    char jugar = ' ';
    do
    {
        int posicion = -1;
        int eleccion = elegir_ahorcado();
        system("clear");

        int vidas = 10;
        printf("Vidas: %d\n", vidas);

        cargar_sobre_arreglo(cargar_ahorcado(eleccion), ahorcado);
        memcpy(ahorcado_origen, ahorcado, sizeof(ahorcado));
        cargar_sobre_arreglo("ahorcado1_solucion.txt", solucion);

        while (vidas > 0){
            char letra = escoger_letra(ahorcado);
            elegir_posicion(letra, ahorcado, &posicion, ahorcado_origen);
            actualizar_ahorcado(ahorcado, posicion, letra);
            mostrar_ahorcado(ahorcado);
            bool victoria = evaluar_victoria(ahorcado, solucion);
            if(victoria == true){
                system("clear");
                printf("Felicidades, ha ganado\n");
                printf("Puntuacion: %d\n", puntuacion(vidas));
                char *nombre = malloc(sizeof(char) * 20);
                printf("Ingrese su nombre: ");
                scanf("%s", nombre);
                savePlayer(nombre, puntuacion(vidas));
                break;
            }else{
                system("clear");
                vidas--;
                printf("Vidas: %d\n", vidas);
            }            
        }

        printf("Seguir jugando? (s/n)\n");
        scanf(" %c", &jugar);
    } while (jugar == 's' || jugar == 'S');
    
    return 0;
}