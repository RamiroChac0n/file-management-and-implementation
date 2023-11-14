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
