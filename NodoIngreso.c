#include "NodoIngreso.h"
#include "NodoArbolPaciente.h"
#include <stdio.h>
NodoIngresos *iniclista_ingreso()
{
    return NULL;
}


NodoIngresos *busca_ingreso_desde_Arbol(nodoArbolPaciente *arbol,int nroIngreso_Buscado)
{
    if(arbol)

    {
        Ingreso *seg;
        while(seg)
        {
            if(nroIngreso_Buscado>arbol->der->paciente.nroIngreso)
            {
                arbol=busca_ingreso_desde_Arbol(arbol->der,nroIngreso_Buscado);
            }
            else
            {
                arbol=busca_ingreso_desde_Arbol(arbol->izq,nroIngreso_Buscado);
            }
            ///corregir?
            //seg=seg->sig;
        }
    }
    return arbol ;
}

NodoIngresos *crear_nodo_lista_ingreso(Ingreso dato)
{
    NodoIngresos *nuevo=(NodoIngresos *)malloc(sizeof(NodoIngresos));
    nuevo->ingreso=dato;
    nuevo->siguiente= NULL;
    nuevo->anterior=NULL;
    return nuevo;
}

NodoIngresos *agregar_ppio(NodoIngresos *lista_Ingreso, NodoIngresos *nuevo)
{
    if(lista_Ingreso==NULL)
    {
        lista_Ingreso=nuevo;
    }
    else
    {
        nuevo->siguiente=lista_Ingreso;
        lista_Ingreso=nuevo;
    }
    return lista_Ingreso;
}

NodoIngresos *busca_Ingreso(NodoIngresos *lista_Ingreso,int nroIngresoBuscado)
{
    NodoIngresos *seg;
    NodoIngresos *buscada;
    seg=lista_Ingreso;
    while(seg)
    {
        if(seg->ingreso.NroIngreso==nroIngresoBuscado)
        {
            buscada=seg;
        }
        seg=seg->siguiente;
    }
    return buscada;
}
