#include "arches.h"
#include <stdio.h>
#include <string.h>
#define LONG_REG 64
#define campo_a_buffreg(br, cad) strcat(br, cad); strcat(br, DELIM_CAD);

static char *solicitud[] = {"   Apellido: ",
                            "     Nombre: ",
                            "  Direccion: ",
                            "     Ciudad: ",
                            "     Estado: ",
                            "Cod. Post.: ",
                            "\0"
                           };
static int fd;
static struct{
    short   cont_reg;
    char    relleno[60]; 
} encabezado;

static int menu();
static void pide_info(char buffreg[]);
static int pide_nrr();
static void lee_y_muestra();
static int cambio();

void mayusculas(cadent, cadsal);
int toma_campo(char campo[], char buffreg[], short pos_bus, short long_reg);

int main(){
    int i, menu_elec, nrr;
    int byte_pos;
    char nomarch[15];
    long lseek();
    char buffreg[TAM_MAX_REG +1];

    printf("Proporcione el nombre del archivo que quiere crear: ");
    fgets(nomarch, 15, stdin);
    if((fd = open(nomarch, LECTESCRIT)) < 0){
        fd = creat(nomarch, PMODE);
        encabezado.cont_reg = 0;
        write(fd, &encabezado, sizeof(encabezado));
    }else{
        read(fd, &encabezado, sizeof(encabezado));
    }
    while((menu_elec = menu()) < 3){
        switch(menu_elec){
            case 1:
                printf("Proporcione la información del registro nuevo\n\n");
                pide_info(buffreg);
                byte_pos = encabezado.cont_reg * LONG_REG + sizeof(encabezado);
                lseek(fd, (long) byte_pos, 0);
                write(fd, buffreg, LONG_REG);
                encabezado.cont_reg++;
                break;
            case 2:
                nrr = pide_nrr();

                if(nrr >= encabezado.cont_reg){
                    printf("El numero de registro es demasiado grande\n");
                    printf("... se vuelve al menu ...");
                    break;
                }

                byte_pos = nrr * LONG_REG + sizeof(encabezado);
                lseek(fd, (long) byte_pos, 0);

                lee_y_muestra();
                if(cambio()){
                    printf("\n\nProporcione los valores revisados: \n\n");
                    pide_info(buffreg);
                    lseek(fd, (long) byte_pos, 0);
                    write(fd, buffreg, LONG_REG);
                }
                break;
        }
    }
    lseek(fd, 0L, 0);
    write(fd, &encabezado, sizeof(encabezado));
    close(fd);
    return(0);
}

static int menu(){
    int elección;
    char respuesta[10];

    printf("\n\n\n\n        PROGRAMA DE ACTUALIZACIÓN DEL ARCHIVO\n");
    printf("\n\nUd. Puede elegir:\n\n");
    printf("\n1. Agregar un registro al final del archivo\n");
    printf("\n2. Extraer un registro para actualizarlo\n");
    printf("\n3. Salir del programa\n\n");
    printf("Proporcione el número de su elección: ");
    fgets(respuesta, 10, stdin);
    /*gets(respuesta);*/
    elección = atoi(respuesta);
    return(elección);
}

static void pide_info(buffreg)
    char buffreg[];
{
    int con_campos, i;
    char respuesta[50];

    for(i = 0; i < TAM_MAX_REG; i++)
        buffreg[i] = '\0';

    for(i = 0; *solicitud[i] != '\0'; i++){
        printf("%s", solicitud[i]);
        fgets(respuesta, 50, stdin);
        campo_a_buffreg(buffreg, respuesta);
    }
}

static int pide_nrr(){
    int nrr;
    char respuesta[10];

    printf("\n\nDigite el número relativo del registro\n");
    printf("\tque desee actualizar: ");
    gets(respuesta);
    nrr = atoi(respuesta);
    return(nrr);
}

static void lee_y_muestra(){
    char buffreg[TAM_MAX_REG +1], campo[TAM_MAX_REG +1];
    int pos_bus, long_datos;

    pos_bus = 0;
    read(fd, buffreg, LONG_REG);

    printf("\n\n\n\nContenido del registro existente\n");

    buffreg[LONG_REG] = '\0';

    long_datos = strlen(buffreg);

    while((pos_bus = toma_campo(campo, buffreg, pos_bus, long_datos)) > 0)
        printf("\t%s\n", campo);
}

static int cambio(){
    char respuesta[10];

    printf("\n\nDesea modificar este registro?\n");
    printf(" Conteste S o N, seguido por <ENTER>  ==>");
    gets(respuesta);
    mayusculas(respuesta,respuesta);
    return((respuesta[0] == 'S') ? 1 : 0);
}

void mayusculas(cadent, cadsal)
    char cadent[], cadsal[];
{
    while (*cadsal++ = (*cadent >= 'a' && *cadent <= 'z') ? *cadent & 0x5F : *cadent)
        cadent++;
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