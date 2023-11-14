#include "arches.h"

/*
    La función toma_reg() lee un registro del archivo "fd" y lo coloca en el
    arreglo "buffreg". La función devuelve la longitud del registro leído.
*/
int toma_reg(fd, buffreg)
    int fd;
    char buffreg[];
{
    int long_reg;

    if (read(fd, &long_reg, 2) == 0) /*toma la longitud del registro*/
        return(0);
    long_reg = read(fd, buffreg, long_reg);
    return (long_reg);
}

/*
    La función toma_campo() toma un campo del registro y lo coloca en el arreglo
    "campo". La función devuelve la posición del siguiente campo en el registro.
*/
int toma_campo(campo, buffreg, pos_bus, long_reg)
    char campo[], buffreg[];
    short pos_bus, long_reg;
{
    short cpos = 0;     /*posicion en el arreglo "campo" */

    if (pos_bus == long_reg) /* si no hay mas campos que leer */
        return(0);              /*devuelve pos_bus de 0 */

    while( pos_bus < long_reg && (campo[cpos++] = buffreg[pos_bus++]) != DELIM_CAR);

    if (campo[cpos -1] == DELIM_CAR)
        campo[-cpos] = '\0';
    else
        campo[cpos] = '\0';

    return (pos_bus);

}
