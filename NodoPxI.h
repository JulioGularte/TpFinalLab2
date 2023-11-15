#ifndef NODOPXI_H_INCLUDED
#define NODOPXI_H_INCLUDED
#include "PracticasXIngreso.h"

typedef struct _NodoPxI
{
    PracticasXIngreso PxI;

    struct NodoPxI * siguiente;
    struct NodoPxI * anterior;

}NodoPxI;

NodoPxI * inicListaPxI();
NodoPxI * crearNodoPxI(PracticasXIngreso datoPxI);
NodoPxI * cargarListaPxI_inicio(NodoPxI * listaPxI, PracticasXIngreso datoPxI);
NodoPxI * buscarNodoPxI(NodoPxI * listaPxI, PracticasXIngreso datoPxI);
NodoPxI * eliminarNodo(NodoPxI * listaPxI, PracticasXIngreso datoPxI);
NodoPxI * modificarPxI(NodoPxI * nodoAModificar);


#endif // NODOPXI_H_INCLUDED
