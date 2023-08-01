#include <stdio.h>

void reglas(){
    printf("------------- SUDOKU --------------\n");
    printf("Reglas del juego:\n");
    printf("1. Para jugar, escoja el numero de sudoku de 1 a 9\n");
    printf("2. Para ganar debe cumplir las reglas que se especefican a continuacion\n");
    printf("3. Debe escoger numeros de 1 a 9\n");
    printf("4. No puede repetir numeros en la misma fila, columna ni cuadrilla\n");
    printf("5. No debe escoger posiciones fuera del mapa\n");
    printf("6. No debe sobreescribir numeros que son parte del mapa original\n");
    printf("7. Puede cambiar de valor los numeros que no sean parte del mapa original");
    printf("8. Los valores marcados en ceros son posiciones que puede editar, son parte del mapa vació\n");
    printf("9. En caso de que haya ganado se le notificará, sino no se le notificará nada\n");
    printf("10 En caso de necesitarlo se le facilitará la solución del mapa, puede verlo presionando la tecla 'v'\n");
    printf("11. Diviertasa\n");
    printf("------------------------------------\n");
}

int elegir_sudoku(){
    int eleccion = -1;
    int continuar = 1;
    while (continuar = 1)
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

//Función para abrir el archivo que contiene el mapa.
char *cargar_eleccion(int valor){
    char *nombre_archivo = malloc(sizeof(char) * 12);
    switch (valor)
    {
    case 1:strcpy(nombre_archivo, "sudoku1_tablilla.txt");break;
    case 2:strcpy(nombre_archivo, "sudoku2_tablilla.txt");break;
    case 3:strcpy(nombre_archivo, "sudoku3_tablilla.txt");break;
    case 4:strcpy(nombre_archivo, "sudoku4_tablilla.txt");break;
    case 5:strcpy(nombre_archivo, "sudoku5_tablilla.txt");break;
    case 6:strcpy(nombre_archivo, "sudoku6_tablilla.txt");break;
    case 7:strcpy(nombre_archivo, "sudoku7_tablilla.txt");break;
    case 8:strcpy(nombre_archivo, "sudoku8_tablilla.txt");break;
    case 9:strcpy(nombre_archivo, "sudoku9_tablilla.txt");break;
    }
    return nombre_archivo;
}

//Método para cargar archivo sobre una martriz
void cargar_sobre_matriz(char *nombre_archivo, int mapa[9][9]){
    FILE *archivo = fopen(nombre_archivo, "r");
    char letra = ' ';
    int contador_fila = 0;
    int contador_columna = 0;
    if(archivo == NULL){
        printf("archivo no encontrado\n");
    }else{
        while (letra != EOF)
        {
            letra = getc(archivo);
            if(letra != ' ' && letra != -1 && letra != 9 && letra != 10){
                mapa[contador_fila][contador_columna] = letra - 48;
                contador_columna++;
                if(contador_columna % 9 == 0){
                    contador_columna = 0;
                    contador_fila++;
                }
            }
        }
    }
    mostrar_mapa(mapa);
}

int main(){
    reglas();
    int eleccion = elegir_sudoku();
    return 0;   
}