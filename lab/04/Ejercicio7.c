#include <stdio.h>  // Importar funciones de entrada y salida
#include <stdlib.h> // Importar funciones de la biblioteca estandar
#include <string.h> // Importar funciones para manejo de cadenas

typedef struct {    // Definir una estructura
    int codArt;     // Codigo del articulo
    float precio;   // Precio del articulo
    char descrip[50];   // Descripcion del articulo
} Articulo;

void mostrarArticulo(void *dato);
void mostrarArchivo(const char *nombre);
int generarArchivo(const char *nombre);

void actualizarPrecios(const char *nombre, int cantRegistro){
    FILE *arch = fopen(nombre, "r+b");  // Abrir el archivo en modo lectura y escritura binaria
    if (arch == NULL){  // Verificar que el archivo se haya abierto correctamente
        printf("Error al abrir el archivo %s\n", nombre);
        return;
    }
    Articulo aux;   // Crear una variable auxiliar para leer los articulos del archivo
    int tam = sizeof(Articulo);    // Obtener el tamaño de la estructura Articulo
    for (int i = 0; i < cantRegistro; i++){
        fflush(arch);   // Limpiar el buffer del archivo
        fread(&aux, tam, 1, arch);  // Leer un articulo del archivo
        aux.precio *= 1.10; // Actualizar el precio del articulo
        fseek(arch, -tam, SEEK_CUR);    // Mover el puntero del archivo a la posicion del articulo
        fwrite(&aux, tam, 1, arch); // Escribir el articulo en el archivo
    }
    fclose(arch);   // Cerrar el archivo
}
int main(){
    int cantRegistro;   // Crear una variable para almacenar la cantidad de registros en el archivo
    cantRegistro = generarArchivo("Articulos2.dat");    // Generar el archivo
    mostrarArchivo("Articulos2.dat");   // Mostrar el archivo
    actualizarPrecios("Articulos2.dat", cantRegistro);  // Actualizar los precios del archivo
    printf("Articulos con precio actualizado\n");
    mostrarArchivo("Articulos2.dat");   // Mostrar el archivo
    return 0;   // Terminar el programa
}
int generarArchivo(const char *nombre){
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
    int ce = sizeof(articulos) / sizeof(articulos[0]);    // Obtener la cantidad de elementos del arreglo
    printf("ce: %d\n", ce);
    FILE *pf = fopen(nombre, "wb");    // Abrir el archivo en modo escritura binaria
    if(!pf){    // Verificar que el archivo se haya abierto correctamente
        printf("Fallo al escribir el archivo %s \n", nombre);
        return 0;
    }
    fwrite(articulos, sizeof(Articulo), ce, pf);    // Escribir el arreglo en el archivo
    fclose(pf); // Cerrar el archivo
    return ce;  // Retornar la cantidad de registros escritos en el archivo
}
void mostrarArchivo(const char *nombre){
    FILE *pf = fopen(nombre, "rb");    // Abrir el archivo en modo lectura binaria
    if(!pf){    // Verificar que el archivo se haya abierto correctamente
        printf("Fallo al escribir %s \n", nombre);
        return;
    } 
    Articulo aux;   // Crear una variable auxiliar para leer los articulos del archivo
    printf("Cod\t Precio\t Descripcion\n");
    while(fread(&aux, sizeof(Articulo), 1, pf)) // Leer un articulo del archivo
        mostrarArticulo(&aux);  // Mostrar el articulo
    fclose(pf); // Cerrar el archivo
}
void mostrarArticulo(void *dato){
    Articulo *art = (Articulo *)dato;   // Crear un puntero a la estructura Articulo
    printf("%d\t %.2f\t %-20s\n", art->codArt, art->precio, art->descrip);    // Mostrar el articulo
}