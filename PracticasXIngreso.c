#include "PracticasXIngreso.h"
#include <string.h>
#include <stdio.h>
PracticasXIngreso crearPxI(int nroIngreso, int nroPractica)
{
    char resultado [40];
    PracticasXIngreso pxi;
    pxi.eliminado=0;
    pxi.nroIngreso=nroIngreso;
    pxi.nroPractica=nroPractica;
    printf ("\n Ingrese el resultado de la practica: ");
    fflush(stdin);
    gets(pxi.resultado);
    return pxi;
}
