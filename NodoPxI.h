#ifndef NODOPXI_H_INCLUDED
#define NODOPXI_H_INCLUDED
#include "PracticasXIngreso.h"
#include "NodoIngreso.h"
typedef struct _NodoPxI
{
    PracticasXIngreso PxI;
    struct _NodoPxI * siguiente;
}NodoPxI;
NodoPxI * inicListaPxI ();
NodoPxI * crearNodoPxI (PracticasXIngreso pxi);
NodoPxI * agregarPrincipioPractica (NodoPxI * lista, NodoPxI * nuevoNodo);
int ExisteIngresoActivoEnPractica (NodoPxI * lista, int PracticaId);
void guardarPracticasXIngresoDelPacienteEnArchivo (NodoIngresos * listaDeIngresosPaciente);

#endif // NODOPXI_H_INCLUDED
