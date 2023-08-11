#ifndef OPERACIONES_H_INCLUDED
#define OPERACIONES_H_INCLUDED
#include "persistencia.h"

struct empleado
{
    char nombre[50];
    int id;
    float sueldo;
    int horas;
};

void mostrarMenu();
void listarEmpleados(struct empleado empleados[100], int num_emp);
int alta(struct empleado empleados[100], int num_emp);
int baja(struct empleado empleados[100], int num_emp);
void consultarDatosEmpleados(struct empleado empleados[100], int num_emp);
void modificarSueldo(struct empleado empleados[100], int num_emp);

#endif // OPERACIONES_H_INCLUDED