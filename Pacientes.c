#include "NodoArbolPaciente.h"
#include <stdio.h>
#include <string.h>
Paciente cargaManualPaciente()
{
    Paciente nuevoPaciente;
    printf("INGRESE NOMBRE Y APELLIDO........: \n");
    fflush(stdin);
    gets(nuevoPaciente.NyA);
    printf("INGRESE DIRECCION ........: \n");
    gets(nuevoPaciente.direccion);
    printf("INGRESE DNI........: \n");
    scanf(&nuevoPaciente.DNI);
    int opcion;
    do
    {
    printf("Desea dar de baja el paciente? \n 1-si \n 0-no");
    scanf("%d",&opcion);
    }while (opcion != 1 && opcion !=0);
    scanf(&nuevoPaciente.eliminado);
    printf("INGRESE TELEFONO........: \n");
    fflush(stdin);
    gets(nuevoPaciente.telefono);
    return nuevoPaciente;
}
