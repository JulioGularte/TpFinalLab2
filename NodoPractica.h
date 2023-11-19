#ifndef NODOPRACTICA_H_INCLUDED
#define NODOPRACTICA_H_INCLUDED
#include "Practicas.h"
#include "NodoPxI.h"
typedef struct _NodoPractica
{
    Practica practica;
    struct _NodoPractica * siguiente;
}NodoPractica;
NodoPractica * inicListaPractica ();
NodoPractica * crearNodoPractica (Practica practica);
int contarPracticasEnLista (NodoPractica * lista);
int existeNombrePracticaEnLista(NodoPractica * lista, char nombrePractica []);;
NodoPractica * agregarFinalPractica (NodoPractica *lista, NodoPractica * nuevoNodo);
void editarPractica (NodoPractica * lista, int idPractica, char nuevoNombre []);
void BajaNodoPractica (int idPractica, NodoPractica * lista, NodoPxI * listaPxI);
#endif // NODOPRACTICA_H_INCLUDED
