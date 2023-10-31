#include "ingresos.h"
#include <stdio.h>
///deben actualizarse encascada (dar de baja), las practicas asociadas al ingreso
void bajaDeIngreso (int idIngreso)
{
    FILE * buff=fopen("archivoIngreso", "rb");
    Ingresos rgIngreso;
    int flag=0;
    if (buff)
    {
        while (fread(&rgIngreso, sizeof(Ingresos), 1, buff)>0)
        {
            if (rgIngreso.NroIngreso==idIngreso)
            {
                flag=1;
                fseek(buff, -sizeof(rgIngreso), SEEK_CUR);
                rgIngreso.Eliminado=0;
                fwrite(&rgIngreso, sizeof(Ingresos),1, buff);
            }
        }
        if (flag)
        {
            ///fn para dar de baja las practicas de ingreso
            //bajaDePxI(rgIngreso.NroIngreso);
        }
        else
        {
            printf("No existe el ingreso solicitado \n");
        }
        fclose(buff);
    }
    else
    {
        printf("Error al abrir el archivo de ingresos \n");
    }
}
