#ifndef NODOINGRESO_H_INCLUDED
#define NODOINGRESO_H_INCLUDED
#include "Ingreso.h"
typedef struct _nodoIngresos
{
    Ingreso ingreso;
    struct NodoIngresos * siguiente;
    struct NodoIngresos * anterior;
    struct NodoPxI * listaPxI;
}NodoIngresos;


#endif // NODOINGRESO_H_INCLUDED
