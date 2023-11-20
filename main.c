#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "NodoArbolPaciente.h"
#include "NodoIngreso.h"
#define PAUSA system("pause");
#define BORRAR system("cls");


int main()
{   puts("Generando y mostrando Archivo de Pacientes");
    generarNuevoArchiPaciente("archivoPacientes.bin");
    mostrarArchivoPaciente("archivoPacientes.bin");
    PAUSA;
    BORRAR;
    /*puts("Generando y mostrando Archivo de Ingresos");
    generarNuevoArchiIngreso("archivoIngresos.bin");
    mostrarArchivoIngreso("archivoIngresos.bin");
    PAUSA;
    BORRAR;
    puts("Generando y mostrando Archivo de Practicas por ingreso");
    generarNuevoArchiPxI("archivoPxI.bin");
    mostrarArchivoPxI("archivoPxI.bin");
    PAUSA;
    BORRAR;
    puts("Generando y mostrando la lista de ingresos");
    NodoIngresos * listaDeIngresos=inicListaI();
    listaDeIngresos=leerArchivoYCargarLista("archivoIngresos.bin",listaDeIngresos);
    mostrarListaIngresos(listaDeIngresos);*/
    ///Ingreso nuevoIngresoManual;
    ///7int nroIngreso=201;
    ///nuevoIngresoManual=cargarIngresoManual(&nroIngreso);
    nodoArbolPaciente * arbolPacientes=NULL;
    arbolPacientes=cargarArbolDesdeArchi("archivoPacientes.bin",arbolPacientes);
    PAUSA;
    BORRAR;
    mostrarArbolPacientes(arbolPacientes);

    return 0;
}

int menuEjemplo()
{
    Menu nuevoMenu;
    nuevoMenu.opcionSeleccionada = 0;
    nuevoMenu.titulo = "Bienvenido a HaCPedidos";
    nuevoMenu.cantidadOpciones = 3;
    nuevoMenu.opciones = malloc(nuevoMenu.cantidadOpciones * sizeof(char *));
    nuevoMenu.opciones[0] = "Ingresar";
    nuevoMenu.opciones[1] = "Registrarse";
    nuevoMenu.opciones[2] = "Salir";
    nuevoMenu.opcionSeleccionada = gestionarMenu(nuevoMenu);
    return nuevoMenu.opcionSeleccionada;

}

