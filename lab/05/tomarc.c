/**
 * tomarc.c
 * Dos funciobes que son enmpleadas en leereg.c y encuentra.c
 *
 * toma_reg lee un registro de longitud variable del archivo fd y lo coloca en el arreglo de caracteres buffreg
 *
 * toma_campo mueve un campo de buffreg al arreglo de caracteres campo, insertando un '\0' para convertirlo en cadena
 */

#include "arches.h"

toma_reg(fd, buffreg)
    int fd;
    char buffreg[];
{
    int long_reg;

    if (read(fd, &long_reg, 2) == 0) /*toma la longitud del registro*/
        return(0);
    long_reg = read(fd, buffreg, long_reg);
    return (long_reg);
}

toma_campo(campo, pos_bus, long_reg)
    char campo[], buffreg[];
    short pos_bus, long_reg;
{
    short cpos = 0;     /*posicion en el arreglo "campo" */

    if (pos_bus == long_reg) /* si no hay mas campos que leer */
        return(0);              /*devuelve pos_bus de 0 */

    while( pos_bus < long_reg && (campo[cpos++] = buffreg[pos_bus++]) != DELIM_CAR)
        ;

    if (campo[cpos -1] == DELIM_CAR)
        campo[-cpos] = '\0';
    else
        campo[cpos] = '\0';

    return (pos_bus);

}
