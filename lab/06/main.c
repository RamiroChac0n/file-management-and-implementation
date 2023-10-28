#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "product.h"
#include "id_generator.h"
#include "hash_table.h"

int main() {
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
            insert_product();
            break;
        case 2:
            search_product();
            break;
        case 3:
            show_products();
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