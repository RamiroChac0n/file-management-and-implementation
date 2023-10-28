#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "product.h"
#include "id_generator.h"
#include "hash_table.h"

int main() {
    Product *product = malloc(sizeof(Product)); // Reservar memoria para el producto
    strcpy(product->id, id_generator()); // Copiar el id generado a la estructura
    strcpy(product->name, "Banana"); // Asignar el nomre del product
    product->price = 10.0; // Asignar el precio del producto
    printf("ID: %s\n", product->id); // Imprimir el id del producto
    printf("NAME: %s\n", product->name); // Imprimir el nombre del producto
    printf("PRICE: %.2f\n", product->price); // Imprimir el precio del product
    free(product); // Liberar la memoria reservada para el producto
    return 0;
}