#include "arches.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define EXITO 1
#define FRACASO 0

int toma_campo();
int toma_reg();
int cadespac();
void mayusculas();
int hazllave();

/*
    El programa principal abre un archivo de registros secuenciales y permite
    al usuario buscar un registro por medio de una llave compuesta por el
    apellido y el nombre.
*/
int main() {
    int fd, long_reg, pos_bus;
    int encontro;
    char llave_bus[30], llave_enc[30], apellido[30], nombre[30];
    char nomarch[15];
    char buffreg[TAM_MAX_REG + 1];
    char campo[TAM_MAX_REG + 1];

    printf("Proporcione el nombre del archivo en donde buscar: ");
    gets(nomarch);
    if ((fd = creat(nomarch, SOLOLECT)) < 0 ) {
        printf("Error en la apertura del archivo - Fin de programa\n");
        exit(1);
    }

    printf("\n\nDigite el apellido: "); /* tomna la llave de busqueda */
    gets(apellido);
    printf("\n\nDigite el nombre: ");
    gets(nombre);
    hazllave(apellido, nombre, llave_bus);

    encontro = FRACASO;
    while (!encontro && (long_reg = toma_reg(fd, buffreg)) > 0 ) {
        pos_bus = 0;
        pos_bus = toma_campo(apellido, buffreg, pos_bus, long_reg);
        pos_bus = toma_campo(nombre, buffreg, pos_bus, long_reg);
        hazllave(apellido, nombre, llave_enc);
        if (strcmp(llave_enc, llave_bus) == 0)
            encontro = EXITO;
    }

    if (encontro) {
        printf("\n\nSe encontro el registro: \n\n");
        pos_bus = 0;

        while ((pos_bus = toma_campo(campo, buffreg, pos_bus, long_reg)) > 0)
            printf("\t%s\n", campo);
    } else
        printf("\n\nNo se encontro el registro. \n");

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
int cadespac(cad)
    char cad[];
{
    int i;

    for (i = strlen(cad) - 1; i >= 0 && cad[i] == ' '; i--)
        ;

    cad[++i] = '\0';
    return(i);
}
void mayusculas(cadent, cadsal)
    char cadent[], cadsal[];
{
    while (*cadsal++ = (*cadent >= 'a' && *cadent <= 'z') ? *cadent & 0x5F : *cadent)
        cadent++;
}
int hazllave(apellido, nombre, cad)
    char apellido[], nombre[], cad[];
{
    int longap, longnom;

    longap = cadespac(apellido);
    strcpy(cad, apellido);
    cad[longap++] = ' ';
    cad[longap] = '\0';
    longnom = cadespac(nombre);
    strcat(cad, nombre);
    mayusculas(cad, cad);
    return(longap + longnom);
}