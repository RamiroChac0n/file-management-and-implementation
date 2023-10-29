#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "product.h"

#define SIZE_TABLE 29

typedef struct {
    char* key;
    Product* product;
} Node;

Node* hashTable[SIZE_TABLE];

void init_hash_table() {
    for (int i = 0; i < SIZE_TABLE; i++) {
        hashTable[i] = NULL;
    }
}

int hash_function(char* key) {
    int sum = 0;
    for (int i = 0; key[i] != '\0'; i++) {
        sum += key[i];
    }
    return sum % SIZE_TABLE;
}

void insert(Product* product) {
    int index = hash_function(product->id);

    while (hashTable[index] != NULL) {
        index = (index + 1) % SIZE_TABLE; // Saturación progresiva: buscar la siguiente posición disponible
    }

    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = strdup(product->id);

    // Crear una nueva instancia de Product y copiar el contenido del producto proporcionado
    Product* newProduct = (Product*)malloc(sizeof(Product));
    newProduct->id = strdup(product->id);
    newProduct->name = strdup(product->name);
    // Copiar otros campos según sea necesario...

    newNode->product = newProduct;
    hashTable[index] = newNode;
}


char* search(char* key) {
    int index = hash_function(key);

    while (hashTable[index] != NULL) {
        if (strcmp(hashTable[index]->key, key) == 0) {
            return hashTable[index]->product->name;
        }
        index = (index + 1) % SIZE_TABLE; // Saturación progresiva: buscar la siguiente posición en caso de colisión
    }

    return NULL; // Valor no encontrado
}

void display_hash_table() {
    system("clear");
    printf("Tabla Hash:\n");
    for (int i = 0; i < SIZE_TABLE; i++) {
        if (hashTable[i] != NULL) {
            printf(" %02d: Key: %s Producto: %s\n", i, hashTable[i]->product->id, hashTable[i]->product->name);
        } else {
            printf(" %02d: -----\n", i);
        }
    }
}


/*int main() {
    init_hash_table();

    insert("hola", 5);
    insert("adios", 10);
    insert("ejemplo", 20);
    insert("llave", 30); // Colisión con "ejemplo"
    insert("valor", 40); // Colisión con "hola"

    printf("El valor para 'hola' es: %d El hash es: %d\n", search("hola"), hash_function("hola"));
    printf("El valor para 'adios' es: %d El hash es: %d\n", search("adios"), hash_function("adios"));
    printf("El valor para 'ejemplo' es: %d El hash es: %d\n", search("ejemplo"), hash_function("ejemplo"));
    printf("El valor para 'no existe' es: %d El hash es: %d\n", search("no existe"), hash_function("no existe"));
    printf("El valor para 'llave' es: %d El hash es: %d\n", search("llave"), hash_function("llave"));
    printf("El valor para 'valor' es: %d El hash es: %d\n", search("valor"), hash_function("valor"));

    return 0;
}*/
