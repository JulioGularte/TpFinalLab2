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

NodoIngresos * cargarListaIngreso_inicio_nodo(NodoIngresos * listaIng, NodoIngresos * nuevoNodoIngreso)
{
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
    return listaIng; ///retorno la lista sin el nodo borrado (o igual si es que no se encontro el dato buscado)
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
    NodoIngresos * aux = listaIng;
    if(aux==NULL)
    {
        puts("La lista esta vacia");
    }
    else
    {
        while(aux)
        {
            mostrarNodoIngreso(aux);
            aux=aux->siguiente;
        }
    }
}

NodoIngresos * cargarListaDeIngresosDelPaciente(nodoArbolPaciente ** nodoPaciente)
{
    FILE * archi=fopen(archivoIngresos,"rb"); ///abro el archivo de ingresos con todos los ingresos
    if (archi)
    {
        Ingreso nuevoIngreso;
        while (fread(&nuevoIngreso,sizeof(Ingreso),1,archi)>0) ///leo el archivo
        {
            if((*nodoPaciente)->paciente.DNI==nuevoIngreso.DNI) ///omparo el archivo con el dni del arbol
            {
                (*nodoPaciente)->listaIngresos=cargarListaIngreso_inicio((*nodoPaciente)->listaIngresos,nuevoIngreso); ///si el dni coincide, creo y guardo el nodo en la lista del paciente
            }
        }

        fclose(archi);
    }
    return ((*nodoPaciente)->listaIngresos); ///devuelvo esa lista actualizada
}
/*
void actualizarArchivoIngreso(NodoIngresos * ingresosDePaciente)
{
    FILE * buff=fopen(archivoIngresos, "a+b");
    if (buff)
    {
        NodoIngresos * seg=ingresosDelPaciente;
        if (seg)
        {
            while (seg)
            {
                int esActualizacion=0;
                Ingreso rg;
                fseek(buff, 0, SEEK_SET);
                while (fread(&rg, sizeof(Ingreso), 1, buff)>0 && esActualizacion==0)
                {
                    if (rg.NroIngreso==seg->ingreso.NroIngreso)
                    {
                        fseek(buff, -sizeof(Ingreso), SEEK_CUR);
                        fwrite(&rg, sizeof(Ingreso), 1, buff);
                        esActualizacion=1;
                    }
                }
                if (esActualizacion == 0)
                {
                    fwrite(&rg, sizeof(Ingreso), 1, buff);
                }
                seg=seg->siguiente;
            }
        }
    }
    fclose(buff);
}
*/
/// Recibo todos los ingresos de los pacientes y los guardo en el archivo, luego de guardar el arbol de pacientes
/// al terminar retorno los NodosPxI para su persistencia

void actualizarArchivoIngreso(NodoIngresos * ingresosDeLosPacientes, NodoPxI ** PxiDeLosPacientes)
{
    FILE * buff=fopen(archivoIngresos, "wb");
    if (buff)
    {
        NodoIngresos * seg=ingresosDeLosPacientes;
        Ingreso rg;
        if (seg)
        {
            while (seg)
            {
                NodoPxI * segPxI=seg->listaPxI;
                while (segPxI)
                {
                    printf("Nro Practica: %d \n", segPxI->PxI.nroPractica);
                    printf("Nro Ingreso: %d \n", segPxI->PxI.nroIngreso);
                    printf("Resultado: %s \n", segPxI->PxI.resultado);
                    (*PxiDeLosPacientes)=agregarPrincipioPxI((*PxiDeLosPacientes), crearNodoPxI(segPxI->PxI));
                    segPxI=segPxI->siguiente;

                }
                fwrite(&seg->ingreso, sizeof(Ingreso), 1, buff);
                seg=seg->siguiente;
            }
            system("pause");
        }
        fclose(buff);
    }
    return PxiDeLosPacientes;
}

void BajaDeIngresos (NodoIngresos * ingresosDelPaciente)
{
    mostrarListaIngresos(ingresosDelPaciente);
    NodoIngresos * buscado=NULL;
    int nroIngreso;
    do
    {
        printf ("Seleccione el nro de ingreso que desea dar de baja \n");
        scanf("%d",&nroIngreso);
        buscado=buscarNodoIngresoPorNroIngreso(ingresosDelPaciente, nroIngreso);
        if (!buscado)
        {
            printf ("Numero de ingreso inexsitante \n");
            system("pause");
            system("cls");
        }
    }
    while(!buscado);
    buscado->ingreso.Eliminado=1;
    NodoPxI * PxIBuscado=buscado->listaPxI;
    NodoPxI * seg=PxIBuscado;
    while(seg)
    {
        seg->PxI.eliminado=1;
        seg=seg->siguiente;
    }
    printf ("Ingreso %d y sus practicas dadas de baja exitosamente \n", nroIngreso);
}
