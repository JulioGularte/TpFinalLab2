#ifndef NODOPRACTICA_H_INCLUDED
#define NODOPRACTICA_H_INCLUDED
#include "Practicas.h"
typedef struct _NodoPractica
{
    Practica practica;
    struct _NodoPractica * siguiente;
}NodoPractica;
NodoPractica * inicListaPractica ();
NodoPractica * crearNodoPractica (Practica practica);
NodoPractica * agregarPrincipio (NodoPractica *lista, NodoPractica *nuevoNodo);
void agregarPracticaArchivo (NodoPractica * lista, Practica practica);
int existePracticaEnArchivo(char nombrePractica []);
#endif // NODOPRACTICA_H_INCLUDED
