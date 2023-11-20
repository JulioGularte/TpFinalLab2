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

///funcion para guardar las Practica por ingreso del paciente
void guardarPracticasXIngresoDelPacienteEnArchivo (NodoIngresos * listaDeIngresosPaciente)
{
    FILE * buff=fopen(archivoPxi, "r+b");
    if (buff)
    {
        PracticasXIngreso rg;
        NodoIngresos * segIngreso=listaDeIngresosPaciente;
        int registrosLeidos=0;
        while (segIngreso) ///recorro la lista de ingresos para guardar las pxi en el archivo
        {
            NodoPxI * PxIEncontrada=NULL; ///nodo auxiliar
            while (fread(&rg, sizeof(PracticasXIngreso),1, buff)>0) ///recorro el archivo buscando el PxI
            {
                registrosLeidos++; ///contador de posicion para retomar la ultima posicion por si tengo que ir al final del archivo y agregar
                NodoPxI * segPxI=segIngreso->listaPxI;
                while (segPxI) ///recorro la lista de practicas por ingreso
                {
                    if (segPxI->PxI.nroIngreso==rg.nroIngreso && segPxI->PxI.nroPractica==rg.nroPractica) ///si la practica existe en el archivo la actualizo
                    {
                        PxIEncontrada=segPxI;
                        fseek(buff, -sizeof(PracticasXIngreso), SEEK_CUR); ///me paro en la posicion del archivo para actualizar
                        fwrite(&segPxI->PxI, sizeof(PracticasXIngreso), 1, buff); ///grabo en el archivo
                    }

                    segPxI=segPxI->siguiente;

                    if (!PxIEncontrada) ///si no hay coincidencias agrego al final del archivo
                    {
                        fseek(buff, 0, SEEK_END);
                        fwrite(&segPxI->PxI, sizeof(PracticasXIngreso), 1, buff);
                        fseek(buff, registrosLeidos*sizeof(PracticasXIngreso), SEEK_SET); ///retorno a la posicion del ultimo registro leido
                        PxIEncontrada=NULL;
                    }
                }
            }
            segIngreso=segIngreso->siguiente;
        }
    }
}

