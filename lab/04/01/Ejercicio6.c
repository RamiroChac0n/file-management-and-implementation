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

    FILE *pf = fopen("Articulos.dat", "rb");    // Abrir el archivo en modo escritura binaria
    if (pf == NULL)         // Verificar que el archivo se haya abierto correctamente
        printf("Error al abrir el archivo\n");   // Imprimir un mensaje de error

    fseek(pf, 01, SEEK_END);  // Mover el puntero del archivo a la posicion del segundo articulo
    int cant_registros = ftell(pf) / sizeof(Articulo);  // Obtener la cantidad de registros en el archivo
    rewind(pf);     // Mover el puntero del archivo al inicio
    void* vec = malloc(sizeof(Articulo) * cant_registros); // Crear un vector auxiliar para almacenar los articulos
    fread(vec, sizeof(Articulo), cant_registros, pf);   // Leer los articulos del archivo

    for(int i = 0; i < cant_registros; i++, vec += sizeof(Articulo)){ // Recorrer el vector de articulos
        mostrarRegistro(vec);   // Mostrar el articulo
    }

    return 0;       // Terminar el programa
}
void mostrarRegistro(void* dato){
    Articulo *art = (Articulo *)dato;
    printf("Codigo: %d\n", art->codArt);      // Imprimir el codigo del articulo
    printf("Precio: %.2f\n", art->precio);    // Imprimir el precio del articulo
    printf("Descripcion: %s\n", art->descrip);    // Imprimir la descripcion del articulo
}