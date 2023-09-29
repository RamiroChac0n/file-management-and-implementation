#include <stdio.h>
#include "ab.h"
#include "arches.h"
#define READWRITE 2
#define SI 1
#define NO 0



int main(){
    int promovido;      /* booleano: indica si hay una promocion */
    short   raiz,       /* NRR de la raíz */
            nrr_promo;  /* NRR que se promueve */
    char llave_promo,   /* llave que se promueve */
         llave;         /* Siguiente llave por insertar en el arbol */
    
    if(abreab())            /* Intenta abrir arbolb.dat y obtener la raíz */
        raiz = tomaraiz();
    else                    /* Si arbolb.dat no existe lo crea */
        raiz = crea_arbol();

    while((llave = getchar()) != 'q'){
        promovido = inserta(raiz, llave, &nrr_promo, &llave_promo);
        if(promovido)      /* Si hubo promoción */
            raiz = crea_raiz(llave_promo, raiz, nrr_promo);
    }
    cierraab();             /* Cierra arbolb.dat */
    return 0;
}


// CÓDIGO DE utilab.c
short crea_raiz(llave, izq, der)
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

// CÓDIGO DE abes.c
int daab;

int abreab(){
    daab = open ("arbolb.dat", READWRITE);
    return (daab > 0);
}

void cierraab(){
    close (daab);
}

short tomaraiz (){
    short raiz;
    long lseek ();
    lseek (daab, 0L, 0);
    if (read (daab,&raiz, 2)==0){
        printf ("Error: No se pudo obtener la raiz. \007\n");
        exit (1);
    }
    return (raiz);
}

void colocaraiz (raiz)
short raiz;
{
    long lseek ();
    lseek (daab, 0L, 0);
    write (daab, &raiz, 2);
}

short crea_arbol(){
    char llave;
    daab = creat ("arbolb.dat", PMODE);
    close(daab);
    abreab();   /* Para asegurar el acceso de lectura y escritura. */
    llave = getchar();  /* Toma la primera llave */
    return (crea_raiz(llave, NULO, NULO));
}

short tomapag()
{
    long lseek(), dir;
    dir = lseek(daab, 0L, 2) -2L;
    return ((short) dir/ TAMPAGINA);
}

int leeab(nrr, apunt_pagina)
short nrr;
PAGINAAB *apunt_pagina;
{
    long lseek(), dir;
    dir = (long)nrr * (long)TAMPAGINA + 2L;
    lseek(daab, dir, 0);
    return (read(daab, apunt_pagina, TAMPAGINA));
}

int escribreab (nrr, apunt_pagina)
short nrr;
PAGINAAB *apunt_pagina;
{
    long lseek(), dir;
    dir = (long) nrr * (long) TAMPAGINA + 2L;
    lseek(daab, dir, 0);
    return (write(daab, apunt_pagina, TAMPAGINA));
}

//CÓDIGO DE utilab.c
void iniciapag(a_pagina)
PAGINAAB *a_pagina; /* Apuntador a una página */
{
    int j;
    for (j=0; j<MAXLLAVES; j++) {
        a_pagina->llave[j] = SINLLAVE;
        a_pagina->hijo[j] = NULO;
    }
    a_pagina->hijo[MAXLLAVES] = NULO;
}

int busca_nodo (llave, a_pagina, pos)
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

void ins_en_pag(llave, hijo_d, a_pagina)
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

void divide (llave, hijo_d, a_pagant, llave_promo, hijo_d_promo, a_pagnue)
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

//CÓDIGO DE inserta.c
int inserta (nrr, llave, hijo_d_promo, llave_promo)
short nrr,  /* NRR de pagina en donde se va a insertar */
     *hijo_d_promo; /* Hijo promovido al siguiente nivel */
char llave, /* Llave por insertar aqui o más abajo */
     *llave_promo;  /* Llave promovida al siguiente nivel */

{
        PAGINAAB pagina,    /* Página actual */
        pagnueva;   /* Página nueva creada si hubo división */

        int encontro;   /* Valores booleanos */
        short poss, 
            nrr_p_a;    /* NRR promovido desde abajo */
        char llave_p_a; /* Llave promovida desde abajo */

        if (nrr == NULO) {  /* Se pasó del fondo del arbol "promocion" ...*/
            *llave_promo = llave;   /*...de la llave original de modo que ...*/
            *hijo_d_promo = NULO;   /*...será insertada en el nivel hoja */
            return (SI);
        }

        leeab (nrr, &pagina);
        encontro = busca_nodo (llave, &pagina, &poss);
        if (encontro){
            printf ("Error: intento de insercion de llave duplicada: %c\n\007", llave);
            return (0);
        }

        int promovido = inserta (pagina.hijo[poss], llave, &nrr_p_a, &llave_p_a);
        if (!promovido)
            return (NO);    /* No hay promoción */
        if (pagina.contllave < MAXLLAVES) {

            /* Listo para insertar la llave y el apuntador en esta pagina */
            ins_en_pag (llave_p_a, nrr_p_a, &pagina);
            return (NO);    /* No hay promoción*/
        } else {
            divide(llave_p_a, nrr_p_a, &pagina, llave_promo, hijo_d_promo, &pagnueva);
            escribeab(nrr, &pagina);
            escribeab(*hijo_d_promo, &pagnueva);
            return (SI);    /* Si hubo promoción */
        }
}