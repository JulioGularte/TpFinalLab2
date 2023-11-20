#include "PracticasXIngreso.h"
#include <string.h>
PracticasXIngreso crearPxI(int nroIngreso, int nroPractica, char resultado[])
{
    PracticasXIngreso pxi;
    pxi.eliminado=0;
    pxi.nroIngreso=nroIngreso;
    pxi.nroPractica=nroPractica;
    strcpy(pxi.resultado, resultado);
    return pxi;
}
