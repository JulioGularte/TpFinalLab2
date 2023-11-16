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

NodoPractica * editarPractica (NodoPractica * lista, Practica practica, char nuevoNombre [])
{
    int existePractica=existeNombrePracticaEnArchivo(nuevoNombre);
    if (existePractica==0)
    {
        int flag=0;
        FILE * buff=fopen("archivoPractica", "r+b");
        if (buff)
        {
            Practica rg;
            while (fread(&rg, sizeof(Practica),1, buff)> 0 && flag==0)
            {
                if (strcmpi(rg.NombrePractica, nuevoNombre)==0)
                {
                    flag=1;
                    fseek(buff, -sizeof(Practica), SEEK_CUR);
                    strcpy(rg.NombrePractica, nuevoNombre);
                    fwrite(&rg, sizeof(Practica), 1, buff);
                }
            }
        }
    }
    else
    {
        printf("Ya existe una practica con ese nombre en el archivo \n");
    }
}
