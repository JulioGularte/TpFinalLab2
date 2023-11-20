#include "Practicas.h"
#include <stdio.h>

Practica crearStPractica ()
{
    Practica nueva;
    nueva.eliminado=0;
    printf ("Ingrese el nombre de la practica: \n");
    fflush(stdin);
    gets(nueva.NombrePractica);
    return nueva;
}

void mostrarUnaPractica(Practica practica, int esAdmin)
{
    if (esAdmin==1)
    {
        printf ("Nro Practica: %d \n", practica.nroPractica);
        printf ("Estado: %s \n", practica.eliminado==1 ? "Eliminada" : "Activa");
    }
    printf ("Practica: %s \n", practica.NombrePractica);
}
