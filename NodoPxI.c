#include "nodoPxi.h"
#include <stdio.h>
#include <stdlib.h>
NodoPxI * inicListaPxI ()
{
    return NULL;
}

NodoPxI * crearNodoPxI (PracticasXIngreso pxi)
{
    NodoPxI * nuevo=(NodoPxI*) malloc(sizeof(NodoPxI));
    nuevo->PxI = pxi;
    nuevo->siguiente = NULL;
    return nuevo;
}
///TODO: CAMBIAR A AGREGAR AL FINAL
NodoPxI * agregarPrincipioPxI (NodoPxI * lista, NodoPxI * nuevoNodo)
{
    if (lista==NULL)
    {
        lista=nuevoNodo;
    }
    else
    {
        nuevoNodo->siguiente=lista;
        lista=nuevoNodo;
    }
    return lista;
}
///funcion que determina si una practica existe en un ingreso (activo)
int ExisteIngresoActivoEnPractica (NodoPxI * lista, int PracticaId)
{
    NodoPxI * seg=lista;
    int flag=0;
    while (seg && flag==0)
    {
        if (seg->PxI.eliminado==0 && seg->PxI.nroPractica==PracticaId)
        {
            flag=1;
        }
        seg=seg->siguiente;
    }
    return flag;
}
