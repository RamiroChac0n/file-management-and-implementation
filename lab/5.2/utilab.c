//
// Created by Bezaleel on 27/09/23.
//
#include "ab.h"

crea_raiz(llave, izq, der)
char llave;
short izq, der;
{
    PAGINAAB pagina;
    short nrr;
    inciapag(&pagina);
    pagina.llave[0] = llave;
    pagina.hijo[0] = izq;
    pagina.hijo[1] = der;
    pagina.contllave = 1;
    escribeab(nrr, &pagina);
    colocaraiz(nrr);
    return (nrr);
}

iniciapag(a_pagina)
PAGINAAB *a_pagina; /* Apuntador a una página */
{
    int j;
    for (j=0; j<MAXLLAVES; j++) {
        a_pagina->llave[j] = SINLLAVE;
        a_pagina->hijo[j] = NULO;
    }
    a_pagina->hijo[MAXLLAVES] = NULO;
}

busca_nodo (llave, a_pagina, pos)
char llave;
PAGINAAB *a_pagina;
short *pos; /* Posición en donde la llave está o debe insertarse */
{
    int i;
    for (i=0; i<a_pagina->contllave && llave > a_pagina->llave[i]; i++);
    *pos = i;
    if (*pos < a_pagina->contllave && llave == a_pagina->llave[*pos])
        return (SI);    /* La llave está en la página */
    else
        return (NO);    /* La llave no está en la página */

}

ins_en_pag(llave, hijo_d, a_pagina)
char llave;
short hijo_d;
PAGINAAB *a_pagina;
{
    int i;
    for(i=a_pagina->contllave; llave < a_pagina->llave[i-1] && i>0; i--) {
        a_pagina->llave[i] = a_pagina->llave[i -1/*1 - 1*/]; //Cuidado con el 1 
        a_pagina->hijo[i+1] = a_pagina->hijo[i];
    }
    a_pagina->contllave++;
    a_pagina->llave[i] = llave;
    a_pagina->hijo[i+1] = hijo_d;
}

divide (llave, hijo_d, a_pagant, llave_promo, hijo_d_promo, a_pagnue)
char llave, /* Llave por insertar */
    *llave_promo;   /* Llave a promover hacía arriba desde aquí */
short hijo_d,   /* NRR del hijo por insertar */
    *hijo_d_promo;  /* NRR a promover hacía arriba desde aquí */

PAGINAAB    *a_pagant,  /* Apuntador a la página antecesora */
            *a_pagnue;  /* Apuntador a la página nueva */
{
    int i;
    short mitad;    /* Indica donde debe ocurrir la división */
    char llavesaux[MAXLLAVES+1];    /* Almacena temporalmente las llaves */
    short caraux[MAXLLAVES+2];  /* Almacena temporalmente los hijos */

    /*Antes de dividir mueve las llaves e hijos de la página anterior a 
    los arreglos de trabajo */
    for (i=0; i<MAXLLAVES; i++) {
        llavesaux[i] = a_pagant->llave[i];
        caraux[i] = a_pagant->hijo[i];
    }

    llavesaux[i] = a_pagant->hijo[i];
    /* Inserta la nueva llave */
    for (i=MAXLLAVES; llave < llavesaux[i-1] && i>0; i--) {
        llavesaux[i] = llavesaux[i-1];
        caraux[i+1] = caraux[i];
    }
    llavesaux[i] = llave;
    caraux[i+1] = hijo_d;

    /* Crea la página nueva para la división y
    promueve el NRR a la página nueva */
    *hijo_d_promo = tomapag();
    iniciapag(a_pagnue);

    /* Mueve la primera mitad de las llaves e hijos a la
    página anterior y la segunda a la página nueva, marca
    la segunda mitad como vacía */
    for(i=0; i<MINLLAVES; i++) {
        a_pagant->llave[i] = llavesaux[i];
        a_pagant->hijo[i] = caraux[i];
        a_pagnue->llave[i] = llavesaux[i+1+MINLLAVES];
        a_pagnue->hijo[i] = caraux[i+1+MINLLAVES];
        a_pagant->llave[i+MINLLAVES]=SINLLAVE;
        a_pagant->hijo[i+1+MINLLAVES]=NULO;
    }

    a_pagant->hijo[MINLLAVES] = caraux[MINLLAVES];
    a_pagnue->hijo[MINLLAVES] = caraux[i+1+MINLLAVES];
    a_pagnue->contllave = MAXLLAVES-MINLLAVES;
    a_pagant->contllave = MINLLAVES;

    *llave_promo = llavesaux[MINLLAVES]; /* Promueve la llave de enmedio*/
}