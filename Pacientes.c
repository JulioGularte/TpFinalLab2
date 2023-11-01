#include "NodoArbolPaciente.h"
#include <stdio.h>
nodoArbolPaciente *inicArbol()
{
    return NULL;
}

nodoArbolPaciente *crear_nodo_arbol(Paciente dato)
{
    nodoArbolPaciente *nuevo=(nodoArbolPaciente *)(sizeof(nodoArbolPaciente));
    nuevo->paciente=dato;
    nuevo->der=NULL;
    nuevo->izq=NULL;
    nuevo->listaIngresos=NULL;//cabecera lista
    return nuevo;
}

nodoArbolPaciente *busca_nodoArbolPaciente(nodoArbolPaciente *arbol, Paciente dato)
{
    nodoArbolPaciente *rta=inicArbol();
    if(arbol)
    {
        if(arbol->paciente.DNI==arbol->paciente.DNI)
        {
            rta=arbol;
        }
        else
        {
            if(dato.DNI > arbol->paciente.DNI)
            {
                rta=busca_nodoArbolPaciente(arbol->der,dato);
            }
            else
            {
                rta=busca_nodoArbolPaciente(arbol->izq,dato);
            }
        }
    }
    return rta;
}

nodoArbolPaciente *insertar_nodoArbolPaciente(nodoArbolPaciente *arbol, Paciente dato)
{
    if(arbol==NULL)
    {
        nodoArbolPaciente *nuevo=crear_nodo_arbol(dato);
        nuevo->listaIngresos=iniclista_ingreso();
    }
    else
    {
        if(dato.DNI>arbol->paciente.DNI)
        {
            arbol=insertar_nodoArbolPaciente(arbol->der,dato);
        }
        else
        {
            arbol=insertar_nodoArbolPaciente(arbol->izq,dato);
        }
    }
    return arbol;
}
