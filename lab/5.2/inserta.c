//
// Created by Bezaleel on 27/09/23.
//
#include <ab.h>

inserta (nrr, llave, hijo_d_promo, llave_promo)
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

        promocion = inserta (pagina.hijo[poss], llave, &nrr_p_a, &llave_p_a);
        if (!promocion)
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