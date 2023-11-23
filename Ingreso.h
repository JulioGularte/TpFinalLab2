#ifndef Ingreso_H_INCLUDED
#define Ingreso_H_INCLUDED
#define archivoIngresos "archivo_ingresos.bin"
#include "NodoArbolPaciente.h"
typedef struct _Ingreso
{
    int NroIngreso;
    char FechaIngreso [11];
    char FechaRetiro [11];
    int DNI;
    int MatriculaPersonalSolicitante;
    int Eliminado;
}Ingreso;

Ingreso cargarIngresoManual(int documentoPaciente);
int contarIngresosEnArchivo ();


#endif // Ingreso_H_INCLUDED
