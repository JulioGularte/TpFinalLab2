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

