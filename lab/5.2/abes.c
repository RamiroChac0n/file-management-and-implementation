//
// Created by Bezaleel on 27/09/23.
//
#include "ab.h"
#include <stdio.h>
#include <arches.h>

int daab;

abreab(){
    daab = open ("arbolb.dat", READWRITE);
    return (daab > 0);
}

cierraab(){
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

colocaraiz (raiz)
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

leeab(nrr, apunt_pagina)
short nrr;
PAGINAAB *apunt_pagina;
{
    long lseek(), dir;
    dir = (long)nrr * (long)TAMPAGINA + 2L;
    lseek(daab, dir, 0);
    return (read(daab, apunt_pagina, TAMPAGINA));
}

escribreab (nrr, apunt_pagina)
short nrr;
PAGINAAB *apunt_pagina;
{
    long lseek(), dir;
    dir = (long) nrr * (long) TAMPAGINA + 2L;
    lseek(daab, dir, 0);
    return (write(daab, apunt_pagina, TAMPAGINA));
}