#include "arches.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define LONG_REG 64
typedef char NODOLLAVE[30];
typedef char REGDATOS [LONG_REG +1];
static struct{
    short cont_reg;
    char relleno[30];
} encabezado;

static int toma_archent();
static int toma_archsal();

static int cadespac();
static int hazllave();
static void clasif_shell();
static int toma_campo();
static void mayusculas();
static void extrae_llave();

/*
    La función main() es el programa principal. El programa lee el nombre del
    archivo de entrada y del archivo de salida, abre los archivos y lee el
    encabezado del archivo de entrada. A continuación, el programa lee los
    registros del archivo de entrada y los coloca en un arreglo de registros.
    El programa crea un arreglo de llaves a partir de los registros y un arreglo
    de índices que apuntan a los registros. El programa clasifica los índices
    de acuerdo con el orden de las llaves y escribe los registros en el archivo
    de salida en el orden especificado por los índices.
*/
int main(){
    int fd_ent, fd_sal, i, cont_reg;
    //char *calloc();
    REGDATOS *registros;
    NODOLLAVE *nodosllave;
    short *indice;

    fd_ent = toma_archent();
    fd_sal = toma_archsal();

    if(fd_ent < 0 || fd_sal < 0){
        printf("Programa terminado\n");
        exit(1);
    }

    cont_reg = encabezado.cont_reg;

    registros = (REGDATOS *) calloc(cont_reg, sizeof(REGDATOS));
    nodosllave = (NODOLLAVE *) calloc(cont_reg, sizeof(NODOLLAVE));
    indice = (short *) calloc(cont_reg, sizeof(short));
    
    if(registros == 0L || nodosllave == 0L || indice == 0L){
        printf("No se pudo asignar el espacio requerido\n");
        printf("El archivo es demasiado grande para\n");
        printf("clasificarse en memoria\n");
        exit(1);
    }

    for(i = 0; i < cont_reg; i++){
        read(fd_ent, registros[i], LONG_REG);
        extrae_llave(nodosllave[i], registros[i]);
        indice[i] = i;
    }

    clasif_shell(indice, nodosllave, cont_reg);

    for(i = 0; i < cont_reg; i++)
        write(fd_sal, registros[indice[i]], LONG_REG);

    close(fd_ent);
    close(fd_sal);
    return(0);
}


/*
    La función toma_archent() abre el archivo de entrada y lee el encabezado
    del archivo. Si el archivo no puede abrirse, se imprime un mensaje de error
    y se termina el programa. Si el archivo se abre correctamente, se lee el
    encabezado del archivo y se devuelve el descriptor de archivo del archivo
    de entrada.
*/
static int toma_archent(){
    char nomarch[30];
    int fd;

    printf("Proporcione el nombre del archivo de entrada: ");
    fgets(nomarch, 30, stdin);
    if((fd = open(nomarch, LECTESCRIT)) < 0){
        printf("El archivo %s no puede abrirse\n", nomarch);
        exit(1);
    }else{
        read(fd, &encabezado, sizeof(encabezado));
    }
    return(fd);
}


/*
    La función toma_archsal() abre el archivo de salida y escribe el encabezado
    del archivo. Si el archivo no puede abrirse, se imprime un mensaje de error
    y se termina el programa. Si el archivo se abre correctamente, se escribe el
    encabezado del archivo y se devuelve el descriptor de archivo del archivo
    de salida.
*/
static int toma_archsal(){
    char nomarch[30];
    int fd;

    printf("Proporcione el nombre del archivo de salida: ");
    fgets(nomarch, 30, stdin);
    if((fd = creat(nomarch, PMODE/*0644MODOP*/)) < 0){
        printf("El archivo %s no puede crearse\n", nomarch);
    }else{
        write(fd, &encabezado, sizeof(encabezado));
    }
    return(fd);
}

#define CAMPO_LLAVE(i) nodosllave [indice[(i)]]
typedef char NODOLLAVE[30];

/*
    La función clasif_shell() clasifica los registros en el arreglo de índices
    de acuerdo con el orden de las llaves en el arreglo de llaves. La clasificación
    se realiza mediante el método de clasificación shell.
*/
void clasif_shell(indice, nodosllave, n)
    short indice[];
    NODOLLAVE nodosllave[];
    int n;
{
    int espacio, i, j;
    char *llave_ins;
    short subindice_ins;

    for(espacio = n >> 1; espacio > 0; espacio >>= 1){
        for(j = espacio; j < n; j++){
            llave_ins = CAMPO_LLAVE(j);
            subindice_ins = indice[j];
            for(i = j - espacio; i >= 0; i -= espacio){
                if(strcmp(CAMPO_LLAVE(i), llave_ins) <= 0)
                    break;
                indice[i + espacio] = indice[i];
            }
            indice[i + espacio] = subindice_ins;
        }
    }
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

/*
    La función cadespac() elimina los espacios en blanco del final de la cadena
    "cad". La función devuelve la longitud de la cadena sin los espacios en blanco.
*/
int cadespac(cad)
    char cad[];
{
    int i;

    for (i = strlen(cad) - 1; i >= 0 && cad[i] == ' '; i--)
        ;

    cad[++i] = '\0';
    return(i);
}

/*
    La función mayusculas() convierte la cadena "cadent" en mayúsculas y la
    coloca en la cadena "cadsal".
*/
void mayusculas(cadent, cadsal)
    char cadent[], cadsal[];
{
    while (*cadsal++ = (*cadent >= 'a' && *cadent <= 'z') ? *cadent & 0x5F : *cadent)
        cadent++;
}

/*
    La función hazllave() crea una llave a partir de los campos "apellido" y
    "nombre" y la coloca en la cadena "cad". La función devuelve la longitud
    de la llave.
*/
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

/*
    La función extrae_llave() extrae la llave del registro y la coloca en la
    cadena "llave".
*/
static void extrae_llave(llave, registro)
    REGDATOS registro;
    char llave[];
{
    int pos_bus;
    char nombre[30], apellido[30];

    pos_bus = 0;
    pos_bus = toma_campo(apellido, registro, pos_bus, LONG_REG);
    pos_bus = toma_campo(nombre, registro, pos_bus, LONG_REG);
    hazllave(apellido, nombre, llave);
}