#include "nodoPractica.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "NodoPxI.h"
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

int contarPracticasEnLista (NodoPractica * lista)
{
    int cantidadPracticas;
    if (!lista)
    {
        cantidadPracticas=0;
    }
    else
    {
        cantidadPracticas=1+contarPracticasEnLista (lista->siguiente);
    }
    return cantidadPracticas;
}

NodoPractica * agregarFinalPractica (NodoPractica *lista, NodoPractica *nuevoNodo)
{
    int idPractica=contarPracticasEnLista(lista)+1;
    nuevoNodo->practica.nroPractica=idPractica;
    if (lista==NULL)
    {
        lista=nuevoNodo;
    }
    else
    {
        NodoPractica * seg=lista;
        while (seg->siguiente)
        {
            seg=seg->siguiente;
        }
        seg->siguiente=nuevoNodo;
    }
    return lista;
}
///Funcion que busca practica por nombre, para evitar nombres repetidos
int existeNombrePracticaEnLista(NodoPractica * lista, char nombrePractica [])
{
    int flag=0;
    if (!lista)
    {
        printf ("La lista esta vacia \n");
    }
    else
    {
        NodoPractica * seg=lista;
        while (seg && strcmpi(seg->practica.NombrePractica, nombrePractica)!=0)
        {
            seg=seg->siguiente;
        }
        ///si no me cai de la lista, entonces existe el nodo con ese nombre
        if (seg)
        {
            flag=1;
        }
    }
    return flag;
}

NodoPractica * encontrarNodoPracticaXId (NodoPractica * lista, int idPractica)
{
    NodoPractica * seg=lista;
    while (seg && seg->practica.nroPractica!=idPractica)
    {
        seg=seg->siguiente;
    }
    return seg;
}


void editarPractica (NodoPractica * lista, int idPractica, char nuevoNombre [])
{
    if (!lista)
    {
        printf ("La lista esta vacia: \n");
    }
    else
    {
        NodoPractica * nodoBuscado=encontrarNodoPracticaXId (lista, idPractica);
        if (!nodoBuscado)
        {
            printf ("No existe la practica con el Id ingresado");
        }
        else
        {
            strcpy(nodoBuscado->practica.NombrePractica, nuevoNombre);
            printf("Practica editada correctamente! \n");
            system("pause");
            system("cls");
        }
    }
}

void BajaNodoPractica (int idPractica, NodoPractica * lista, NodoPxI * listaPxI)
{
    NodoPractica * nodoBuscado=encontrarNodoPracticaXId (lista, idPractica);
    if (!nodoBuscado)
    {
        printf ("No existe la practica con el Id ingresado");
    }
    else
    {
        int flag=ExisteIngresoActivoEnPractica(listaPxI, idPractica);
        if (flag==1)
        {
            printf ("No se puede eliminar la practica, dado que existen ingresos asociados a la misma \n");
        }
        else
        {
        nodoBuscado->practica.eliminado=1;
        printf("Practica: %s eliminada \n", nodoBuscado->practica.NombrePractica);
        system("pause");
        system("cls");
        }
    }
}

void actualizarArchivo (NodoPractica * lista)
{
    FILE * buff=fopen("nombreArchivoPracticas", "wb");
    if (buff)
    {
        NodoPractica * seg=lista;
        while (seg)
        {
            Practica stPractica;
            fread(&stPractica, sizeof(Practica), 1, buff);
            seg=seg->siguiente;
        }
        fclose(buff);
    }
    else
    {
        printf ("Error al abrir el archivo de Practicas \n");
    }
}

NodoPractica * altaDePractica (NodoPractica * lista, NodoPractica * nuevo)
{
    int existeNombrePractica=existeNombrePracticaEnLista(lista, nuevo->practica.NombrePractica);
    if (existeNombrePractica==0)
    {
        lista=agregarFinalPractica(lista, nuevo);
        printf("Practica %s agregada exitosamente!", nuevo->practica.NombrePractica);
    }
    else
    {
        printf ("Ya existe una practica con el nombre %s", nuevo->practica.NombrePractica);
        system("pause");
        system("cls");
    }
    return lista;
}
