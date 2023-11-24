#include "nodoPxi.h"
#include "NodoPractica.h"
#include "NodoIngreso.h"
#include <stdio.h>
#include <stdlib.h>
#define archivoPxi "archivo_pxi.bin"

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
///funcion que determina si una practica existe en un ingreso (activo) para eliminacion en cascada
int ExisteIngresoActivoEnPractica (nodoArbolPaciente * arbol, int PracticaId)
{
    int existeIngresoEnPractica=0;
    if (arbol && existeIngresoEnPractica==0)
    {
        existeIngresoEnPractica=ExisteIngresoActivoEnPractica(arbol->izq, PracticaId);
        NodoIngresos * ingresosPaciente=arbol->listaIngresos;
        while (ingresosPaciente && existeIngresoEnPractica)
        {
            NodoPxI * segPxi=ingresosPaciente->listaPxI;
            while (segPxi && existeIngresoEnPractica==0)
            {
                if (segPxi->PxI.nroPractica==PracticaId && existeIngresoEnPractica==0)
                {
                    existeIngresoEnPractica=1;
                }
                segPxi=segPxi->siguiente;
            }
            ingresosPaciente=ingresosPaciente->siguiente;
        }
        existeIngresoEnPractica=ExisteIngresoActivoEnPractica(arbol->der, PracticaId);
    }
    return existeIngresoEnPractica;
}
/*
void actualizarArchivoPxI (NodoPxI * lista)
{
    FILE * buff=fopen(archivoPxi, "wb");
    if (buff)
    {
        NodoPxI * seg=lista;
        while (seg)
        {
            PracticasXIngreso stPxI=seg->PxI;;
            fwrite(&stPxI, sizeof(PracticasXIngreso), 1, buff);
            seg=seg->siguiente;
        }
        fclose(buff);
    }
}
*/
NodoPxI * cargarListaPxIDesdeArchivo (int nroIngreso)
{
    FILE * buff=fopen(archivoPxi, "rb");
    PracticasXIngreso stPxI;
    NodoPxI * listaPxiPaciente=inicListaPxI();
    if (buff)
    {
        while (fread(&stPxI, sizeof(PracticasXIngreso), 1, buff)>0)
        {
            if (stPxI.nroIngreso == nroIngreso)
            {
                if (nroIngreso == 1)
                {
                    printf ("");
                }
                listaPxiPaciente=agregarPrincipioPxI(listaPxiPaciente, crearNodoPxI(stPxI));
            }
        }
        fclose(buff);
    }
    return listaPxiPaciente;
}
/*
void verPracticasPorIngreso (NodoPxI * listaPxI, NodoPractica * listaPracticas, NodoIngresos * listaIngresos)
{
    if (!listaPxI)
    {
        printf ("La lista de practicas x ingreso esta vacia \n");
    }
    else
    {
        NodoPxI * segPxI=listaPxI;
        while (segPxI)
        {
            NodoPractica * buscado=encontrarNodoPracticaXId(listaPracticas, segPxI->PxI.nroIngreso);
            mostrarUnaPractica(buscado.practica, 1);

        }
    }
}
*/

void bajaPxICascada (NodoPxI * listaPxI, Ingreso ingresoActualizado)
{
    if (listaPxI)
    {
        NodoPxI * seg=listaPxI;
        while (seg)
        {
            if (seg->PxI.nroIngreso==ingresoActualizado.NroIngreso)
            {
                seg->PxI.eliminado=1;
            }
            seg=seg->siguiente;
        }
    }
}

int existePxIEnIngreso (NodoPxI * listaPxI, NodoPxI * nuevo)
{
    int existe=0;
    if (listaPxI)
    {
        NodoPxI * seg=listaPxI;
        while (seg && existe==0)
        {
            if ((seg->PxI.nroIngreso && seg->PxI.nroIngreso)
                && seg->PxI.nroPractica && seg->PxI.nroPractica)
            {
                existe=1;
            }
            seg=seg->siguiente;
        }
    }
    return existe;
}

void AltaDePracticaPxI (NodoPxI * listaPxI, nodoArbolPaciente * paciente, NodoPractica * listaDePracticas)
{
    mostrarListaIngresos(paciente->listaIngresos);
    NodoIngresos * buscado=NULL;
    NodoPractica * buscada=NULL;
    do
    {
    printf("Ingrese el numero de ingreso en el que desea cargar la practica: \n");
    int nroIngresoBuscado;
    scanf("%d",&nroIngresoBuscado);
    buscado=buscarNodoIngresoPorNroIngreso(paciente->listaIngresos, nroIngresoBuscado);
    }while (!buscado);
    do
    {
    printf("Ingrese el nro de practica que desea cargar: \n");
    int nroPracticaBuscada;
    scanf("%d",&nroPracticaBuscada);
    buscada=encontrarNodoPracticaXId(listaDePracticas, nroPracticaBuscada);
    }while(!buscada);
    NodoIngresos * nodoIngresoDelPaciente=paciente->listaIngresos;
    nodoIngresoDelPaciente->listaPxI=agregarPrincipioPxI(nodoIngresoDelPaciente->listaPxI, crearNodoPxI(crearPxI(nodoIngresoDelPaciente->ingreso.NroIngreso, buscada->practica.nroPractica)));
    listaPxI=agregarPrincipioPxI(listaPxI, crearNodoPxI(crearPxI(nodoIngresoDelPaciente->ingreso.NroIngreso, buscada->practica.nroPractica)));
    printf("Practica agregada exitosamente \n");
    system("pause");
}

void guardarPxIEnArchivo (NodoPxI * PxIDeLosPacientes)
{
    FILE * buff=fopen(archivoPxi, "wb");
    if (buff)
    {
        PracticasXIngreso rg;
        NodoPxI * seg =PxIDeLosPacientes;
        while (seg)
        {
            fwrite(&seg->PxI, sizeof(PracticasXIngreso), 1, buff);
            seg=seg->siguiente;
        }
        fclose(buff);
    }
}

NodoPxI * obtenerPxI (NodoIngresos * ingreso , int nroPractica)
{
    NodoPxI * pxi=NULL;
    int encontrado=0;
    if (ingreso)
    {
        if (!ingreso->listaPxI)
        {
            printf ("NULL \n");
        }
        NodoPxI * seg=ingreso->listaPxI;
        while (seg)
        {
            if ((seg->PxI.nroPractica==nroPractica) && (seg->PxI.nroIngreso==ingreso->ingreso.NroIngreso))
            {
                encontrado=1;
                pxi=seg;
            }
            seg=seg->siguiente;
        }
    }
    if (encontrado==0)
    {
        printf ("No existe la practica por ingreso ingresada \n");
    }
    return pxi;
}
