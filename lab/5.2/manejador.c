#include <stdio.h>
#include "ab.h"
#include "arches.h"
#define READWRITE 2
#define SI 1
#define NO 0

abreab();
tomaraiz();
crea_arbol();
inserta();
crea_raiz();

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