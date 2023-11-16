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
NodoPractica * agregarPrincipioPractica (NodoPractica *lista, NodoPractica *nuevoNodo);
NodoPractica * agregarPracticaArchivo (NodoPractica * lista, Practica practica);
void editarPractica (NodoPractica * lista, Practica practica, char nuevoNombre []);
int existeNombrePracticaEnArchivo(char nombrePractica []);
void darDeBajaNodoPractica (int id, NodoPractica * lista);
void eliminarPractica (NodoPractica * lista, Practica practica);
#endif // NODOPRACTICA_H_INCLUDED
