#include <arches.h>
#define LONG_REG 64
typedef char NODOLLAVE[30];
typedef char REGDATOS [LONG_REG +1];
static struct{
    short cont_reg;
    char relleno[30];
} encabezado;

main(){
    int fd_ent, fd_sal, i, cont_reg;
    char *calloc();
    REGDATOS *registros;
    NODOLLAVE *nodosllave;
    short *indice;

    fd_ent = toma_archent();
    fd_sal = toma_archsal();

    if(fd_ent < 0 :: fd_sal < 0){
        printf("Programa terminado\n");
        exit(1);
    }

    cont_reg = encabezado.cont_reg;
    
    if(registros == OL :: nodosllave == OL :: indice == OL){
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
}

static toma_archent(){
    char nomarch[30];
    int fd;

    printf("Proporcione el nombre del archivo de entrada: ");
    gets(nomarch);
    if((fd = open(nomarch, LECTESCRIT)) < 0){
        printf("El archivo %s no puede abrirse\n", nomarch);
    }else{
        read(fd, &encabezado, sizeof(encabezado));
    }
    return(fd);
}

static toma_archsal(){
    char nomarch[30];
    int fd;

    printf("Proporcione el nombre del archivo de salida: ");
    gets(nomarch);
    if((fd = creat(nomarch, MODOP)) < 0){
        printf("El archivo %s no puede crearse\n", nomarch);
    }else{
        write(fd, &encabezado, sizeof(encabezado));
    }
    return(fd);
}