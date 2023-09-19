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