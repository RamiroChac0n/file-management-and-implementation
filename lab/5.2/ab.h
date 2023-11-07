#ifndef AB_H
#define AB_H

#define MAXLLAVES 4
#define MINLLAVES MAXLLAVES/2
#define NULO (-1)
#define SINLLAVE '@'

typedef struct {
    short contllave;
    char llave[MAXLLAVES];
    short hijo[MAXLLAVES+1];
} PAGINAAB;

#define TAMPAGINA sizeof(PAGINAAB)

#endif // AB_H