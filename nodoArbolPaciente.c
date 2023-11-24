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
#define archivoPacientes "archivo_pacientes.bin"
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
    return nuevoNodo;
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


nodoArbolPaciente * cargarArbolDesdeArchi(nodoArbolPaciente * arbolPacientes)
{
    FILE * archi=fopen(archivoPacientes,"rb");
    if(archi)
    {
        Paciente nuevoPaciente;
        while(fread(&nuevoPaciente,sizeof(Paciente),1,archi)>0)
        {
            nodoArbolPaciente * nodoAcargar=crearNodoArbol(nuevoPaciente);
            nodoAcargar->listaIngresos=cargarListaDeIngresosDelPaciente(&nodoAcargar);
            NodoIngresos * listaIngresos=nodoAcargar->listaIngresos;
            if (listaIngresos)
            {
                listaIngresos->listaPxI=cargarListaPxIDesdeArchivo (listaIngresos->ingreso.NroIngreso);
            }
            arbolPacientes=cargarArbolOrdenadoDNI(arbolPacientes,nodoAcargar);

        }
        fclose(archi);
    }
    system("pause");
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

void bajaNodoArbol (nodoArbolPaciente * arbol, int dni)
{
    if (arbol)
    {
        if (arbol->paciente.DNI==dni)
        {
            arbol->paciente.eliminado=1;
        }
        else if (dni < arbol->paciente.DNI)
        {
            bajaNodoArbol (arbol->izq, dni);
        }
        else
        {
            bajaNodoArbol (arbol->der, dni);
        }
    }
}
/*
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
*/

NodoIngresos * actualizarPacientesEnArchivo (nodoArbolPaciente * arbol)
{
    FILE * buff=fopen(archivoPacientes, "wb");
    NodoIngresos * nodoIngresosPaciente=inicListaI();
    if (buff)
    {
        nodoArbolPaciente * aux=arbol;
        guardarNodoArbolPacientes(aux, buff, &nodoIngresosPaciente);
        fclose(buff);
    }
    return nodoIngresosPaciente;
}

void guardarNodoArbolPacientes(nodoArbolPaciente* nodo, FILE * buff, NodoIngresos ** nodoIngresosPaciente)
{
    if (nodo != NULL)
    {
        guardarNodoArbolPacientes(nodo->izq, buff, nodoIngresosPaciente);

        fwrite(&nodo->paciente, sizeof(Paciente), 1, buff);

        guardarNodoArbolPacientes(nodo->der, buff, nodoIngresosPaciente);

        NodoIngresos * seg=nodo->listaIngresos;
        while (seg)
        {
            (*nodoIngresosPaciente)=cargarListaIngreso_inicio_conservar_lista_ingresos((*nodoIngresosPaciente), seg);
            seg=seg->siguiente;
        }

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

void altaDeIngresoPaciente(nodoArbolPaciente * paciente, int numeroUltimoIngreso, NodoPractica * listaDePracticas)
{
    int nroPractica;
    NodoPractica * practicaBuscada=NULL;
    Ingreso nuevoIngreso=cargarIngresoManual(paciente->paciente.DNI);
    nuevoIngreso.NroIngreso=numeroUltimoIngreso+1;
    printf("Nro ingreso %d", nuevoIngreso.NroIngreso);
    NodoIngresos * nuevoNodoIngreso=inicListaI();
    nuevoNodoIngreso=crearNodoI(nuevoIngreso);
    nuevoNodoIngreso->listaPxI=inicListaPxI();
    char control='s';
    fflush(stdin);
    while(control=='s')
    {
        do
        {
            mostrarListaPracticas(listaDePracticas, 1);
            printf("Ingresar el numero de practica a realizar el alta, la misma debe estar en estado activo: ");
            scanf("%d",&nroPractica);
            practicaBuscada=encontrarNodoPracticaXId(listaDePracticas, nroPractica);
            if (!practicaBuscada)
            {
                printf ("No existe una practica con ese nro practica \n");
                PAUSA
                BORRAR
            }
            else if (practicaBuscada->practica.eliminado==1)
            {
                printf ("La practica se encuentra eliminada \n");
                PAUSA
                BORRAR
            }
        }
        while(!practicaBuscada || practicaBuscada->practica.eliminado==1);
        PracticasXIngreso pxi=crearPxI(nuevoIngreso.NroIngreso, nroPractica);
        NodoPxI * nuevaPxI=crearNodoPxI(pxi);
        nuevoNodoIngreso->listaPxI=agregarPrincipioPxI(nuevoNodoIngreso->listaPxI, crearNodoPxI(pxi));
        printf ("Ingrese 's' para contunuar cargando practicas \n");
        fflush(stdin);
        scanf("%c",&control);
    }
    paciente->listaIngresos=cargarListaIngreso_inicio_nodo(paciente->listaIngresos, nuevoNodoIngreso);
}

void modificacionDeIngresoPaciente(nodoArbolPaciente * paciente)
{
    NodoIngresos * ingresoBuscado=NULL;
    int nroIngreso;
    do
    {
        mostrarListaIngresos(paciente->listaIngresos);
        printf ("Ingrese el nro de ingreso a modificar \n");
        scanf ("%d",&nroIngreso);
        ingresoBuscado=buscarNodoIngresoPorNroIngreso(paciente->listaIngresos, nroIngreso);
        if (!ingresoBuscado)
        {
            printf ("No existe un ingreso con el nroIngreso: %d \n", nroIngreso);
            PAUSA
            BORRAR
        }
    }
    while(!ingresoBuscado);
    Ingreso ingresoAEditar=ingresoBuscado->ingreso;
    printf ("Ingrese el nro de matricula del nuevo profesional solicitante: \n");
    scanf("%d", &ingresoAEditar.MatriculaPersonalSolicitante);
    char fechaRetiro[11];
    int formatoFechaValida;
    int fechaValida;
    do
    {
        puts("Ingrese la fecha estimada de retiro: (dd/mm/aaaa)");
        scanf("%s",fechaRetiro);

        formatoFechaValida=validarFormatoFecha(fechaRetiro);
        fechaValida=compararFechas(ingresoAEditar.FechaIngreso,fechaRetiro);
        if (fechaValida==1 && formatoFechaValida==1)
        {
            strcpy(ingresoAEditar.FechaRetiro,fechaRetiro);
        }
        else
        {
            if (fechaValida!=1)
            {

                puts("La fecha de retiro no puede ser anterior a la fecha de ingreso");
                printf("La fecha de ingreso es %s \n",ingresoAEditar.FechaIngreso);
            }
            else if (formatoFechaValida!=1)
            {
                puts("La fecha debe tener un formato dd/mm/aaaa y ser una fecha valida");
            }
        }
    }
    while(fechaValida!=1 || formatoFechaValida!=1);
    ingresoBuscado->ingreso=ingresoAEditar;
}
/*
void cargarListaPxIEnPaciente (nodoArbolPaciente * paciente, NodoPxI * listaPxI)
{
    nodoArbolPaciente * segArbol=arbol;
    nodoArbolPaciente * segLista=listaPxI;
    if (segArbol && segLista)
    {

    }
}
*/

int contarIngresosDeTodosLosPacientes(nodoArbolPaciente *arbol)
{
    int cantidad = 0;
    NodoIngresos *seg;

    if (arbol)
    {
        seg = arbol->listaIngresos;
        while (seg)
        {
            cantidad++;
            seg = seg->siguiente;
        }
        cantidad += contarIngresosDeTodosLosPacientes(arbol->izq);
        cantidad += contarIngresosDeTodosLosPacientes(arbol->der);
    }

    return cantidad;
}


void mostrarNodosIngresosTodosLosPacientes (nodoArbolPaciente * arbol)
{
    if (arbol)
    {
        mostrarNodosIngresosTodosLosPacientes (arbol -> izq);
        mostrarListaIngresos(arbol->listaIngresos);
        mostrarNodosIngresosTodosLosPacientes (arbol -> der);
    }
}

NodoIngresos * buscarNodoIngresoEnArbol (nodoArbolPaciente * arbol, NodoIngresos * buscado, int nroIngreso)
{
   if (arbol == NULL) {
       return NULL;
   }
   buscado = buscarNodoIngresoEnArbol(arbol->izq, buscado, nroIngreso);

   if (buscado != NULL) {
       return buscado;
   }

   buscado = buscarNodoIngresoPorNroIngreso(arbol->listaIngresos, nroIngreso);

   if (buscado != NULL) {
       return buscado;
   }

   return buscarNodoIngresoEnArbol(arbol->der, buscado, nroIngreso);
}

/*
NodoIngresos * obtenerIngresosDeTodosLosPacientes (nodoArbolPaciente * arbol)
{
    NodoIngresos * nodoIngresosPaciente=inicListaI();
    if (arbol)
    {
        nodoArbolPaciente * aux=arbol;
        arbolToIngresosPaciente(aux, &nodoIngresosPaciente);
    }
    return nodoIngresosPaciente;
}

void arbolToIngresosPaciente(nodoArbolPaciente * arbol, NodoIngresos ** nodoIngresosPaciente)
{
    if (arbol != NULL)
    {
        arbolToIngresosPaciente(arbol->izq, nodoIngresosPaciente);

        NodoIngresos * seg=arbol->listaIngresos;
        while (seg)
        {
            (*nodoIngresosPaciente)=cargarListaIngreso_inicio_nodo((*nodoIngresosPaciente), crearNodoI(seg->ingreso));
            seg=seg->siguiente;
        }


        arbolToIngresosPaciente(arbol->der, nodoIngresosPaciente);
    }
}
*/
void mostrarPracticasXIngresos (NodoIngresos * ingresosDeLosPacientes, int nroIngreso, NodoPractica * listaPracticas)
{
    NodoIngresos * seg=ingresosDeLosPacientes;
    while(seg)
    {
        NodoPxI * PxI=seg->listaPxI;
        if (seg->ingreso.NroIngreso==nroIngreso)
        {
            while (PxI)
            {
                NodoPractica * nodo=encontrarNodoPracticaXId (listaPracticas, PxI->PxI.nroPractica);
                printf ("==================================================== \n");
                mostrarUnaPractica(nodo->practica, 1);
                printf ("Practicas: \n");
                printf ("Resultado: %s \n", PxI->PxI.resultado);
                printf ("==================================================== \n");
                PxI=PxI->siguiente;
            }
        }
        seg=seg->siguiente;
    }
}
