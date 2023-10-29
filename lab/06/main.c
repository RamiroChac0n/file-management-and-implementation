#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "product.h"
#include "id_generator.h"
#include "hash_table.h"

void info_product(){
    Product* product = (Product*) malloc(sizeof(Product));
    char name[23];
    int price;
    char* id = id_generator();
    printf("ID: %s\n", id);
    printf("Nombre del producto: ");
    scanf("%s", name);
    printf("Precio del producto: ");
    scanf("%d", &price);

    product->id = id;
    product->name = name;
    product->price = price;

    insert(product);
    free(product);
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
            //search_product();
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