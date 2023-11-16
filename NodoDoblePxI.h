#ifndef NODODOBLEPXI_H_INCLUDED
#define NODODOBLEPXI_H_INCLUDED
#include "PracticasXIngreso.h"
typedef struct _NodoDoblePxI {
    PracticaXIngreso practica;
    struct _NodoDoblePxI * siguiente;
    struct _NodoDoblePxI * anterior;
}NodoDoblePxI;
///generales
NodoDoblePxI * inicListaDoblePxI (NodoDoblePxI * lista);
NodoDoblePxI * crearNodoDoblePxI (PracticaXIngreso practica);
NodoDoblePxI * agregarPpioDoblePxI (NodoDoblePxI * lista, NodoDoblePxI * nuevoNodo);
///baja en cascada
void bajaDeIngreso (NodoDoblePxI * lista, int idIngreso);
void bajaDePxIEnCascadaLista (NodoDoblePxI * lista, int nroIngreso);
#endif // NODODOBLEPXI_H_INCLUDED
