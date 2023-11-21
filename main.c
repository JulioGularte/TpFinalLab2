#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "NodoArbolPaciente.h"
#include "NodoIngreso.h"
#include "NodoArbolPaciente.h"
#define PAUSA system("pause");
#define BORRAR system("cls");


int main()
{
    char archivo[40];
    int a=loguear(archivo);

    /*
    char fecha1[30]="20/11/1994";
    char fecha2[30]="15/10/1994";
    int aux=compararFechas(fecha1,fecha2);
    printf("\n%i",aux);*/
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

