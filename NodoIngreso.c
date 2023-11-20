#include "NodoIngreso.h"
#include "NodoArbolPaciente.h"
#include "NodoPxI.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

NodoIngresos * inicListaI()
{
    return NULL;
}

NodoIngresos * crearNodoI(Ingreso datoIngreso)
{
    NodoIngresos * nuevoNodoI=(NodoIngresos*) malloc (sizeof(NodoIngresos));
    nuevoNodoI->ingreso=datoIngreso;
    nuevoNodoI->listaPxI=inicListaPxI();
    nuevoNodoI->anterior=NULL;
    nuevoNodoI->siguiente=NULL;

    return nuevoNodoI;

}

NodoIngresos * cargarListaIngreso_inicio(NodoIngresos * listaIng, Ingreso datoIngreso)
{
    NodoIngresos* nuevoNodoIngreso=crearNodoI(datoIngreso);
    if(listaIng==NULL)
    {
        listaIng=nuevoNodoIngreso;
    }
    else
    {
        nuevoNodoIngreso->siguiente=listaIng;
        listaIng->anterior=nuevoNodoIngreso;
        listaIng=nuevoNodoIngreso;
    }
    return listaIng;
}


NodoIngresos * buscarNodoIngresoPorNroIngreso(NodoIngresos * listaIng, int nroIngresoBuscado)
{
    NodoIngresos * aux=listaIng;     ///apunto un nodo auxiliar a la lista para recorrerla
    NodoIngresos * nodoBuscado=NULL;  ///creo una variable para guardar el nodo que estoy buscando
    int flag=0;                     ///flag para dejar de  recorrer la lista
    while((aux!=NULL) && flag==0) ///recorro la lista hasta que llegue al final o encuentre el nodo
    {
        if(aux->ingreso.NroIngreso==nroIngresoBuscado) ///debe coincidir el nro de ingreso
        {
            nodoBuscado=aux;        ///guardo el nodo buscado
            flag=1;                 ///cambio la variable para dejar de buscar en la lista
        }
        aux=aux->siguiente;            /// recorro la lista
    }

    return nodoBuscado;     ///retorno el nodo buscado
}
NodoIngresos * buscarNodoIngresoPorNroDNI(NodoIngresos * listaIng, int DNI)
{
    NodoIngresos * aux=listaIng;     ///apunto un nodo auxiliar a la lista para recorrerla
    NodoIngresos * nodoBuscado=NULL;  ///creo una variable para guardar el nodo que estoy buscando
    int flag=0;                     ///flag para dejar de  recorrer la lista
    while((aux!=NULL) && flag==0) ///recorro la lista hasta que llegue al final o encuentre el nodo
    {
        if(aux->ingreso.NroIngreso==DNI) ///debe coincidir el nro de ingreso
        {
            nodoBuscado=aux;        ///guardo el nodo buscado
            flag=1;                 ///cambio la variable para dejar de buscar en la lista
        }
        aux=aux->siguiente;            /// recorro la lista
    }

    return nodoBuscado;     ///retorno el nodo buscado
}
NodoIngresos * eliminarNodoIngPorNroIngreso(NodoIngresos * listaIng, int nroIngresoBuscado)
{
    NodoIngresos * nodoIngAEliminar=buscarNodoIngresoPorNroIngreso(listaIng,nroIngresoBuscado); ///cargo el nodo a eliminar en una variable
    if (nodoIngAEliminar!=NULL) ///si hay algo para eliminar, ingreso a la condicion
    {
        nodoIngAEliminar->ingreso.Eliminado=1;
    }
    return listaIng; ///retorno la lista con el nodo modificado(o igual si es que no se encontro el dato buscado)

}
NodoIngresos * eliminarNodoIngPorDNI(NodoIngresos * listaIng, int DNI)
{
    NodoIngresos * nodoIngAEliminar=buscarNodoIngresoPorNroDNI(listaIng,DNI); ///cargo el nodo a eliminar en una variable
    if (nodoIngAEliminar!=NULL) ///si hay algo para eliminar, ingreso a la condicion
    {
        nodoIngAEliminar->ingreso.Eliminado=1;
    }
    return listaIng; ///retorno la lista con el nodo modificado(o igual si es que no se encontro el dato buscado)

}
void mostrarNodoIngreso(NodoIngresos * nodoAMostrar)
{

    printf("El numero de ingreso es:......................... %d\n",nodoAMostrar->ingreso.NroIngreso);
    printf("La fecha de ingreso es:.......................... %s\n",nodoAMostrar->ingreso.FechaIngreso);
    printf("La fecha de ingreso es:.......................... %s\n",nodoAMostrar->ingreso.FechaRetiro);
    printf("El numero de DNI del paciente es:................ %d\n",nodoAMostrar->ingreso.DNI);
    printf("La matricula del medico solicitante es:.......... %d\n",nodoAMostrar->ingreso.MatriculaPersonalSolicitante);
    if(nodoAMostrar->ingreso.Eliminado==1)
    {
        puts("El ingreso esta dado de baja");
    }
    else
    {
        puts("El ingreso esta activo");
    }
    puts("===========================================================================");

}

void mostrarListaIngresos(NodoIngresos* listaIng)
{
    NodoIngresos * aux=listaIng;
    if(aux==NULL)
    {
        puts("La lista está vacia");
    }
    else
    {
    while(aux->siguiente!=NULL)
        {
        mostrarNodoIngreso(aux);
        aux=aux->siguiente;
        }
    }
}

NodoIngresos * leerArchivoYCargarLista(char archivoIngreso[], NodoIngresos * listaIngresos)
{
FILE * archi=fopen(archivoIngreso,"rb");
if (archi)
    {
    Ingreso nuevoIngreso;
while (fread(&nuevoIngreso,sizeof(Ingreso),1,archi)>0)
    {
    listaIngresos=cargarListaIngreso_inicio(listaIngresos,nuevoIngreso);

    }
    fclose(archi);
    }
return listaIngresos;
}
