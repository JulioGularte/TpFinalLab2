#include "NodoIngreso.h"
#include "NodoArbolPaciente.h"
#include "NodoPxI.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

NodoIngresos * inicListaI()
{
    return NULL;
}

NodoIngresos * crearNodoI(Ingreso datoIngreso)
{
    NodoIngresos * nuevoNodoI=(NodoIngresos*) malloc (sizeof(NodoIngresos));
    nuevoNodoI->ingreso=datoIngreso;
    nuevoNodoI->practicasIngreso=inicListaPxI();
    nuevoNodoI->anterior=NULL;
    nuevoNodoI->siguiente=NULL;

    return nuevoNodoI;

}

NodoIngresos * cargarListaIngreso_inicio(NodoIngresos * listaIng, Ingreso datoIngreso)
{
    NodoIngresos* nuevoNodoIngreso=crearNodoI(datoIngreso);
    if(listaIng==NULL)
    {
        listaIng=nuevoNodoIngreso;
    }
    else
    {
        nuevoNodoIngreso->siguiente=listaIng;
        listaIng->anterior=nuevoNodoIngreso;
        listaIng=nuevoNodoIngreso;
    }
    return listaIng;
}


NodoIngresos * buscarNodoIngreso(NodoIngresos * listaIng, Ingreso datoIngreso)
{
    NodoIngresos * aux=listaIng;     ///apunto un nodo auxiliar a la lista para recorrerla
    NodoIngresos * nodoBuscado=NULL;  ///creo una variable para guardar el nodo que estoy buscando
    int flag=0;                     ///flag para dejar de  recorrer la lista
    while((aux!=NULL) && flag==0) ///recorro la lista hasta que llegue al final o encuentre el nodo
    {
        if(aux->ingreso.NroIngreso==datoIngreso.NroIngreso) ///debe coincidir el nro de ingreso
        {
            nodoBuscado=aux;        ///guardo el nodo buscado
            flag=1;                 ///cambio la variable para dejar de buscar en la lista
        }
        aux=aux->siguiente;            /// recorro la lista
    }

    return nodoBuscado;     ///retorno el nodo buscado
}

NodoIngresos * eliminarNodoIng(NodoIngresos * listaIng, Ingreso datoIngreso)
{
    NodoIngresos * nodoIngAEliminar=buscarNodoIngreso(listaIng,datoIngreso); ///cargo el nodo a eliminar en una variable
    if (nodoIngAEliminar!=NULL) ///si hay algo para eliminar, ingreso a la condicion
    {
       nodoIngAEliminar->ingreso.Eliminado=1;
    }
return listaIng; ///retorno la lista sin el nodo borrado (o igual si es que no se encontro el dato buscado)

}
