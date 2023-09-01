#include <stdio.h>  // Importar funciones de entrada y salida
#include <stdlib.h> // Importar funciones de la biblioteca estandar
#include <string.h> // Importar funciones para manejo de cadenas

typedef struct {    // Definir una estructura
    int codArt;     // Codigo del articulo
    float precio;   // Precio del articulo
    char descrip[50];   // Descripcion del articulo
} Articulo;

int main(){
    Articulo articulos[10] = {  // Crear un arreglo de articulos
        {1, 10.0, "Pelota de futbol"},
        {2, 20.0, "Raqueta de tenis"},
        {3, 30.0, "Pelota de baloncesto"},
        {4, 40.0, "Bicicleta"},
        {5, 50.0, "Guantes de boxeo"},
        {6, 60.0, "Gafas de natacion"},
        {7, 70.0, "Zapatillas de correr"},
        {8, 80.0, "Casco para ciclismo"},
        {9, 90.0, "Pelota de voleibol"},
        {10, 100.0, "Equipo de golf"}
    };

    FILE *pf = fopen("Articulos.dat", "wb");    // Abrir el archivo en modo escritura binaria
    if (pf == NULL)         // Verificar que el archivo se haya abierto correctamente
        printf("Error al abrir el archivo\n");   // Imprimir un mensaje de error

    fwrite(&articulos, sizeof(Articulo), 10, pf);// Escribir el arreglo de articulos en el archivo
    return 0;       // Terminar el programa
}