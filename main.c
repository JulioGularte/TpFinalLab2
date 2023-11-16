#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
int main()
{
    menuEjemplo();
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
