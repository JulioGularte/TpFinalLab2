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
int existeNombrePracticaEnLista(NodoPractica * lista, char nombrePractica []);
NodoPractica * agregarPracticaEnOrden (NodoPractica *lista, NodoPractica *nuevoNodo);
void editarPractica (NodoPractica * lista, int idPractica, char nuevoNombre []);
void mostrarListaPracticas (NodoPractica * lista, int esAdmin, int mostrarInactivas);
NodoPractica * altaDePractica (NodoPractica * lista, NodoPractica * nuevo);
NodoPractica * cargarListaPracticaDesdeArchivo (NodoPractica * lista);
void actualizarArchivoPracticas (NodoPractica ** lista);
#endif // NODOPRACTICA_H_INCLUDED
