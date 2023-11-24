#include "menu.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#include <windows.h> ///me deja utilizar la funcion sleep
#include "gotoxy.h"  ///me permite cambiar la posicion del cursor
#define TeclaArriba 72
#define TeclaAbajo 80
#define Enter 13

#include "NodoPractica.h"

int crearMenuPrincipalPracticasAdministradores()
{
    Menu nuevoMenu;
    nuevoMenu.opcionSeleccionada = 0;
    nuevoMenu.titulo = "Gestion de Practicas";
    nuevoMenu.cantidadOpciones = 3;
    nuevoMenu.opciones = malloc(nuevoMenu.cantidadOpciones * sizeof(char *));
    nuevoMenu.opciones[0] = "Alta de Practica";
    nuevoMenu.opciones[1] = "Modificacion de Practica";
    nuevoMenu.opciones[2] = "Baja de practica";
    nuevoMenu.opciones[3] = "Volver al menu principal";
    nuevoMenu.opcionSeleccionada = gestionarMenu(nuevoMenu);
    return nuevoMenu.opcionSeleccionada;
}

int gestionarMenu(Menu menu)
{
    pintarPantallaConMenu(menu);
    int teclaPulsada = 0;
    do
    {
        teclaPulsada = getch();
        menu.opcionSeleccionada = cambiarOpcionSeleccionada(teclaPulsada, menu.cantidadOpciones, menu.opcionSeleccionada);
        pintarPantallaConMenu(menu);
    } while (teclaPulsada != Enter);
    return menu.opcionSeleccionada;
}

void gestionarOpcionesMenuPracticasAdministradores (Menu menu, NodoPractica * lista)
{
    system("cls");
    switch(menu.opcionSeleccionada)
    {
    case 0:
        lista=altaDePractica(lista, crearNodoPractica(crearStPractica()));
        break;
    case 1:
        mostrarListaPracticas(lista, 1, 0);
        int idPractica;
        scanf("%d",&idPractica);
        printf ("Ingrese nuevo nombre para la practica: \n");
        fflush(stdin);
        char nuevoNombre[30];
        gets(nuevoNombre);
        editarPractica(lista, idPractica, nuevoNombre);
        break;
    }
}
int cambiarOpcionSeleccionada(int teclaPulsada, int cantidadOpciones, int opcionSeleccionada)
{
    if (teclaPulsada == TeclaAbajo)
    {
        opcionSeleccionada++;
        if (opcionSeleccionada > cantidadOpciones - 1)
        {
            opcionSeleccionada = 0;
        }
    }

    if (teclaPulsada == TeclaArriba)
    {
        opcionSeleccionada--;
        if (opcionSeleccionada < 0)
        {
            opcionSeleccionada = cantidadOpciones - 1;
        }
    }

    return opcionSeleccionada;
}

void pintarPantallaConMenu(Menu menu)
{
    system("cls");
    mostrarPantallaConMenu(menu);
}

void mostrarPantallaConMenu(Menu menu)
{
    printf("\t -- %s --\n", menu.titulo);
    for (int i = 0; i < menu.cantidadOpciones; i++)
    {
        mostrarOpcion(menu.opciones[i], i, menu.opcionSeleccionada);
    }
}

void mostrarOpcion(char *opcion, int numeroDeOpcion, int opcionSeleccionada)
{
    gotoxy(6, 3 + numeroDeOpcion);
    if (opcionSeleccionada == numeroDeOpcion)
    {
        color(112);
        printf(" %s \n", opcion);
        color(7);
    }
    else
    {
        printf(" %s \n", opcion);
    }
}
