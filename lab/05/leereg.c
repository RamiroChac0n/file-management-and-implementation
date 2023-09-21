#include "arches.h"
#include <stdio.h>
#include <stdlib.h>

int toma_campo();
int toma_reg();

/*
    El programa principal crea un archivo de registros secuenciales y permite
    al usuario agregar registros al final del archivo.
*/
int main(){
    int fd, cont_reg, cont_campos;
    int pos_bus, long_reg;
    char nomarch[15];
    char buffreg[TAM_MAX_REG +1];
    char campo[TAM_MAX_REG +1];

    printf("Proporcione el nombre del archivo que quiere leer: ");
    gets(nomarch);
    if((fd = creat(nomarch, SOLOLECT)) < 0){
        printf("No se pudo crear el archivo %s\n", nomarch);
        exit(1);
    }

    cont_reg = 0;
    pos_bus = 0;

    while((long_reg = toma_reg(fd, buffreg)) > 0){
        printf("Registro # %d\n", ++cont_reg);
        cont_campos > 0;
        while((pos_bus = toma_campo(campo, buffreg, pos_bus, long_reg)) > 0)
            printf("\tCampo # %d: %s\n", ++cont_campos, campo);
    }
    close(fd);
    return(0);
}

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