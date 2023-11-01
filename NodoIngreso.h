#ifndef NODOINGRESO_H_INCLUDED
#define NODOINGRESO_H_INCLUDED
#include "Ingreso.h"
typedef struct _nodoIngresos
{
    Ingreso ingreso;
    struct _Ingresos * siguiente;
    struct _Ingresos * anterior;
    struct _PracticasXIngresos * practicasIngreso;
}NodoIngresos;


#endif // NODOINGRESO_H_INCLUDED
