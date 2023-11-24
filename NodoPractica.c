#include "nodoPractica.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "NodoPxI.h"
#define archivoPracticas "archivo_practicas.bin"
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

NodoPractica * agregarPracticaEnOrden(NodoPractica *lista, NodoPractica *nuevoNodo)
{
    int idPractica = contarPracticasEnLista(lista) + 1;
    nuevoNodo->practica.nroPractica = idPractica;
    if (!lista)
    {
        lista = nuevoNodo;
    }
    else
    {
        if (strcmp(nuevoNodo->practica.NombrePractica, lista->practica.NombrePractica) < 0)
        {
            nuevoNodo->siguiente = lista;
            lista = nuevoNodo;
        }
        else
        {
            NodoPractica *anterior = lista;
            NodoPractica *actual = lista->siguiente;
            while (actual && strcmp(nuevoNodo->practica.NombrePractica, actual->practica.NombrePractica) > 0)
            {
                anterior = actual;
                actual = actual->siguiente;
            }
            nuevoNodo->siguiente = actual;
            anterior->siguiente = nuevoNodo;
        }
    }
    return lista;
}

int existeNombrePracticaEnLista(NodoPractica * lista, char nombrePractica [])
{
    int flag=0;
    if (lista)
    {
        NodoPractica * seg=lista;
        while (seg && flag==0)
        {
            if (strcmpi(seg->practica.NombrePractica, nombrePractica)==0)
            {
                flag=1;
            }
            seg=seg->siguiente;
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
        else if (nodoBuscado->practica.eliminado==1)
        {
            printf ("La practica esta eliminada \n");
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

void actualizarArchivoPracticas (NodoPractica ** lista)
{
    FILE * buff=fopen(archivoPracticas, "wb");
    if (buff)
    {
        NodoPractica * seg=lista;
        while (seg)
        {
            Practica stPractica=seg->practica;
            fwrite(&stPractica, sizeof(Practica), 1, buff);
            seg=seg->siguiente;
        }
        fclose(buff);
    }
}

NodoPractica * altaDePractica (NodoPractica * lista, NodoPractica * nuevo)
{
    int existeNombrePractica=existeNombrePracticaEnLista(lista, nuevo->practica.NombrePractica);
    if (existeNombrePractica==0)
    {
        lista=agregarPracticaEnOrden(lista, nuevo);
        printf("Practica %s agregada exitosamente! \n", nuevo->practica.NombrePractica);
    }
    else
    {
        printf ("Ya existe una practica con el nombre %s \n", nuevo->practica.NombrePractica);
    }
    return lista;
}

void mostrarListaPracticas (NodoPractica * lista, int esAdmin, int mostrarInactivas)
{
    if (!lista)
    {
        printf ("\n\tLa lista de practicas esta vacia \n");
    }
    else
    {
        NodoPractica * seg=lista;
        while (seg)
        {
            if ((seg->practica.eliminado==1 && mostrarInactivas == 1) || seg->practica.eliminado==0)
            {
            mostrarUnaPractica(seg->practica, esAdmin);
            printf ("=================================================== \n");
            }
            seg=seg->siguiente;
        }
    }
}

NodoPractica * cargarListaPracticaDesdeArchivo (NodoPractica * lista)
{
    FILE * buff=fopen(archivoPracticas, "rb");
    if (buff)
    {
        Practica rg;
        while (fread(&rg, sizeof(Practica), 1, buff)>0)
        {
            lista=agregarPracticaEnOrden(lista, crearNodoPractica(rg));
        }
        fclose(buff);
    }
    else
    {
        printf ("Error al leer desde el archivo de practicas %s", archivoPracticas);
    }
    return lista;
}

NodoPractica * filtrarPracticasPorIniciales(NodoPractica *lista, char nombre[])
{

    NodoPractica *listaFiltrada = inicListaPractica();
    if (lista) {
        int longitudCadenaBusqueda = strlen(nombre);
        NodoPractica *seg = lista;
        while (seg) {
            // Comparo las iniciales y la cantidad de caracteres a buscar
            if (strncmp(nombre, seg->practica.NombrePractica, longitudCadenaBusqueda) == 0) {
                listaFiltrada=agregarPracticaEnOrden(listaFiltrada, crearNodoPractica(seg->practica));
            }
            seg = seg->siguiente;
        }
    }
    return listaFiltrada;
}
