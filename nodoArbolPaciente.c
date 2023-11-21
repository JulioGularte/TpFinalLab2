#define _XOPEN_SOURCE 700
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
                aux=cargarArbolOrdenadoDNI(aux->der,nodoACargar);
            }
            else
            {
                aux=cargarArbolOrdenadoDNI(aux->izq,nodoACargar);
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

        }
fclose(archi);
return arbolPacientes;
}


void cargaManualPaciente(Paciente nuevoPaciente)
{
    printf("INGRESE NOMBRE Y APELLIDO........: \n");
    scanf(&nuevoPaciente.NyA);
    printf("INGRESE DIRECCION ........: \n");
    scanf(&nuevoPaciente.direccion);
    printf("INGRESE DNI........: \n");
    scanf(&nuevoPaciente.DNI);
    printf("Desea dar de baja el paciente?\n 1-si\n2-no");
    scanf(&nuevoPaciente.eliminado);
    printf("INGRESE TELEFONO........: \n");
    scanf(&nuevoPaciente.telefono);
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

    if(arbolPacientes!=NULL)
        {
        mostrarArbolPacientes(arbolPacientes->izq);
        mostrarNodoArbol(arbolPacientes);
        mostrarArbolPacientes(arbolPacientes->der);


        }

}
