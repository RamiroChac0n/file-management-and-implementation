#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE_TABLE 29

typedef struct {
    char* key;
    int value;
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

void insert(char* key, int value) {
    int index = hash_function(key);

    while (hashTable[index] != NULL) {
        index = (index + 1) % SIZE_TABLE; // Saturación progresiva: buscar la siguiente posición disponible
    }

    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = strdup(key);
    newNode->value = value;
    hashTable[index] = newNode;
}

int search(char* key) {
    int index = hash_function(key);

    while (hashTable[index] != NULL) {
        if (strcmp(hashTable[index]->key, key) == 0) {
            return hashTable[index]->value;
        }
        index = (index + 1) % SIZE_TABLE; // Saturación progresiva: buscar la siguiente posición en caso de colisión
    }

    return -1; // Valor no encontrado
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
