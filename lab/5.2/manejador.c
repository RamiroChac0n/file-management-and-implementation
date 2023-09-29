#include <stdio.h>
#include "ab.h"

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