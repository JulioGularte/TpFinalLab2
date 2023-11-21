#ifndef NODOINGRESO_H_INCLUDED
#define NODOINGRESO_H_INCLUDED
#include "Ingreso.h"
typedef struct _nodoIngresos
{
    Ingreso ingreso;
    struct _nodoIngresos * siguiente;
    struct _nodoIngresos * anterior;
    struct _NodoPxI * listaPxI;
}NodoIngresos;


#endif // NODOINGRESO_H_INCLUDED
