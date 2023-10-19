#include <stdlib.h>
#include <time.h>

char* id_generator() {
    char* new_id = malloc(7 * sizeof(char)); // Reservar memoria para la new_id de resultado
    srand(time(NULL)); // Inicializar la semilla aleatoria

    // Generar 3 letras aleatorias
    for (int i = 0; i < 3; i++) {
        new_id[i] = 'A' + rand() % 26; // Generar una letra aleatoria entre A y Z
    }

    // Generar 3 números aleatorios
    for (int i = 3; i < 6; i++) {
        new_id[i] = '0' + rand() % 10; // Generar un número aleatorio entre 0 y 9
    }

    new_id[6] = '\0'; // Agregar el carácter nulo al final de la new_id de resultado

    return new_id;
}