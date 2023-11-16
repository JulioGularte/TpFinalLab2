#include "NodoIngreso.h"
#include "NodoArbolPaciente.h"
#include "NodoPxI.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

NodoPxI * inicListaPxI()
{
    return NULL;
}

NodoPxI * crearNodoPxI(PracticasXIngreso datoPxI)
{
    NodoPxI * nuevoNodoPxI=(NodoPxI*) malloc (sizeof(NodoPxI));
    nuevoNodoPxI->PxI=datoPxI;
    nuevoNodoPxI->anterior=NULL;
    nuevoNodoPxI->siguiente=NULL;

    return nuevoNodoPxI;

}

NodoPxI * cargarListaPxI_inicio(NodoPxI * listaPxI, PracticasXIngreso datoPxI)
{
    NodoPxI* nuevoNodoPxI=crearNodoPxI(datoPxI);
    if(listaPxI==NULL)
    {
        listaPxI=nuevoNodoPxI;
    }
    else
    {
        nuevoNodoPxI->siguiente=listaPxI;
        listaPxI->anterior=nuevoNodoPxI;
        listaPxI=nuevoNodoPxI;
    }
    return listaPxI;
}


NodoPxI * buscarNodoPxI(NodoPxI * listaPxI, PracticasXIngreso datoPxI)
{
    NodoPxI * aux=listaPxI;     ///apunto un nodo auxiliar a la lista para recorrerla
    NodoPxI * nodoBuscado=NULL;  ///creo una variable para guardar el nodo que estoy buscando
    int flag=0;                     ///flag para dejar de  recorrer la lista
    while((aux!=NULL) && flag==0) ///recorro la lista hasta que llegue al final o encuentre el nodo
    {
        if((aux->PxI.nroIngreso==datoPxI.nroIngreso) && (aux->PxI.nroPractica==datoPxI.nroPractica) ) ///debe coincidir el nro de ingreso y el nro de practica a la vez
        {
            nodoBuscado=aux;        ///guardo el nodo buscado
            flag=1;                 ///cambio la variable para dejar de buscar en la lista
        }
        aux=aux->siguiente;            /// recorro la lista
    }

    return nodoBuscado;     ///retorno el nodo buscado
}

NodoPxI * eliminarNodoPxI(NodoPxI * listaPxI, PracticasXIngreso datoPxI) ///lo elimina completamente, ya que no tiene un int eliminado para cambiar
{
    NodoPxI * nodoAEliminar=buscarNodoPxI(listaPxI,datoPxI); ///cargo el nodo a eliminar en una variable
    NodoPxI * ante=nodoAEliminar->anterior;
    NodoPxI * seg=nodoAEliminar->siguiente;
    if (nodoAEliminar!=NULL) ///si hay algo para eliminar, ingreso a la condicion
    {
        if (ante==NULL) ///caso en que el nodo a eliminar es el primero de la lista
        {
            listaPxI=listaPxI->siguiente;
            listaPxI->anterior=NULL;
            free(nodoAEliminar);
        }
        else        ///es un nodo del medio o el ultimo
        {
            if(seg==NULL) ///caso en que sea el ultimo nodo
            {

                ante->siguiente=NULL;
                free(nodoAEliminar);

            }
            else    ///caso que sea un nodo intermedio
            {

                ante->siguiente=nodoAEliminar->siguiente;
                seg->anterior=ante;
                free(nodoAEliminar);
            }
        }

    }
return listaPxI; ///retorno la lista sin el nodo borrado (o igual si es que no se encontro el dato buscado)

}

