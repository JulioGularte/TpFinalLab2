#ifndef NODOPXI_H_INCLUDED
#define NODOPXI_H_INCLUDED
#include "PracticasXIngreso.h"
typedef struct _NodoPxI
{
    PracticasXIngreso PxI;
    struct _NodoPxI * siguiente;
}NodoPxI;
NodoPxI * inicListaPxI ();
NodoPxI * crearNodoPxI (PracticasXIngreso pxi);
NodoPxI * agregarPrincipioPractica (NodoPxI * lista, NodoPxI * nuevoNodo);
#endif // NODOPXI_H_INCLUDED
