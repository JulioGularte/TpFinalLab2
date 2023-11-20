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
