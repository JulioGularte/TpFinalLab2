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

nodoArbolPaciente* buscarXDni(nodoArbolPaciente* arbol, int dni)
{
    if (arbol)
    {
        if (arbol->paciente.DNI == dni)
        {
            return arbol;
        }
        else if (dni < arbol->paciente.DNI)
        {
            return buscarXDni(arbol->izq, dni);
        }
        else
        {
            return buscarXDni(arbol->der, dni);
        }
    }
    else
    {
        // Retorna NULL si el árbol está vacío o el paciente no se encuentra.
        return NULL;
    }
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
        arbolPacientes->listaIngresos=cargarListaDeIngresosDelPaciente(archivoIngreso,arbolPacientes);
        cargarTodasListasIngresoDesdeArchi(archivoIngreso,arbolPacientes->der);
    }
}
void mostrarTodasListasIngresoDesdeArbol(nodoArbolPaciente * arbolPacientes)
{
    mostrarTodasListasIngresoDesdeArbol(arbolPacientes->izq);
    mostrarListaIngresos(arbolPacientes->listaIngresos);
    mostrarTodasListasIngresoDesdeArbol(arbolPacientes->der);

}

void altaDeIngresoPaciente(nodoArbolPaciente * paciente, int * numeroUltimoIngreso, NodoPractica * listaDePracticas, NodoPxI * listaPxI)
{
    NodoPractica * practicaBuscada=NULL;
    mostrarListaPracticas(listaDePracticas, 1);
    do
    {
        printf("Ingresar el numero de practica a realizar el alta, la misma debe estar en estado activo: ");
        int nroPractica;
        scanf("%d",&nroPractica);
        practicaBuscada=encontrarNodoPracticaXId(listaDePracticas, nroPractica);
    }while(!practicaBuscada);
    Ingreso nuevoIngreso=cargarIngresoManual(numeroUltimoIngreso, paciente->paciente.DNI);
    paciente->listaIngresos=agregarPrincipioPxI(listaPxI, crearNodoPxI(crearPxI(nuevoIngreso.NroIngreso, practicaBuscada->practica.nroPractica)));
}

void modificacionDeIngresoPaciente(nodoArbolPaciente * paciente, int * numeroUltimoIngreso, NodoPractica * listaDePracticas, NodoPxI * listaPxI)
{
    NodoPractica * practicaBuscada=NULL;
    mostrarListaPracticas(listaDePracticas, 1);
    do
    {
        printf("Ingresar el numero de practica a modificar, la misma debe estar en estado activo: ");
        int nroPractica;
        scanf("%d",&nroPractica);
        practicaBuscada=encontrarNodoPracticaXId(listaDePracticas, nroPractica);
    }while(!practicaBuscada);
    Ingreso nuevoIngreso=cargarIngresoManual(numeroUltimoIngreso, paciente->paciente.DNI);
    paciente->listaIngresos=agregarPrincipioPxI(listaPxI, crearNodoPxI(crearPxI(nuevoIngreso.NroIngreso, practicaBuscada->practica.nroPractica)));
}
