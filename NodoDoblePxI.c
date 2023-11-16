#include "NodoDoblePxI.h"
#include <stdio.h>
#include <stdlib.h>
NodoDoblePxI * inicListaDoblePxI (NodoDoblePxI * lista)
{
    return NULL;
}

NodoDoblePxI * crearNodoDoblePxI (PracticaXIngreso practica)
{
    NodoDoblePxI * nuevo=(NodoDoblePxI *) malloc(sizeof(NodoDoblePxI));
    nuevo->practica=practica;
    nuevo->siguiente=NULL;
    nuevo->anterior=NULL;
    return nuevo;
}

NodoDoblePxI * agregarPpioDoblePxI (NodoDoblePxI * lista, NodoDoblePxI * nuevoNodo)
{
    if (!lista)
    {
        lista=nuevoNodo;
    }
    else
    {
        nuevoNodo->siguiente=lista;
        lista->anterior=nuevoNodo;
        lista=nuevoNodo;
    }
    return lista;
}


///deben actualizarse encascada (dar de baja), las practicas asociadas al ingreso
///TODO: agregar el parametro de la lista de ingresos para hacer la baja de ese nodo
void bajaDeIngreso (NodoDoblePxI * lista, int idIngreso)
{
    FILE * buff=fopen("archivoPxI", "rb");
    PracticaXIngreso rgPxI;
    int flag=0;
    if (buff)
    {
        while (fread(&rgPxI, sizeof(PracticaXIngreso), 1, buff)>0)
        {
            if (rgPxI.nroIngreso==idIngreso)
            {
                flag=1;
                fseek(buff, -sizeof(PracticaXIngreso), SEEK_CUR);
                rgPxI.eliminado=1;
                fwrite(&rgPxI, sizeof(PracticaXIngreso),1, buff);
            }
        }
        if (flag)
        {
            bajaDePxIEnCascadaLista(lista, rgPxI.nroIngreso);
            ///TODO: baja de ingreso en archivo
        }
        else
        {
            printf("No existe el ingreso solicitado \n");
        }
        fclose(buff);
    }
    else
    {
        printf("Error al abrir el archivo de ingresos \n");
    }
}

void bajaDePxIEnCascadaLista (NodoDoblePxI * lista, int nroIngreso)
{
    if (!lista)
    {
        printf ("La lista de nodos de practicas x ingreso esta vacia \n");
    }
    else
    {
        NodoDoblePxI * seg=lista;
        while (seg)
        {
            if (seg->practica.nroIngreso==nroIngreso)
            {
                seg->practica.eliminado=1;
            }
            seg=seg->siguiente;
        }
    }
}
