#include "nodoPxi.h"
#include "NodoPractica.h"
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

NodoPxI * cargarListaPxIDesdeArchivo (NodoPxI * lista)
{
    FILE * buff=fopen(archivoPxi, "rb");
    if (buff)
    {
        PracticasXIngreso stPxI;
        while (fread(&stPxI, sizeof(PracticasXIngreso), 1, buff)>0)
        {
            lista=agregarPrincipioPxI(lista, crearNodoPxI(stPxI));
        }
        fclose(buff);
    }
    else
    {
        printf ("Error al leer desde el archivo de practicas %s", archivoPxi);
    }
    return lista;
}

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
