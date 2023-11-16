#include "Practicas.h"
#include <stdio.h>
int contarPracticasEnArchivo()
{
    FILE * buff=fopen("archivoPracticas", "rb");
    int cantidad=0;
    if (buff)
    {
        Practica rg;
        while (fread(&rg, sizeof(Practica),1, buff)>0)
        {
            cantidad++;
        }
        fclose(buff);
    }
    return cantidad;
}

