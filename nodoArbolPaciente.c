#include "NodoIngreso.h"
#include "NodoArbolPaciente.h"
#include "NodoPxI.h"
#include "Ingreso.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define PAUSA system("pause");
#define BORRAR system("cls");

nodoArbolPaciente *inicArbol()
{
    return NULL;
}


nodoArbolPaciente * crearNodoArbol(Paciente nuevoPaciente)
{
    nodoArbolPaciente * nuevoNodo=(nodoArbolPaciente* )malloc(sizeof(nodoArbolPaciente));
    nuevoNodo->paciente=nuevoPaciente;
    nuevoNodo->der=NULL;
    nuevoNodo->izq=NULL;
    nuevoNodo->listaIngresos= inicListaI();

}

nodoArbolPaciente * cargarArbolOrdenadoDNI(nodoArbolPaciente * arbolPacientes, nodoArbolPaciente * nodoACargar)
{
    nodoArbolPaciente * aux=arbolPacientes;
    if(aux==NULL)
    {
        arbolPacientes=nodoACargar;
    }
    else
    {
        if (aux->paciente.DNI==nodoACargar->paciente.DNI)
        {
            puts("El numero de DNI ya se encuentra en el sistema.");
        }
        else
        {
            if(aux->paciente.DNI<nodoACargar->paciente.DNI)
            {
                aux->der=cargarArbolOrdenadoDNI(aux->der,nodoACargar);
            }
            else
            {
                aux->izq=cargarArbolOrdenadoDNI(aux->izq,nodoACargar);
            }
        }
    }
    return arbolPacientes;
}

nodoArbolPaciente * cargarArbolDesdeArchi(char archivoPacientes[], nodoArbolPaciente * arbolPacientes)
{
    FILE * archi=fopen(archivoPacientes,"rb");
    if(archi)
    {
        Paciente nuevoPaciente;
        while(fread(&nuevoPaciente,sizeof(Paciente),1,archi)>0)
        {
            nodoArbolPaciente * nodoAcargar=crearNodoArbol(nuevoPaciente);
            arbolPacientes=cargarArbolOrdenadoDNI(arbolPacientes,nodoAcargar);
        }
        fclose(archi);
    }

    return arbolPacientes;
}




void mostrarNodoArbol(nodoArbolPaciente * nodoAMostrar)
{

    printf("Numero de DNI:...................................... %d\n",nodoAMostrar->paciente.DNI);
    printf("Nombre y apellido:.................................. %s\n",nodoAMostrar->paciente.NyA);
    printf("Edad:............................................... %d\n",nodoAMostrar->paciente.edad);
    printf("Direccion:.......................................... %s\n",nodoAMostrar->paciente.direccion);
    printf("Telefono:........................................... %s\n",nodoAMostrar->paciente.telefono);
    printf("Paciente eliminado:................................. %d\n",nodoAMostrar->paciente.eliminado);
    puts("===========================================================================");

}

void mostrarArbolPacientes(nodoArbolPaciente * arbolPacientes)
{

    nodoArbolPaciente * aux=arbolPacientes;
    if(aux!=NULL)
    {
        mostrarArbolPacientes(aux->izq);
        mostrarNodoArbol(aux);
        mostrarArbolPacientes(aux->der);


    }
}

nodoArbolPaciente * buscarXDni (nodoArbolPaciente * arbol, int dni)
{
    nodoArbolPaciente * nodoBusqueda=NULL;
    if (arbol)
    {
        if (arbol->paciente.DNI==dni)
        {
            nodoBusqueda=crearNodoArbol(arbol->paciente);
        }
        else if (dni < arbol->paciente.DNI)
        {
            nodoBusqueda=buscarXDni (arbol->izq, dni);
        }
        else
        {
            nodoBusqueda=buscarXDni (arbol->der, dni);
        }
    }
    else
    {
        printf ("No existe un paciente con el dni %d en el sistema \n");
    }
    return nodoBusqueda;
}

nodoArbolPaciente * actualizarNodoArbol (nodoArbolPaciente * arbol, int dni)
{
    if (arbol)
    {
        if (arbol->paciente.DNI==dni)
        {
            system("pause");
            arbol->paciente=cargaManualPaciente();
        }
        else if (dni < arbol->paciente.DNI)
        {
            arbol->izq=actualizarNodoArbol (arbol->izq, dni);
        }
        else
        {
            arbol->der=actualizarNodoArbol (arbol->der, dni);
        }

    }
    return arbol;
}

nodoArbolPaciente * bajaNodoArbol (nodoArbolPaciente * arbol, int dni)
{
    if (arbol)
    {
        if (arbol->paciente.DNI==dni)
        {
            arbol->paciente.eliminado=1;
        }
        else if (dni < arbol->paciente.DNI)
        {
            arbol->izq=bajaNodoArbol (arbol->izq, dni);
        }
        else
        {
            arbol->der=bajaNodoArbol (arbol->der, dni);
        }

    }
    return arbol;
}

void actualizarPacientesEnArchivo (nodoArbolPaciente * arbol)
{
    FILE * buff=fopen("archivo_pacientes.bin", "wb");
    if (buff)
    {
        nodoArbolPaciente * aux=arbol;
        guardarNodoArbolPacientes(aux, buff);
        fclose(buff);
    }
}

void guardarNodoArbolPacientes(nodoArbolPaciente* nodo, FILE * buff)
{
    if (nodo != NULL)
    {
        guardarNodoArbolPacientes(nodo->izq, buff);
        fwrite(&nodo->paciente, sizeof(Paciente), 1, buff);
        guardarNodoArbolPacientes(nodo->der, buff);
    }
}

void cargarTodasListasIngresoDesdeArchi(char archivoIngreso[],nodoArbolPaciente*arbolPacientes)
{
    if (arbolPacientes != NULL)
    {
        cargarTodasListasIngresoDesdeArchi(archivoIngreso,arbolPacientes->izq);
        arbolPacientes->listaIngresos=leerArchivoYCargarLista(archivoIngreso,arbolPacientes);
        cargarTodasListasIngresoDesdeArchi(archivoIngreso,arbolPacientes->der);
    }
}
void mostrarTodasListasIngresoDesdeArbol(nodoArbolPaciente * arbolPacientes)
{
    mostrarTodasListasIngresoDesdeArbol(arbolPacientes->izq);
    mostrarListaIngresos(arbolPacientes->listaIngresos);
    mostrarTodasListasIngresoDesdeArbol(arbolPacientes->der);

}
