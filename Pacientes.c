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
    fflush(stdin);
    gets(nuevoPaciente.direccion);
    printf("INGRESE DNI........: \n");
    fflush(stdin);
    scanf("%d", &nuevoPaciente.DNI);
    nuevoPaciente.eliminado==0;
    scanf(&nuevoPaciente.eliminado);
    printf("INGRESE TELEFONO........: \n");
    fflush(stdin);
    gets(nuevoPaciente.telefono);
    printf("INGRESE EDAD........: \n");
    scanf("%d", &nuevoPaciente.edad);
    return nuevoPaciente;
}
