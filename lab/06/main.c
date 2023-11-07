#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "product.h"
#include "id_generator.h"
#include "hash_table.h"

void info_product(){
    Product* product = (Product*) malloc(sizeof(Product));
    char name[23];
    float price;
    char* id = id_generator();
    printf("ID: %s\n", id);
    printf("Nombre del producto: ");
    scanf("%s", name);
    printf("Precio del producto: ");
    scanf("%f", &price);

    product->id = id;
    product->name = name;
    product->price = price;

    insert(product);
    free(product);
}

void search_product() {
    char* id;
    printf("ID del producto: ");
    scanf("%s", id);
    Product* product = search(id);

    if (product != NULL) {
        system("clear");
        printf("==================================================\n");
        printf("ID: %s\n", product->id);
        printf("Nombre del producto: %s\n", product->name);
        printf("Precio del producto: %.2f\n", product->price);
        printf("==================================================\n");
    } else {
        printf("Producto no encontrado\n");
    }
}

int main() {
    system("clear");
    int eleccion = 0;
    do
    {
        printf("1. Insertar producto\n");
        printf("2. Buscar producto\n");
        printf("3. Mostrar productos\n");
        printf("0. Salir\n");
        printf("Elija una opción: ");
        scanf("%d", &eleccion);
        printf("\n");

        switch (eleccion)
        {
        case 1:
            info_product();
            break;
        case 2:
            search_product();
            break;
        case 3:
            display_hash_table();
            break;
        case 0:
            printf("Saliendo...\n");
            break;
        default:
            printf("Opción no válida\n");
            break;
        }
        printf("\n");
    } while (eleccion != 0);
    
    return 0;
}