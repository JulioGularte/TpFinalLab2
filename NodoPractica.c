#include "nodoPractica.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
NodoPractica * inicListaPractica ()
{
    return NULL;
}

NodoPractica * crearNodoPractica (Practica practica)
{
    NodoPractica * nuevo=(NodoPractica*) malloc(sizeof(NodoPractica));
    nuevo->practica = practica;
    nuevo->siguiente = NULL;
    return nuevo;
}

NodoPractica * agregarPrincipioPractica (NodoPractica *lista, NodoPractica *nuevoNodo)
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
//eliminar, agregar al final de la lista
NodoPractica * agregarPracticaArchivo (NodoPractica * lista, Practica practica)
{
    FILE * buff=fopen("archivoPractica", "ab");
    if (buff)
    {
        int flag=existeNombrePracticaEnArchivo(practica.NombrePractica);
        if (flag==0)
        {
            fwrite(&practica, sizeof(practica), 1, buff);
            lista=agregarPrincipioPractica(lista, crearNodoPractica(practica));
        }
        else
        {
            printf ("Ya existe una practica con el nombre %s", practica.NombrePractica);
        }
    }
    else
    {
        printf ("Error al abrir el archivo de practicas \n");
    }
    return lista;
}
//refactor a buscar en lista
int existeNombrePracticaEnArchivo(char nombrePractica [])
{
    FILE * buff=fopen("archivoPractica", "ab");
    int flag=0;
    if (buff)
    {
        Practica rg;
        while (fread(&rg, sizeof(Practica),1, buff) > 0 && flag==0)
        {
            if (strcmpi(nombrePractica, rg.NombrePractica)==0)
            {
                flag=1;
            }
        }
    }
    else
    {
        printf ("Error al abrir el archivo de practicas \n");
    }
    return flag;
}

void editarPractica (NodoPractica * lista, Practica practica, char nuevoNombre [])
{
    if (!lista)
    {
        printf ("La lista esta vacia: \n");
    }
    else
    {
        NodoPractica * seg=lista;
        while (seg && seg->practica.nroPractica!=practica.nroPractica)
        {
            seg=seg->siguiente;
        }
        if (seg)
        {
            strcpy(seg->practica.NombrePractica, nuevoNombre);
        }
    }
}

void BajaNodoPractica (int id, NodoPractica * lista)
{
    NodoPractica * seg=lista;
    while (seg && seg->practica.nroPractica!=id)
    {
        seg=seg->siguiente;
    }
    if (seg)
    {
        seg->practica.eliminado=1;
    }
}
